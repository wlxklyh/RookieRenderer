#ifndef PARALLEL_FOR_H
#define PARALLEL_FOR_H

#include <functional>
#include <thread>
#include <map>
#include <stack>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

#define ENABLE_PARALLEL_FOR                    1
#define ENABLE_NESTING_PARALLEL_FOR            0

//全局变量
std::thread::id g_main_thread_id;

using parallel_for_fn = std::function<void(int)>;
enum method {
    FULL_THREAD,
    FULL_THREAD_MINUS_1,
    TASKSYSTEM,
    COUNT,
};

//task系统
class TaskGroup
{
public:
    TaskGroup()
    {
    }
    ~TaskGroup()
    {
    }
    std::atomic<int> m_children_num;    //这组task还有多少在跑
    std::mutex m_mutex;
    std::condition_variable m_cv;       //用于当前线程等待task组全部完成通知唤醒 保证先执行parallel_for完毕后再执行后面的语句
};

class Task {
public:
    TaskGroup* m_task_group;            //task group的信息
    parallel_for_fn m_func;             //任务
    int m_param;                        //参数

    Task() {
        m_task_group = nullptr;
        m_func = nullptr;
        m_param = -1;
    };
    Task(parallel_for_fn func, int param, TaskGroup* task_group) : m_func(func), m_param(param), m_task_group(task_group) {}
};


class TaskScheduler {
public:
    std::mutex m_mutex;
    std::atomic<bool> m_is_runing;
    std::vector<std::thread> m_threads;
    int m_threads_num;
    TaskScheduler(){
        m_threads_num = std::thread::hardware_concurrency();
    }

    TaskScheduler(int num){
        m_threads_num = num;
    }

    std::queue<Task> m_tasks;

    void AddTasks(int first, int last, int step, parallel_for_fn func, TaskGroup* task_parent) {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (int index = first; index < last; index += step) {
            Task task(func, index, task_parent);
            m_tasks.push(task);
        }
    }

    void AddTask(int index, parallel_for_fn func, TaskGroup* task_parent) {
        std::lock_guard<std::mutex> lock(m_mutex);
        Task task(func, index, task_parent);
        m_tasks.push(task);
    }

    bool PopTask(Task &out_task) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_tasks.empty()) {
            return false;
        }
        out_task = m_tasks.front();
        m_tasks.pop();
        return true;
    }

    void FinishTasks()
    {
        m_is_runing = false;
        m_threads.clear();
    }

    void RunTasks() {
        m_threads.clear();
        m_threads.reserve(m_threads_num);
        m_is_runing = true;

        for (int t = 0; t < m_threads_num; ++t) {
            m_threads.emplace_back([&]() {
                while (m_is_runing) {
                    Task task;
                    if (PopTask(task)) {
                        if (task.m_func) {
                            (task.m_func)(task.m_param);
                            task.m_task_group->m_children_num.fetch_sub(1);
                            if(task.m_task_group->m_children_num == 0)
                            {
                                task.m_task_group->m_cv.notify_all();
                            }
                        }
                    }
                }
            });
        }
        for (auto &thread: m_threads) {
            thread.detach();
        }
    }
};
//
TaskScheduler *g_main_taskscheduler = new TaskScheduler(1);
TaskScheduler *g_sub_taskscheduler = new TaskScheduler();

void parallel_for_onelayer(int first, int last, int step, parallel_for_fn func) {
    const int num_threads = std::thread::hardware_concurrency() - 1;//主线程也会调度 所以减去避免线程调度

    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    std::mutex func_mutex;
    int i = first;

    for (int t = 0; t < num_threads; ++t) {
        threads.emplace_back([&]() {
            int local_i;
            while (true) {
                {
                    std::lock_guard<std::mutex> lock(func_mutex);
                    if (i >= last) {
                        break;
                    }
                    local_i = i;
                    i += step;
                }
                func(local_i);
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }
}


void parallel_for_nesting(int first, int last, int step, parallel_for_fn func) {\
    //trick了  保证parallel_for运行完再执行后面的  然后第一层for只有一个线程在添加新线程 第二个for则是 max_core-1个线程在
    bool is_main_thread = (std::this_thread::get_id() == g_main_thread_id);
    if(is_main_thread)
    {
        //（1）主线程添加task
        TaskGroup* task_parent = new TaskGroup();
        task_parent->m_children_num.fetch_add((last - first) / step);

        for (int index = first; index < last; index += step) {
            g_main_taskscheduler->AddTask(index, func, task_parent);
        }

        //（2）主线程等待 所有任务完成
        std::unique_lock<std::mutex> lock(task_parent->m_mutex);
        while ((task_parent->m_children_num) > 0) {
            task_parent->m_cv.wait(lock);
        }
        delete task_parent;
    }
    else
    {
        //（1）子线程添加task
        TaskGroup* task_parent = new TaskGroup();
        task_parent->m_children_num.fetch_add((last - first) / step);
        g_sub_taskscheduler->AddTasks(first, last, step, func, task_parent);

        //（2）子线程等待 所有任务完成
        std::unique_lock<std::mutex> lock(task_parent->m_mutex);
        while ((task_parent->m_children_num) > 0) {
            task_parent->m_cv.wait(lock);
        }
        delete task_parent;
    }

}

void parallel_for(int first, int last, int step, parallel_for_fn func) {
#if ENABLE_NESTING_PARALLEL_FOR
    parallel_for_nesting(first, last, step, func);
#else
    parallel_for_onelayer(first, last, step, func);
#endif
}


void init_parallel_env() {
    g_main_thread_id = std::this_thread::get_id();
    g_main_taskscheduler->RunTasks();
    g_sub_taskscheduler->RunTasks();
}

void fini_parallel_env() {
    /* Write your fini code here */
    g_main_taskscheduler->FinishTasks();
    g_sub_taskscheduler->FinishTasks();
}

#endif

