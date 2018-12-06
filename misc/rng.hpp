#include <chrono>
#include <random>

namespace rng_util {

int CurrentTimeNano() {
  auto current_time = std::chrono::high_resolution_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(current_time).count();
}

} // namespace rng_util

template <typename IntType>
class UniformIntRng {
 private:
  IntType min_value_;
  IntType max_value_;
  std::default_random_engine engine_;
  std::uniform_int_distribution<IntType> distribution_;

 public:
  UniformIntRng(IntType min_value, IntType max_value) : 
      min_value_(min_value), max_value_(max_value) {
    static_assert(std::is_integral<IntType>::value, "Requires integral type");
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::uniform_int_distribution<IntType>(min_value_, max_value_);
  }
  
  IntType GenerateValue() {
    return distribution_(engine_);
  }
};

template <typename FloatType>
class UniformFloatRng {
 private:
  FloatType min_value_;
  FloatType max_value_;
  std::default_random_engine engine_;
  std::uniform_real_distribution<FloatType> distribution_;

 public:
  UniformFloatRng(FloatType min_value, FloatType max_value) : 
      min_value_(min_value), max_value_(max_value) {
    static_assert(std::is_floating_point<FloatType>::value, "Requires floating point type");
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::uniform_real_distribution<FloatType>(min_value_, max_value_);
  }
  
  FloatType GenerateValue() {
    return distribution_(engine_);
  }
};

template <typename FloatType>
class NormalFloatRng {
 private:
  FloatType mean_;
  FloatType standard_deviation_;
  std::default_random_engine engine_;
  std::normal_distribution<FloatType> distribution_;

 public:
  NormalFloatRng(FloatType mean, FloatType standard_deviation) : 
      mean_(mean), standard_deviation_(standard_deviation) {
    static_assert(std::is_floating_point<FloatType>::value, "Requires floating point type");
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::normal_distribution<FloatType>(mean_, standard_deviation_);
  }
  
  FloatType GenerateValue() {
    return distribution_(engine_);
  }
};

template <typename IntType>
class NormalIntRng {
 private:
  double mean_;
  double standard_deviation_;
  std::default_random_engine engine_;
  std::normal_distribution<double> distribution_;

 public:
  NormalIntRng(double mean, double standard_deviation) : 
      mean_(mean), standard_deviation_(standard_deviation) {
    static_assert(std::is_integral<IntType>::value, "Template type must be integral");
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::normal_distribution<double>(mean_, standard_deviation_);
  }
  
  IntType GenerateValue() {
    return static_cast<IntType>(distribution_(engine_) + 0.5);
  }
};

