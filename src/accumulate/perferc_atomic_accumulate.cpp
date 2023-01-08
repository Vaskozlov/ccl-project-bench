#include "accumulate.hpp"
#include <benchmark/benchmark.h>

namespace accumulate
{
    static auto perfectAtomicAccumulate(benchmark::State &state) -> void
    {
        const auto &chunk_numbers = ChunkedNumbers[static_cast<size_t>(state.threads() - 1)];
        const auto &numbers = chunk_numbers[static_cast<size_t>(state.thread_index())];

        for (auto _ : state) {
            ssize_t local_accumulator = 0;

            for (auto number : numbers) {
                local_accumulator += number;
            }

            atomic_fetch_add_explicit(
                &AtomicAccumulator, local_accumulator, std::memory_order_relaxed);
            benchmark::DoNotOptimize(AtomicAccumulator.load(std::memory_order_relaxed));
        }
    }

    BENCHMARK(perfectAtomicAccumulate)->DenseThreadRange(1, ThreadLimit)->UseRealTime();
}// namespace accumulate
