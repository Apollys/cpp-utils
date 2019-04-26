#include <chrono>
#include <random>

namespace rng {

int CurrentTimeNano() {
  auto current_time = std::chrono::high_resolution_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(current_time).count();
}

template <typename IntType>
IntType SimpleIntRng(IntType min_value, IntType max_value) {
  static_assert(std::is_integral<IntType>::value, "Parameters must be of integral type");
  static std::default_random_engine engine(CurrentTimeNano());
  std::uniform_int_distribution<int> distribution(min_value, max_value);
  return distribution(engine);
}
  
} // namespace rng
