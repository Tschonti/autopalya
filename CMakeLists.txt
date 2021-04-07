cmake_minimum_required(VERSION 3.17)
project(autopalya)

set(CMAKE_CXX_STANDARD 98)

add_compile_definitions(MEMTRACE)

# Felhasználói felület
#add_executable(autopalya autopalya_main.cpp memtrace.cpp autopalya.cpp auto.cpp auto_tarolo.cpp)

# Tesztelési környezet
add_executable(autopalya memtrace.cpp autopalya.cpp auto.cpp auto_tarolo.cpp autopalya_test.cpp)
add_compile_definitions(MYTEST)