#include "utils/random/Randomizer.h"

#include <cstdlib>
#include <cstring>
#include <time.h>

#include "utils/Time.h"

namespace Utils
{

/****************************
 * RANDOM GENERATOR
 ****************************/
Randomizer& Randomizer::instance(unsigned int seed)
{
    static Randomizer randomizer(seed);
    return randomizer;
}

Randomizer::Randomizer(unsigned int seed)
{
    std::srand(seed);
}

bool Randomizer::getBool()
{
    return static_cast<bool>(std::rand() % 2);
}

SYSTEMTIME Randomizer::getDate(SYSTEMTIME min_date, SYSTEMTIME max_date)
{
    if (min_date > max_date)
    {
        SYSTEMTIME tmp = min_date;
        min_date       = max_date;
        max_date       = tmp;
    }

    if (min_date == max_date) return min_date;

    time_t min_date_ms = TimeConverter().systemTimeToMilliseconds(min_date);
    time_t max_date_ms = TimeConverter().systemTimeToMilliseconds(max_date);

    return TimeConverter().millisecondsToSystemTime(getNumber(min_date_ms, max_date_ms));
}

size_t Randomizer::getNumber(size_t min, size_t max)
{
    if (min > RAND_MAX) min = RAND_MAX;
    if (max > RAND_MAX) max = RAND_MAX;

    if (min > max)
    {
        size_t tmp = min;
        min        = max;
        max        = tmp;
    }

    if (min == max) return min;
    else            return static_cast<size_t>(std::rand() % (max - min) + min);
}

std::string Randomizer::getString(size_t min_size, size_t max_size)
{
    size_t      size = getNumber(min_size, max_size);
    std::string text(size, ' ');

    for (size_t i = 0; i < size; ++i) text[i] = UTILS_RANDOMIZER_STRING_CHARSET[getNumber(0, UTILS_RANDOMIZER_STRING_CHARSET_SIZE)];
    return text;
}

};
