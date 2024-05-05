#ifndef _UTILS_RANDOM_RANDOMIZER_H_
#define _UTILS_RANDOM_RANDOMIZER_H_

#include <ctime>
#include <string>
#include <windows.h>

#define UTILS_RANDOMIZER_MIN_DATE {2020, 1,  3, 1,  0,  0,  0,  0  }
#define UTILS_RANDOMIZER_MAX_DATE {2024, 12, 3, 31, 23, 59, 59, 999}

#define UTILS_RANDOMIZER_DEFAULT_MIN_NUMBER 0
#define UTILS_RANDOMIZER_DEFAULT_MAX_NUMBER 100

#define UTILS_RANDOMIZER_DEFAULT_MIN_STRING_SIZE 3
#define UTILS_RANDOMIZER_DEFAULT_MAX_STRING_SIZE 10

#define UTILS_RANDOMIZER_STRING_CHARSET      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define UTILS_RANDOMIZER_STRING_CHARSET_SIZE 62

namespace Utils
{

/****************************
 * RANDOM GENERATOR
 ****************************/

class Randomizer
{
public:
    static Randomizer& instance(unsigned int seed = std::time(NULL));

    bool        getBool();
    SYSTEMTIME  getDate(SYSTEMTIME min_date = UTILS_RANDOMIZER_MIN_DATE, SYSTEMTIME max_date = UTILS_RANDOMIZER_MAX_DATE);
    size_t      get32bNumber(size_t min = UTILS_RANDOMIZER_DEFAULT_MIN_NUMBER, size_t max = UTILS_RANDOMIZER_DEFAULT_MAX_NUMBER);
    std::string getString(size_t min_size = UTILS_RANDOMIZER_DEFAULT_MIN_STRING_SIZE, size_t max_size = UTILS_RANDOMIZER_DEFAULT_MAX_STRING_SIZE);

private:
    Randomizer(unsigned int seed);
    
    // DO NOT IMPLEMENT
    Randomizer(const Randomizer& randomizer);
    Randomizer& operator=(const Randomizer& randomizer);
};

};

#endif
