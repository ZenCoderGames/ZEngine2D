#include <iostream>
#include <string>

#define ASSERT(condition, errorStr) \
    if(condition) { std::cout << "ERROR: " << errorStr << " (File: " << __FILE__ << ": " << __LINE__ << " [fn: " << __FUNCTION__ << "])\n"; abort(); }

#define STR_CONCAT(str1, str2) \
    std::string(str1) + std::string(str2)