#include "accumulate.hpp"
#include <benchmark/benchmark.h>

namespace accumulate
{
    static auto mutexAccumulate(benchmark::State &state) -> void
    {
        const auto &chunk_numbers = ChunkedNumbers[static_cast<size_t>(state.threads() - 1)];
        const auto &numbers = chunk_numbers[static_cast<size_t>(state.thread_index())];

        for (auto _ : state) {
            for (auto number : numbers) {
                const auto lock = std::scoped_lock{Mutex};
                Counter += number;
            }

            benchmark::DoNotOptimize(Counter);
        }
    }

    BENCHMARK(mutexAccumulate)->DenseThreadRange(1, ThreadLimit)->UseRealTime();
}// namespace accumulate
