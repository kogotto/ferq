cmake_minimum_required(VERSION 3.16.3)

project(freq)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    frequency.cpp
    word_extracter.cpp
)

find_package(benchmark)
if (benchmark_FOUND)
    add_executable(
        benchmark
        bench.cpp
        bench_helpers.cpp
        frequency.cpp
        word_extracter.cpp
    )
    target_link_libraries(
        benchmark
        benchmark::benchmark
    )
else()
    message(WARNING "Google benchmark not found. Install it to build benchmark")
endif()
