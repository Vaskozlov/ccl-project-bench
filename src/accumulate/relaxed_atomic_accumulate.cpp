#include "accumulate.hpp"
#include <benchmark/benchmark.h>

namespace accumulate
{
    static auto relaxedAtomicAccumulate(benchmark::State &state) -> void
    {
        const auto &chunk_numbers = ChunkedNumbers[static_cast<size_t>(state.threads() - 1)];
        const auto &numbers = chunk_numbers[static_cast<size_t>(state.thread_index())];

        for (auto _ : state) {
            for (auto number : numbers) {
                std::atomic_fetch_add_explicit(
                    &AtomicAccumulator, number, std::memory_order_relaxed);
            }

            benchmark::DoNotOptimize(AtomicAccumulator.load(std::memory_order_relaxed));
        }
    }

    BENCHMARK(relaxedAtomicAccumulate)->DenseThreadRange(1, ThreadLimit)->UseRealTime();
}// namespace accumulate
