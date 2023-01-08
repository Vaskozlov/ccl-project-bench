file(
        GLOB_RECURSE
        CCL_CONCEPTS_OBJECTS
        "src/*.cpp"
)

add_executable(ccl-concepts-bench ${CCL_CONCEPTS_OBJECTS})

add_dependencies(ccl-concepts-bench fmt::fmt)
add_dependencies(ccl-concepts-bench benchmark::benchmark)

target_link_libraries(
        ccl-concepts-bench
        fmt::fmt
)

target_link_libraries(
        ccl-concepts-bench
        benchmark::benchmark
)
