#include "chunk.hpp"
#include <cstddef>
#include <span>

auto chunk(const std::vector<int> &vector, size_t chunks_count) -> std::vector<std::span<const int>>
{
    auto result = std::vector<std::span<const int>>{};
    auto chunk_size = std::max<size_t>(1, vector.size() / chunks_count);
    auto last_chunk = vector.begin();
    const auto loop_stop = std::min(vector.size(), chunks_count) - 1;
    result.reserve(chunks_count);

    if (chunk_size < vector.size() - loop_stop * chunk_size) {
        ++chunk_size;
    }

    for (size_t i = 0; i != loop_stop && (last_chunk + chunk_size < vector.end()); ++i) {
        last_chunk = vector.begin() + static_cast<ptrdiff_t>((i + 1) * chunk_size);
        result.emplace_back(vector.begin() + static_cast<ptrdiff_t>(i * chunk_size), last_chunk);
    }

    result.emplace_back(last_chunk, vector.end());

    return result;
}
