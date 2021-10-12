cmake_minimum_required(VERSION 2.4)
set(NAME RookieRenderer)
project(RookieRenderer)

include_directories(Main)
include_directories(Framwork)
include_directories(UnitTest)

add_executable(app Main/main.cpp)

#add_subdirectory(Framwork)
#add_subdirectory(UnitTest)