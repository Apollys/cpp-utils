#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << "[";
  for (size_t i = 0; i < v.size(); i++) {
    os << v[i];
    if (i + 1 < v.size()) {
      os << ", ";
    }
  }
  os << (v.size() ? "]" : " ]");
  return os;
}

int CurrentTimeNano() {
  auto current_time = std::chrono::high_resolution_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(current_time).count();
}

template <typename IntType>
IntType UniformIntRng(IntType min_value, IntType max_value) {
  static_assert(std::is_integral<IntType>::value, "Parameters must be of integral type");
  static std::default_random_engine engine(CurrentTimeNano());
  std::uniform_int_distribution<int> distribution(min_value, max_value);
  return distribution(engine);
}

// Basic algorithm, but runs in O(num_elements) time/space, to build vector
// Can use a map instead to run in O(num_samples) time & space
std::vector<int> RandomSampleNaive(int num_samples, int num_elements) {
  std::vector<int> permutation;
  permutation.reserve(num_elements);
  for (int i = 0; i < num_elements; ++i) {
    permutation.push_back(i);
  }
  for (int i = 0; i < num_samples; ++i) {
    int random_index = UniformIntRng(i, num_elements-1);
    std::swap(permutation[random_index], permutation[i]);
  }
  return std::vector<int>(permutation.begin(), permutation.begin() + num_samples);
}

// Random sampling without replacement:
// Optimal sampling algorithm if you want k samples from n elements
// without replacement is given by first performing the first k iterations
// of the permutation-generating algorithm, then returning those first k values
// Time: O(k), space: O(k)
std::vector<int> RandomSample(int num_samples, int num_elements) {
  std::unordered_map<int, int> permutation_map;
  for (int i = 0; i < num_samples; ++i) {
    int i_value = permutation_map.count(i) ? permutation_map[i] : i;
    int random_index = UniformIntRng(i, num_elements-1);
    int random_value = permutation_map.count(random_index) ?
                       permutation_map[random_index] : random_index;
    permutation_map[i] = random_value;
    permutation_map[random_index] = i_value;
  }
  std::vector<int> sample_results;
  for (int i = 0; i < num_samples; i++) {
    sample_results.push_back(permutation_map[i]);
  }
  return sample_results;
}

int main() {
  const int kNumElements = 10;
  for (int num_samples = 1; num_samples <= kNumElements; ++num_samples) {
    std::cout << RandomSample(num_samples, kNumElements) << std::endl;
  }
  return 0;
}
