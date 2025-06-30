
cmake_minimum_required(VERSION 3.14)
project(confManagerApplication1)

find_package(Qt5 REQUIRED COMPONENTS Core DBus)

set(SOURCES
    src/main.cpp
    src/ClientApplication.cpp
)

set(HEADERS
    include/ClientApplication.hpp
)

include_directories(include)

add_executable(confManagerApplication1 ${SOURCES} ${HEADERS})

target_link_libraries(confManagerApplication1 Qt5::Core Qt5::DBus)
