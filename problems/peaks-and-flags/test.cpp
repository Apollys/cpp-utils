#include <cmath>
#include <algorithm>
#include <iostream>
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

void DebugTest(const std::vector<int>& input_vector) {
  std::cout << "Input vector: " << input_vector << std::endl;
  std::cout << "Peak indices: " << ComputePeakIndices(input_vector) << std::endl;
  std::cout << "Next peak is: " << ComputeNextPeakIndices(input_vector) << std::endl;
  std::cout << std::endl;
}

void TestFlagsPossible(const std::vector<int>& input_vector) {
  std::vector<size_t> next_peak_indices = ComputeNextPeakIndices(input_vector);
  bool possible = true;
  for (int num_flags = 0; possible; ++num_flags) {
    possible = CheckFlagsPossible(num_flags, next_peak_indices);
    std::cout << "Possible with " << num_flags << "? " << possible << std::endl;
  }
  std::cout << std::endl;
}

void TestMaxFlags(const std::vector<int>& input_vector) {
  std::cout << "Max flags: " << MaxFlags(input_vector) << std::endl;
  std::cout << std::endl;
}

int main() {
  std::vector<int> input_vector{0, 2, 3, 2, 4};
  DebugTest(input_vector);
  TestFlagsPossible(input_vector);
  TestMaxFlags(input_vector);
  
  std::vector<int> input_vector2{1, 0, 1, 2, 2, 2, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1};
  DebugTest(input_vector2);
  TestFlagsPossible(input_vector2);
  TestMaxFlags(input_vector2);
  
  std::vector<int> singleton_vector{0};
  DebugTest(singleton_vector);
  TestFlagsPossible(singleton_vector);
  TestMaxFlags(singleton_vector);
  
  std::vector<int> empty_vector;
  DebugTest(empty_vector);
  TestFlagsPossible(empty_vector);
  TestMaxFlags(empty_vector);
  
  return 0;
}
