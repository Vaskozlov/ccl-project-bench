#ifndef CCL_PROJECT_BENCH_ACCUMULATE_HPP
#define CCL_PROJECT_BENCH_ACCUMULATE_HPP

#include "../chunk.hpp"
#include "../random_vector.hpp"
#include <mutex>
#include <span>
#include <thread>
#include <vector>

namespace accumulate
{
    const inline auto Numbers = generateVector(10'000'000);
    const inline auto ChunkedNumbers = []() {
        auto chunks = std::vector<std::vector<std::span<const int>>>{};

        for (size_t i = 1; i != std::thread::hardware_concurrency() + 1; ++i) {
            chunks.emplace_back(chunk(Numbers, i));
        }

        return chunks;
    }();

    inline auto Mutex = std::mutex{};
    inline auto Counter = static_cast<ssize_t>(0);
    inline auto AtomicAccumulator = std::atomic<ssize_t>(0);

    inline const auto ThreadLimit = static_cast<int>(std::thread::hardware_concurrency());
}// namespace accumulate

#endif /* CCL_PROJECT_BENCH_ACCUMULATE_HPP */
