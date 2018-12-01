#include <cmath>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <map>
#include <vector>

#include "timer.hpp"

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

std::vector<size_t> ComputePeakIndices(const std::vector<int>& input_vector) {
  std::vector<size_t> peak_indices;
  for (size_t i = 0; i < input_vector.size(); ++i) {
    bool greater_than_prev = (i == 0) || (input_vector[i] > input_vector[i - 1]);
    bool greater_than_next = (i + 1 == input_vector.size()) || (input_vector[i] > input_vector[i + 1]);
    if (greater_than_prev && greater_than_next) {
      peak_indices.push_back(i);
    }
  }
  return peak_indices;
}

std::vector<size_t> ComputeNextPeakIndices(const std::vector<int>& input_vector) {
  std::vector<size_t> peak_indices = ComputePeakIndices(input_vector);
  std::vector<size_t> next_peak_indices;
  for (size_t peak_i : peak_indices) {
    next_peak_indices.insert(next_peak_indices.end(), peak_i - next_peak_indices.size() + 1, peak_i);
  }
  return next_peak_indices;
}

// O(sqrt(original vector length))
bool CheckFlagsPossible(int num_flags, const std::vector<size_t>& next_peak_indices) {
  if (num_flags == 0) {
    return true;
  }
  if (next_peak_indices.empty()) {
    return false;
  }
  size_t current_index = next_peak_indices[0];
  int flags_placed = 1;
  while (flags_placed < num_flags)  {
    current_index += num_flags; // must have at least num_flags distance between flags
    if (current_index + 1 > next_peak_indices.size()) {
      return false;
    }
    current_index = next_peak_indices[current_index];
    ++flags_placed;
  }
  return true;
}

int BinarySearchNumFlags(int min_flags, int max_flags, const std::vector<size_t>& next_peak_indices) {
  if (max_flags > min_flags) {
    int lower_max_flags = min_flags + (max_flags - min_flags)/2;
    return std::max(BinarySearchNumFlags(min_flags, lower_max_flags, next_peak_indices),
                    BinarySearchNumFlags(lower_max_flags + 1, max_flags, next_peak_indices));
  }
  return CheckFlagsPossible(min_flags, next_peak_indices) ? min_flags : -1;
}

// O(log n * sqrt(n)) + O(n) = O(n)
int MaxFlags(const std::vector<int>& input_vector) {
  std::vector<size_t> next_peak_indices = ComputeNextPeakIndices(input_vector);
  int max_flags = std::ceil(std::sqrt(static_cast<int>(input_vector.size())));
  return BinarySearchNumFlags(0, max_flags, next_peak_indices);
}

int CurrentTimeNano() {
  auto current_time = std::chrono::high_resolution_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(current_time).count();
}

int main() {
  Timer timer;
  std::map<size_t, double> runtime_stats;
  static std::default_random_engine engine(CurrentTimeNano());
  std::uniform_int_distribution<int> distribution(0, 2);
  const size_t kMinSize = 1000;
  const size_t kMaxSize = 10000000;
  size_t size = kMinSize;
  int dummy_accumulator;
  while (size <= kMaxSize) {
    std::vector<int> test_vector(size);
    for (size_t i = 0; i < test_vector.size(); ++i) {
      test_vector[i] = distribution(engine);
    }
    timer.Reset();
    int result = MaxFlags(test_vector);
    double runtime = timer.GetSeconds();
    runtime_stats[size] = runtime;
    dummy_accumulator += result;
    size = static_cast<size_t>(static_cast<double>(size) * 1.2);
  }
  
  for (const auto& item : runtime_stats) {
    size_t size = item.first;
    double runtime = item.second;
    std::cout << size << " : " << runtime << std::endl;
  }
  
  std::cout << (dummy_accumulator & 1 ? " " : "") << std::endl; 
  
  return 0;
}
