#include "utils/Time.h"

#define LOW_MASK_64_BITS  0x00000000FFFFFFFF
#define HIGH_MASK_64_BITS 0xFFFFFFFF00000000
#define SHIFT_32_BITS     32

namespace Utils
{

/****************************
 * TIME UTILITIES
 ****************************/

/*
 * TIME CONVERSION
 */
TimeConverter::TimeConverter()
{
}

time_t TimeConverter::systemTimeToMilliseconds(SYSTEMTIME systemTime)
{
    FILETIME fileTime;

    if (!SystemTimeToFileTime(&systemTime, &fileTime)) return 0;
    
    return fileTimeToMilliseconds(fileTime);
}

SYSTEMTIME TimeConverter::millisecondsToSystemTime(time_t milliseconds)
{
    FILETIME   fileTime;
    SYSTEMTIME systemTime;

    fileTime = millisecondsToFileTime(milliseconds);
    if (!FileTimeToSystemTime(&fileTime, &systemTime)) ZeroMemory(&systemTime, sizeof(systemTime));

    return systemTime;
}

time_t TimeConverter::fileTimeToMilliseconds(FILETIME fileTime)
{
    uint64_t tmp;

    tmp  = (static_cast<uint64_t>(fileTime.dwHighDateTime) << SHIFT_32_BITS) & HIGH_MASK_64_BITS;
    tmp |= (static_cast<uint64_t>(fileTime.dwLowDateTime) & LOW_MASK_64_BITS);

    return static_cast<time_t>((tmp - 116444736000000000) / 10000000);
}

FILETIME TimeConverter::millisecondsToFileTime(time_t milliseconds)
{
    FILETIME fileTime;
    uint64_t tmp;

    tmp = static_cast<uint64_t>(milliseconds) * 10000000 + 116444736000000000;

    fileTime.dwLowDateTime  = static_cast<DWORD>(tmp & LOW_MASK_64_BITS);
    fileTime.dwHighDateTime = static_cast<DWORD>((tmp >> SHIFT_32_BITS) & LOW_MASK_64_BITS);

    return fileTime;
}

/*
 * SYSTEMTIME UTILS
 */
bool operator==(const SYSTEMTIME& lhs, const SYSTEMTIME& rhs)
{
    return operator<(lhs, rhs) && operator>(lhs, rhs);
}

bool operator<(const SYSTEMTIME& lhs, const SYSTEMTIME& rhs)
{
    return (lhs.wYear  < rhs.wYear)
        || (lhs.wMonth < rhs.wMonth)
        || (lhs.wDay < rhs.wDay)
        || (lhs.wHour < rhs.wHour)
        || (lhs.wMinute < rhs.wMinute)
        || (lhs.wSecond < rhs.wSecond)
        || (lhs.wMilliseconds < rhs.wMilliseconds);
}

bool operator<=(const SYSTEMTIME& lhs, const SYSTEMTIME& rhs)
{
    return operator<(lhs, rhs) || operator==(lhs, rhs);
}

bool operator>(const SYSTEMTIME& lhs, const SYSTEMTIME& rhs)
{
    return operator<(rhs, lhs);
}

bool operator>=(const SYSTEMTIME& lhs, const SYSTEMTIME& rhs)
{
    return operator>(lhs, rhs) || operator==(lhs, rhs);
}

/*
 * SYSTEMTIME x MILLISECONDS UTILS
 */
bool operator==(const SYSTEMTIME& lhs, const time_t& rhs)
{
    return TimeConverter().systemTimeToMilliseconds(lhs) == rhs;
}

bool operator<(const SYSTEMTIME& lhs, const time_t& rhs)
{
    return TimeConverter().systemTimeToMilliseconds(lhs) < rhs;
}

bool operator<=(const SYSTEMTIME& lhs, const time_t& rhs)
{
    return TimeConverter().systemTimeToMilliseconds(lhs) <= rhs;
}

bool operator>(const SYSTEMTIME& lhs, const time_t& rhs)
{
    return TimeConverter().systemTimeToMilliseconds(lhs) > rhs;
}

bool operator>=(const SYSTEMTIME& lhs, const time_t& rhs)
{
    return TimeConverter().systemTimeToMilliseconds(lhs) >= rhs;
}

/*
 * MILLISECONDS x SYSTEMTIME UTILS
 */
bool operator==(const time_t& lhs, const SYSTEMTIME& rhs)
{
    return lhs == TimeConverter().systemTimeToMilliseconds(rhs);
}

bool operator<(const time_t& lhs, const SYSTEMTIME& rhs)
{
    return lhs < TimeConverter().systemTimeToMilliseconds(rhs);
}

bool operator<=(const time_t& lhs, const SYSTEMTIME& rhs)
{
    return lhs <= TimeConverter().systemTimeToMilliseconds(rhs);
}

bool operator>(const time_t& lhs, const SYSTEMTIME& rhs)
{
    return lhs > TimeConverter().systemTimeToMilliseconds(rhs);
}

bool operator>=(const time_t& lhs, const SYSTEMTIME& rhs)
{
    return lhs >= TimeConverter().systemTimeToMilliseconds(rhs);
}

};
