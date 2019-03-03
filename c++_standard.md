## Print C++ Standard

```c++
/* 
 * Program to print the c++ standard the compiler used to during compilation.
 * This program is intended to be used as a quick convenient check, NOT as a
 * guarantee of feature availability.  Not all compilers have the __cplusplus
 * macro defined correctly (for example, gcc before version 4.7.0), and not
 * all compilers which claim to support a specific standard actually support
 * 100% of that standard's features and adhere to 100% of its requirements.
 */
 
#include <iostream>

const char* CppStandard() {
  switch (__cplusplus) {
    case 1: return "pre-c++98";
    case 199711L: return "c++98";
    case 201103L: return "c++11";
    case 201402L: return "c++14";
    case 201703L: return "c++17";
    default: return "unknown";
  }
}

int main() {
  std::cout << "Program compiled using standard: " << CppStandard() << std::endl;
  
  return 0;
}
```
