#ifndef RANDOM_VECTOR_HPP
#define RANDOM_VECTOR_HPP

#include <vector>

#include "rng.hpp"

namespace random_vector {

// Generates a vector of integers sampled from a uniform distribution
template <typename IntType>
std::vector<IntType> GenerateIntVector(size_t num_elements, IntType min_value, IntType max_value) {
  static_assert(std::is_integral<IntType>::value, "Requires integral type");
  UniformIntRng<IntType> rng(min_value, max_value);
  std::vector<IntType> generated_vector(num_elements);
  for (size_t i = 0; i < num_elements; ++i) {
    generated_vector[i] = rng.GenerateValue();
  }
  return generated_vector;
}

}  // namespace random_vector

#endif  // RANDOM_VECTOR_HPP

