#include "utils/random/Randomizer.h"

#include <cstdlib>
#include <cstring>
#include <time.h>

#include "utils/Time.h"

#define LOW_MASK_64_BITS  0x00000000FFFFFFFF
#define HIGH_MASK_64_BITS 0xFFFFFFFF00000000
#define SHIFT_32_BITS     32
#define MAX_64_BITS       static_cast<size_t>(-1)

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
    time_t diff_date   = max_date_ms - min_date_ms;

    time_t random_date = min_date_ms;
    if (diff_date <= RAND_MAX)
        random_date += get32bNumber(0, diff_date);
    else
    {
        size_t tmp_random_date = (get32bNumber(0, (diff_date >> SHIFT_32_BITS) & LOW_MASK_64_BITS) << SHIFT_32_BITS) & HIGH_MASK_64_BITS;
        random_date           += tmp_random_date;
        random_date           += get32bNumber(0, diff_date & LOW_MASK_64_BITS);
    }
    
    return TimeConverter().millisecondsToSystemTime(random_date);
}

size_t Randomizer::get32bNumber(size_t min, size_t max)
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
    else            return static_cast<size_t>(std::rand() % (max - min + 1) + min);
}

std::string Randomizer::getString(size_t min_size, size_t max_size)
{
    size_t      size = get32bNumber(min_size, max_size);
    std::string text(size, ' ');

    for (size_t i = 0; i < size; ++i) text[i] = UTILS_RANDOMIZER_STRING_CHARSET[get32bNumber(0, UTILS_RANDOMIZER_STRING_CHARSET_SIZE)];
    return text;
}

};
