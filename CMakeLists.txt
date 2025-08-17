cmake_minimum_required(VERSION 3.12)
project(cpu-sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

file(GLOB SRC
    src/*.cpp
    src/schedulers/*.cpp
)

add_executable(cpu-sim ${SRC})
target_include_directories(cpu-sim PRIVATE src)
