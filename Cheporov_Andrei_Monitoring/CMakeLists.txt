
cmake_minimum_required(VERSION 3.10)
project(MonitoringApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(monitor
    main.cpp
)

target_include_directories(monitor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
