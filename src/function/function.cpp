#include "function.hpp"
#include <array>
#include <benchmark/benchmark.h>
#include <fmt/format.h>
#include <iostream>

namespace function
{
    auto Vector = std::vector<size_t>{};

    auto testNoinlineFunction(int a, int b) -> int
    {
        return (a + b) * (a + b);
    }

    // NOLINTNEXTLINE
    static auto findCacheSize(int level) -> size_t
    {
        const auto level_minus_one = static_cast<size_t>(level - 1);

        static const auto &caches = benchmark::CPUInfo::Get().caches;
        static std::array<size_t, 3> ready_cache_size{};

        if (level <= 3 && ready_cache_size.at(level_minus_one) != 0) {
            return ready_cache_size.at(level_minus_one);
        }

        if (0 == level) {
            std::cerr << "Unable to find cache size\n";
            std::exit(1);// NOLINT
        }

        for (const auto &cache : caches) {
            if ((level == cache.level) && ((level != 1) || (cache.type == "Data"))) {
                ready_cache_size.at(level_minus_one) = static_cast<size_t>(cache.size);// NOLINT
                fmt::print("{} {}\n", level, cache.size);
                return ready_cache_size.at(level_minus_one);
            }
        }

        return findCacheSize(level - 1);
    }

    // NOLINTBEGIN
    auto clearCache(CacheType cache_type) -> void
    {
        size_t bytes_to_clear = 0;

        if (cache_type == CacheType::L1) {
            bytes_to_clear = findCacheSize(1);
        } else if (cache_type == CacheType::L2) {
            bytes_to_clear = findCacheSize(2);
        } else {
            bytes_to_clear = findCacheSize(3);
        }

        const auto vector_size = bytes_to_clear / sizeof(size_t) +
                                 static_cast<unsigned long>(bytes_to_clear % sizeof(size_t) != 0);
        Vector.resize(vector_size);

        for (size_t i = 0; i != 20; ++i) {
// unrolling loop
#pragma unroll 4
            for (size_t j = 0; j != vector_size; ++j) {
                Vector[j] = i;
            }

            benchmark::DoNotOptimize(Vector);
        }
    }
    // NOLINTEND
}// namespace function
