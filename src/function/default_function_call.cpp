#include "function.hpp"
#include <benchmark/benchmark.h>

namespace function
{
    static auto noinlineFunctionCall(benchmark::State &state) -> void
    {
        for (auto _ : state) {
            for (int a = 0; a < 9000; ++a) {
                for (int b = 0; b < 9000; ++b) {
                    benchmark::DoNotOptimize(testNoinlineFunction(a, b));
                }
            }
        }
    }

    BENCHMARK(noinlineFunctionCall);

    static auto inlineFunctionCall(benchmark::State &state) -> void
    {
        for (auto _ : state) {
            for (int a = 0; a < 9000; ++a) {
                for (int b = 0; b < 9000; ++b) {
                    benchmark::DoNotOptimize(testInlineFunction(a, b));
                }
            }
        }
    }

    BENCHMARK(inlineFunctionCall);
}// namespace function
