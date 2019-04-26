#include <algorithm> // std::find_if
#include <cctype> // std::isspace
#include <string>

// Trim from left, in-place
static inline void Ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
    return !std::isspace(ch);
  }));
}

// Trim from right, in-place
static inline void Rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
    return !std::isspace(ch);
  }).base(), s.end());  // .base() gets forward iterator from reverse
}

// Trim from both sides, in-place
static inline void Trim(std::string &s) {
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

