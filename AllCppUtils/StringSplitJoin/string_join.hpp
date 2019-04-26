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
