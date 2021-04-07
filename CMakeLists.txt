cmake_minimum_required(VERSION 3.17)
project(autopalya)

set(CMAKE_CXX_STANDARD 98)

add_compile_definitions(MEMTRACE)

add_executable(autopalya main.cpp memtrace.cpp autopalya.cpp auto.cpp auto_tarolo.cpp)