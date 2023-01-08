#ifndef CCL_PROJECT_BENCH_CHUNK_HPP
#define CCL_PROJECT_BENCH_CHUNK_HPP

#include <span>
#include <vector>

auto chunk(const std::vector<int> &vector, size_t chunks_count)
    -> std::vector<std::span<const int>>;

#endif /* CCL_PROJECT_BENCH_CHUNK_HPP */
