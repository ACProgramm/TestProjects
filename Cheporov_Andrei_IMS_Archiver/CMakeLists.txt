
cmake_minimum_required(VERSION 3.10)
project(IMSArchiver)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(myapp main.cpp ${SOURCES})

find_package(ZLIB REQUIRED)
target_link_libraries(myapp ZLIB::ZLIB)
