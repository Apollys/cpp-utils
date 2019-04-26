#include <string>
#include <vector>

std::vector<std::string> SplitString(std::string input_string, const char delim,
                                     bool retain_empty = false) {
  std::vector<std::string> results;
  size_t start_i = 0;
  size_t found_i = 0; // dummy initialization to start while loop
  size_t len;
  while (found_i != std::string::npos) {
    found_i = input_string.find(delim, start_i);
    len = (found_i == std::string::npos) ? input_string.length() - start_i : found_i - start_i;
    if (len > 0) { // non-consecutive delimiters
      results.push_back(input_string.substr(start_i, found_i - start_i));
    }
    else if (retain_empty) {
      results.push_back(std::string(""));
    }
    start_i = found_i + 1;
  }
  return results;
}

