cmake_minimum_required(VERSION 3.16.3)

project(freq)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(Boost REQUIRED COMPONENTS iostreams)

add_library(
    core STATIC
    frequency.cpp
    second.cpp
    word_extracter.cpp
    raw_words.cpp
    words.cpp
    writewords.cpp
)
target_link_libraries(
    core
    Boost::iostreams
)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    core
)

find_package(benchmark)
if (benchmark_FOUND)
    add_executable(
        benchmark
        bench.cpp
        bench_helpers.cpp
    )
    target_link_libraries(
        benchmark
        core
        benchmark::benchmark
    )
else()
    message(WARNING "Google benchmark not found. Install it to build benchmark")
endif()
