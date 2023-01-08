#include "accumulate.hpp"
#include <benchmark/benchmark.h>

namespace accumulate
{
    static auto perfectMutexAccumulate(benchmark::State &state) -> void
    {
        const auto &chunk_numbers = ChunkedNumbers[static_cast<size_t>(state.threads() - 1)];
        const auto &numbers = chunk_numbers[static_cast<size_t>(state.thread_index())];

        for (auto _ : state) {
            ssize_t local_accumulator = 0;

            for (auto number : numbers) {
                local_accumulator += number;
            }

            {
                const auto lock = std::scoped_lock{Mutex};
                Counter += local_accumulator;
            }

            benchmark::DoNotOptimize(Counter);
        }
    }

    BENCHMARK(perfectMutexAccumulate)->DenseThreadRange(1, ThreadLimit)->UseRealTime();
}// namespace accumulate
