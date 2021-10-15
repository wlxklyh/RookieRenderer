#（1）把文件夹下的cpp文件名字添加到SRC_List 然后组织文件夹结构
file(GLOB FRAMEWORK_SOURCE Framework/*.cpp Framework/*.hpp Framework/*.inl Framework/*.h)
file(GLOB MAIN_SOURCE Main/*.cpp Main/*.hpp Main/*.inl Main/*.h)

source_group("Framework" FILES ${FRAMEWORK_SOURCE})
source_group("Main" FILES ${MAIN_SOURCE})

AUX_SOURCE_DIRECTORY(Main SRC_LIST)
AUX_SOURCE_DIRECTORY(Framework SRC_LIST)

#（2）添加一个可执行的文件
ADD_EXECUTABLE(${PROJECT_NAME}
        ${FRAMEWORK_SOURCE}
        ${MAIN_SOURCE}
        )

#（3）设置可执行的文件 放在哪个目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

#（4）添加include 目录 这样cpp里面可以直接include这些目录的文件
INCLUDE_DIRECTORIES(Framework)
INCLUDE_DIRECTORIES(Main)

#（5）如果是VS则设置启动项目
if (MSVC)
    # Set the startup project .
    if (NOT ${CMAKE_VERSION} VERSION_LESS "3.6.0")
        MESSAGE(STATUS "MSVC ===")
        MESSAGE(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
        MESSAGE(STATUS ${PROJECT_NAME})
        set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    endif ()
endif (MSVC)


