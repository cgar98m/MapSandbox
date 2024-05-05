#ifndef _UTILS_TIME_H_
#define _UTILS_TIME_H_

#include <cstdint>
#include <ctime>
#include <windows.h>

namespace Utils
{

/****************************
 * TIME UTILITIES
 ****************************/

/*
 * TIME CONVERSION
 */
class TimeConverter
{
public:
    TimeConverter();

    time_t     systemTimeToMilliseconds(SYSTEMTIME systemTime);
    SYSTEMTIME millisecondsToSystemTime(time_t milliseconds);

private:
    time_t   fileTimeToMilliseconds(FILETIME fileTime);
    FILETIME millisecondsToFileTime(time_t milliseconds);
};

/*
 * SYSTEMTIME UTILS
 */
bool operator==(const SYSTEMTIME& lhs, const SYSTEMTIME& rhs);
bool operator< (const SYSTEMTIME& lhs, const SYSTEMTIME& rhs);
bool operator<=(const SYSTEMTIME& lhs, const SYSTEMTIME& rhs);
bool operator> (const SYSTEMTIME& lhs, const SYSTEMTIME& rhs);
bool operator>=(const SYSTEMTIME& lhs, const SYSTEMTIME& rhs);

/*
 * SYSTEMTIME x MILLISECONDS UTILS
 */
bool operator==(const SYSTEMTIME& lhs, const time_t& rhs);
bool operator< (const SYSTEMTIME& lhs, const time_t& rhs);
bool operator<=(const SYSTEMTIME& lhs, const time_t& rhs);
bool operator> (const SYSTEMTIME& lhs, const time_t& rhs);
bool operator>=(const SYSTEMTIME& lhs, const time_t& rhs);

/*
 * MILLISECONDS x SYSTEMTIME UTILS
 */
bool operator==(const time_t& lhs, const SYSTEMTIME& rhs);
bool operator< (const time_t& lhs, const SYSTEMTIME& rhs);
bool operator<=(const time_t& lhs, const SYSTEMTIME& rhs);
bool operator> (const time_t& lhs, const SYSTEMTIME& rhs);
bool operator>=(const time_t& lhs, const SYSTEMTIME& rhs);

};

#endif
