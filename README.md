# C++ Utility Functions

<br/>

<details>
  <summary><b>Vector ostream operator<<</b></summary><p>
  
```c++
#ifndef VECTOR_OSTREAM_HPP
#define VECTOR_OSTREAM_HPP

#include <ostream>
#include <string>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i + 1 < v.size()) os << ", ";
    }
    os << "]";
    return os;
}

// Specialization for vector of strings
std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        os << "\"" << v[i] << "\"";
        if (i + 1 < v.size()) os << ", ";
    }
    os << "]";
    return os;
}

#endif  // VECTOR_OSTREAM_HPP

```
Note: index checking method rather than `\b` deletion at end used becuase `\b` does not work for stringstreams.

</p></details><br/>

<br/>

<details>
  <summary><b>Generate random vector</b></summary><p>

```c++
#include <algorithm>
#include <chrono>
#include <functional>
#include <vector>

int CurrentTimeNano() {
    auto current_time = std::chrono::high_resolution_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(current_time).count();
}

std::vector<int> GenerateRandomVector(size_t size, int min_value, int max_value) {
    std::default_random_engine engine(CurrentTimeNano());
    std::uniform_int_distribution<int> distribution(min_value, max_value);
    std::vector<int> generated_vector;
    std::generate_n(std::back_inserter(generated_vector), size, std::bind(distribution, engine));
    return generated_vector;
}
```

Or, using the the `rng.hpp` header in this repository:

```c++
#include "rng.hpp"

std::vector<int> GenerateRandomVector(size_t size, int min_value, int max_value) {
  UniformIntRng<int> rng(min_value, max_value);
  std::vector<int> generated_vector(size);
  for (size_t i = 0; i < size; ++i) {
    generated_vector[i] = rng.GenerateValue();
  }
  return generated_vector;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Simple struct with ostream operator<<</b></summary><p>
  
```c++
#include <ostream>

struct ValueIndexPair {
  int value = -1;
  int index = -1;
};

std::ostream& operator<<(std::ostream& os, const ValueIndexPair& p) {
  os << "(" << p.value << ", " << p.index << ")";
  return os;
}
```

```c++
struct Point {
  double x;
  double y;
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Sort vector of pairs</b></summary><p>
  
```c++
#include <algorithm>
#include <utility>
#include <vector>

// Using explicitly declared lambda argument types (c++11)
std::sort(pair_vector.begin(), pair_vector.end(),
          [](const std::pair<size_t, double>& left, const std::pair<size_t, double>& right) {
	    return left.second < right.second;
          });

// Using auto lambda argument types (c++14)
std::sort(pair_vector.begin(), pair_vector.end(), [](const auto& left, const auto& right) {
	    return left.second < right.second;
          });
```
</p></details><br/>

<br/>

<details>
  <summary><b>Copy/move test class</b></summary><p>
  
```c++
#include <iostream>

class Thing {
  public:
    Thing(int value) : _value(value) {
        std::cout << "Value constructor: " << *this << std::endl;
    }

    Thing(const Thing& other) : _value(other._value) {
        std::cout << "Copy constructor: " << *this << std::endl;
    }

    Thing(Thing&& other) : _value(std::move(other._value)) {
        std::cout << "Move constructor: " << *this << " from " << other << std::endl;
        other._value = 0;
    }

    Thing& operator=(const Thing& other) {
        std::cout << "Copy assignment: " << *this << " = " << other << std::endl;
        _value = other._value;
        return *this;
    }

    Thing& operator=(Thing&& other) {
        std::cout << "Move assignment: " << *this << " = " << other << std::endl;
        _value = std::move(other._value);
        other._value = 0;
        return *this;
    }
    
    ~Thing() {
        std::cout << "Destructor: " << *this << std::endl;
    }

    int GetValue() const { return _value; }

  private:
    int _value;

    friend std::ostream& operator<<(std::ostream& os, const Thing& thing);
};

std::ostream& operator<<(std::ostream& os, const Thing& thing) {
    os << "Thing(" << thing._value << ")";
    return os;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Point test class (with copy and swap)</b></summary><p>
  
```c++
#include <iostream>
#include <utility>

class Point {
 public:
  Point(int x_, int y_) : x_(x_), y_(y_) {
    std::cout << "Value constructor" << std::endl;
  }
  
  Point(const Point& other) : x_(other.x_), y_(other.y_) {
    std::cout << "Copy constructor" << std::endl;
  }
  
  Point(Point&& other) : x_(std::move(other.x_)), y_(std::move(other.y_)) {
    std::cout << "Move constructor" << std::endl;
  }
  
  Point& operator=(Point other) {
    std::cout << "Assignment operator" << std::endl;
    swap(*this, other);
    return *this;
  }
  
  ~Point() {
    std::cout << "Destructor (" << x_ << ", " << y_ << ")" << std::endl;
  }
  
 private:
  int x_;
  int y_;
  
  friend void swap(Point& left, Point& right);
  friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

void swap(Point& left, Point& right) {
  std::swap(left.x_, right.x_);
  std::swap(left.y_, right.y_);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x_ << ", " << p.y_ << ")";
  return os;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Test algorithm correctness (against reference/naive solution)</b></summary><p>
  
```c++
#include "random_vector.hpp"
#include "rng.hpp"

void RunRandomTests(int num_tests, size_t max_array_size, int max_array_value) {
  UniformIntRng<size_t> array_size_rng(0, max_array_size);
  int num_tests_passed = 0;
  for (int i = 0; i < num_tests; ++i) {
    // Check 0- and 1-sized vectors on first two iterations
    size_t num_elements = (i < 2) ? i : array_size_rng.GenerateValue();
    std::vector<int> test_vector(random_vector::GenerateIntVector(num_elements, 0, max_array_value));
    int naive_result = NaiveMaxWater(test_vector);
    int result = MaxWater(test_vector);
    num_tests_passed += (result == naive_result);
    if (result != naive_result) {
      std::cout << "Test failed: " << test_vector << std::endl;
      std::cout << "Naive result: " << naive_result << std::endl;
      std::cout << "Other result: " << result << std::endl;
    }
  }
  std::cout << "Tests passed: " << num_tests_passed << " / " << num_tests << std::endl;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Timer</b></summary><p>
  
See [CppTimer](https://github.com/Apollys/CppTimer) repository.

</p></details><br/>

<br/>

<details>
  <summary><b>RNG</b></summary><p>
  
  [Raw code](https://raw.githubusercontent.com/Apollys/cpp-utils/master/misc/rng.hpp)
  
```c++
#ifndef RNG_HPP
#define RNG_HPP

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

class BernoulliRng {
 private:
  double true_probability_;
  std::default_random_engine engine_;
  std::uniform_real_distribution<double> distribution_;

 public:
  BernoulliRng(double true_probability) : true_probability_(true_probability) {
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::uniform_real_distribution<double>(0, 1);
  }
  
  double GenerateValue() {
    return distribution_(engine_) < true_probability_;
  }
};

#endif  // RNG_HPP

```
</p></details><br/>

<br/>

<details>
  <summary><b>To fixed width string</b></summary><p>
  
```c++
#include <iomanip>
#include <sstream>
#include <string>

// Converts the given value to a string of length at least width by padding on the left with
// left_padding ('0' if unspecified).  Requires ostream insertion operator for T.
template <typename T>
std::string ToFixedWidthString(T value, int width, char left_padding = '0') {
    std::ostringstream oss;
    oss << std::setfill(left_padding) << std::setw(width) << value;
    return oss.str();
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>String trim</b></summary><p>
  
```c++
#include <algorithm>  // std::find_if
#include <cctype>  // std::isspace
#include <string>

// Trim from left, in-place
void Ltrim(std::string& s) {
    // Note: argument to std::isspace should be unsigned char to prevent undefined behavior
    auto not_space = [](unsigned char ch) { return !std::isspace(ch); };
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
}

// Trim from right, in-place
void Rtrim(std::string& s) {
    auto not_space = [](unsigned char ch) { return !std::isspace(ch); };
    // Note: .base() gets forward iterator from reverse
    s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
}

// Trim from both sides, in-place
void Trim(std::string& s) {
    Ltrim(s);
    Rtrim(s);
}

// Trim from left, makes copy
static inline std::string LtrimCopy(std::string s) {
  Ltrim(s);
  return s;
}

// Trim from right, makes copy
static inline std::string RtrimCopy(std::string s) {
  Rtrim(s);
  return s;
}

// Trim from both sides, makes copy
static inline std::string TrimCopy(std::string s) {
  Trim(s);
  return s;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>String split</b></summary><p>
  
```c++
#include <string>
#include <vector>

// Split string by delim, optionally retaining empty strings (caused by consecutive delim chars)
std::vector<std::string> SplitString(const std::string& input_string,
                                     const char delim,
                                     bool retain_empty = false) {
    std::vector<std::string> output_vector;
    size_t start_i = 0;
    size_t found_i = 0;  // dummy initialization to start while loop
    size_t len;
    while (found_i != std::string::npos) {
        found_i = input_string.find(delim, start_i);
        len = (found_i == std::string::npos) ? input_string.length() - start_i : found_i - start_i;
        if (len > 0) {  // non-consecutive delimiters
            output_vector.push_back(input_string.substr(start_i, found_i - start_i));
        } else if (retain_empty) {
            output_vector.push_back(std::string(""));
        }
        start_i = found_i + 1;
    }
    return output_vector;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>String join</b></summary><p>
  
```c++
#include <vector>
#include <string>

// Delimiter as char
std::string JoinStrings(const std::vector<std::string>& input_vector, const char delim) {
  std::string result("");
  for (unsigned int i = 0; i < input_vector.size(); i++) {
    result += input_vector[i];
    if (i + 1 < input_vector.size()) {
      result += delim;
    }
  }
  return result;
}

// Delimiter as string
std::string JoinStrings(const std::vector<std::string>& input_vector, const std::string& delim) {
  std::string result("");
  for (unsigned int i = 0; i < input_vector.size(); i++) {
    result += input_vector[i];
    if (i + 1 < input_vector.size()) {
      result += delim;
    }
  }
  return result;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Linear interpolation (lerp)</b></summary><p>
  
```c++
/*
 * Linear interpolation, given:
 *  - input variable reference points: [t_min, t_max]
 *  - target value of input variable: t
 *  - output values: f(t_min), f(t_max)
 *
 * Returns: f(t) where f is the line passing through (t_min, f(t_min)), (t_max, f(t_max))
 */
double Lerp(double t_min, double t_max, double t, double f_t_min, double f_t_max) {
    double r = (t - t_min) / (t_max - t_min);
    return (1 - r) * f_t_min + r * f_t_max;
}
</p></details><br/>

<br/>

<details>
  <summary><b>Integer power function</b></summary><p>
  
```c++
#include <type_traits>

// Fast int power function, assumes exponent is non-negative
template <typename BaseType, typename ExpType>
BaseType IntPower(BaseType base, ExpType exponent) {
  static_assert(std::is_integral<BaseType>::value, "Integral type required for base");
  static_assert(std::is_integral<ExpType>::value, "Integral type required for exponent");
  BaseType result = 1;
  if (base < 0) {
    result *= (exponent & 1) ? -1 : 1;
    base *= -1;
  }
  while (exponent > 0) {
    if (exponent & 1) {
       result *= base;
    }
    // Now exponent is even
    exponent /= 2;
    base *= base;
  }
  return result;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Float To string given sig figs</b></summary><p>
  
```c++
#include <cmath> // std::log10
#include <type_traits>

// Generate string representing a float rounded to given number of significant figures
template <typename FloatType>
std::string FloatToSigFigs(FloatType value, int sig_figs) {
  static_assert(std::is_floating_point<FloatType>::value, "Float type required");
  int digits_before_decimal = (value > 1) ? std::floor(std::log10(value)) + 1 : 1;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(sig_figs - digits_before_decimal) << value;
  return ss.str();
}  
```
</p></details><br/>

<br/>

<details>
  <summary><b>Scientific notation</b></summary><p>
  
```c++
#include <iomanip> // std::setprecision
#include <sstream>
#include <string>
#include <type_traits>
  
// Returns std::string containg scientific notation with given precision, float version
template <typename FloatType>
typename std::enable_if<std::is_floating_point<FloatType>::value, std::string>::type
SciNotation(FloatType value, int precision = 3) {
  std::stringstream ss;
  ss << std::scientific << std::setprecision(precision) << value;
  return ss.str();
}

// Returns std::string containg scientific notation with given precision, int version
template <typename IntType>
typename std::enable_if<std::is_integral<IntType>::value, std::string>::type
SciNotation(IntType value, int precision = 3) {
  return SciNotation(static_cast<double>(value), precision);
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Human-readable number formatting</b></summary><p>
  
```c++
#include <cmath> // std::log10
#include <cstdlib> // std::to_string
#include <iomanip> // std::setprecision
#include <sstream>
#include <string>
#include <vector>

// Fast int power function, assumes exponent is non-negative
template <typename BaseType, typename ExpType>
BaseType IntPower(BaseType base, ExpType exponent) {
  static_assert(std::is_integral<BaseType>::value, "Integral type required for base");
  static_assert(std::is_integral<ExpType>::value, "Integral type required for exponent");
  BaseType result = 1;
  if (base < 0) {
    result *= (exponent & 1) ? -1 : 1;
    base *= -1;
  }
  while (exponent > 0) {
    if (exponent & 1) {
       result *= base;
    }
    // Now exponent is even
    exponent /= 2;
    base *= base;
  }
  return result;
}

// Generate string representing a float rounded to given number of significant figures
template <typename FloatType>
std::string FloatToSigFigs(FloatType value, int sig_figs) {
  static_assert(std::is_floating_point<FloatType>::value, "Float type required");
  int digits_before_decimal = (value > 1) ? std::floor(std::log10(value)) + 1 : 1;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(sig_figs - digits_before_decimal) << value;
  return ss.str();
}  

template <typename IntType>
std::string IntSciNotation(IntType value, int sig_figs) {
  static_assert(std::is_integral<IntType>::value, "Integral type required");
  std::stringstream ss;
  ss << std::scientific << std::setprecision(sig_figs - 1) << static_cast<double>(value);
  return ss.str();
}

template <typename IntType>
std::string HumanReadableFormat(IntType num, int sig_figs = 3) {
  static_assert(std::is_integral<IntType>::value, "Integral type required");
  std::string result_string("");
  // First, check for negative values
  if (num < 0) {
    num = -num;
    result_string += '-';
  }
  // Next, check number's size
	static const std::vector<char> kSuffixChars{' ', 'K', 'M', 'B'};
  int log_scale = num ? std::floor(std::log10(num)) : 0;
  int k_log_scale = log_scale / 3;
  if (k_log_scale < 1) {
    return result_string + std::to_string(num);
  }
  else if (k_log_scale >= kSuffixChars.size()) {
    return result_string + IntSciNotation(num, sig_figs);
  }
  // Now, put into form {prefix-digits} + {suffix-char}
  double prefix_digits = static_cast<double>(num) / IntPower(1000, k_log_scale);
  result_string += FloatToSigFigs(prefix_digits, sig_figs);
  result_string += kSuffixChars[k_log_scale];
  return result_string;
}
```
</p></details><br/>

<br/>
