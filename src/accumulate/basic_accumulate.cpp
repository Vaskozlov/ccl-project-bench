#include "accumulate.hpp"
#include <benchmark/benchmark.h>

namespace accumulate
{
    static auto basicAccumulate(benchmark::State &state) -> void
    {
        const auto &chunk_numbers = ChunkedNumbers[static_cast<size_t>(state.threads() - 1)];
        const auto &numbers = chunk_numbers[static_cast<size_t>(state.thread_index())];

        for (auto _ : state) {
            ssize_t local_accumulator = 0;

            for (auto number : numbers) {
                Counter += number;
            }

            benchmark::DoNotOptimize(local_accumulator);
        }
    }

    BENCHMARK(basicAccumulate)->UseRealTime();
}// namespace accumulate
