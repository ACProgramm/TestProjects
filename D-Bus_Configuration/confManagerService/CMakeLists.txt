
cmake_minimum_required(VERSION 3.14)
project(confManagerService)

find_package(Qt5 REQUIRED COMPONENTS Core DBus)

set(SOURCES
    src/main.cpp
    src/ConfigurationManager.cpp
)

set(HEADERS
    include/ConfigurationManager.hpp
)

include_directories(include)

add_executable(confManagerService ${SOURCES} ${HEADERS})

target_link_libraries(confManagerService Qt5::Core Qt5::DBus)
