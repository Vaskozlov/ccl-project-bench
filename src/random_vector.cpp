#include "random_vector.hpp"
#include <random>

constexpr static auto LowerBound = -1000;
constexpr static auto UpperBound = 1000;

auto generateVector(size_t size) noexcept -> std::vector<int>
{
    static auto random_device = std::random_device{};                                         // NOLINT
    static auto random_engine = std::default_random_engine(random_device());                   // NOLINT
    static auto int_distribution = std::uniform_int_distribution<int>(LowerBound, UpperBound);// NOLINT

    auto vector = std::vector<int>(size);

    for (auto &number : vector) {
        number = int_distribution(random_engine);
    }

    return vector;
}
