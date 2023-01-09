#ifndef CCL_PROJECT_BENCH_FUNCTION_HPP
#define CCL_PROJECT_BENCH_FUNCTION_HPP

#include <utility>
namespace function
{
    enum struct CacheType
    {
        L1,
        L2,
        L3
    };

    [[nodiscard]] inline auto testInlineFunction(int a, int b) -> int
    {
        return (a + b) * (a + b);
    }

    [[nodiscard]] auto testNoinlineFunction(int a, int b) -> int;

    [[maybe_unused]] auto clearCache(CacheType cache_type) -> void;
}// namespace function

#endif /* CCL_PROJECT_BENCH_FUNCTION_HPP */
