cmake_minimum_required(VERSION 3.7)
# 指定C++11
set(CMAKE_CXX_STANDARD 11)
set(NAME RookieRenderer)
project(RookieRenderer)


#=====
macro(PrintList eles preStr)
    foreach (ele ${eles})
        message("${preStr} ${ele}")
    endforeach ()
endmacro()
#===
# Framework
# Main->[All]
# Platform
# RMath->Platform
# Material->RMath
# Scene->RMath
# RPhysics->Material->RMath
#（1）扫描文件
set(MAIN_TARGET_FILES)
set(TEST_TARGET_FILES)
set(SRC_INCLUDE_DIR)

file(GLOB_RECURSE file_list LIST_DIRECTORIES true src/*)
foreach (file ${file_list})
    #/Main/ 目录不能放到Test里面
    if (NOT file MATCHES "\\.")
        #文件夹
        set(SRC_INCLUDE_DIR ${SRC_INCLUDE_DIR} ${file})
    else ()

        #文件
        if (NOT file MATCHES "/Main/")
            #不包含Main的放在Test这个target
            set(TEST_TARGET_FILES ${TEST_TARGET_FILES} ${file})
        endif ()

        if (NOT file MATCHES "_test")
            #不包含_test放在Main这个target
            set(MAIN_TARGET_FILES ${MAIN_TARGET_FILES} ${file})
        endif ()
    endif ()
endforeach ()

message(=== (1) Files:)
PrintList("${SRC_INCLUDE_DIR}" "Dir:")
PrintList("${TEST_TARGET_FILES}" "Test Files:")
PrintList("${MAIN_TARGET_FILES}" "Main Files:")


#（2）Target设置
add_executable(${PROJECT_NAME} ${MAIN_TARGET_FILES})
add_executable(UnitTest ${TEST_TARGET_FILES})

#（3）设置可执行的文件 放在哪个目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#这个宏定义是为了解决mac 和 windows的编译差异
add_compile_definitions(_USE_MATH_DEFINES)

#（4）添加include 目录 这样cpp里面可以直接include这些目录的文件
include_directories(${SRC_INCLUDE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


#（5）如果是VS则设置启动项目
if (MSVC)
    # Set the startup project .
    if (NOT ${CMAKE_VERSION} VERSION_LESS "3.6.0")
        set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    endif ()
endif (MSVC)


#（6）单元测试
include(FetchContent)
fetchcontent_declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
fetchcontent_makeavailable(googletest)


target_link_libraries(${PROJECT_NAME} gtest_main)
target_link_libraries(UnitTest gtest_main)
add_test(NAME example_test COMMAND UnitTest)

include(GoogleTest)
gtest_discover_tests(UnitTest)


#备忘：
#1、分组问题：
#https://www.jianshu.com/p/c31b00acc57b
#http://blog.audio-tk.com/2015/09/01/sorting-source-files-and-projects-in-folders-with-cmake-and-visual-studioxcode/