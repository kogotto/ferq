cmake_minimum_required(VERSION 3.16.3)

project(freq)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    frequency.cpp
)

find_package(benchmark)
if (benchmark_FOUND)
    add_executable(
        benchmark
        bench.cpp
        frequency.cpp
    )
    target_link_libraries(
        benchmark
        benchmark::benchmark
    )
else()
    message(WARNING "Google benchmark not found. Install it to build benchmark")
endif()
