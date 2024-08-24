// This is directly stolen from a very bad, no good old project.
// The only modification I made was changing from lltoa to sprintf
// There are weird decisions made in here. I don't know why I made them.

#pragma once

#include <stdlib.h>
#include <chrono>
#include <string>

template <
    class result_t = std::chrono::microseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::microseconds>

auto since(std::chrono::time_point<clock_t, duration_t> const &start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

const int64_t monthLengthInMicroseconds = 2629746000000;
// 30.436875 days

// takes a long long, and returns something like "1 months, 5 days, 17 hours, 28 minutes, 34 seconds, 690 miliseconds, and 125 microseconds"
// accurate for longer times, but may have weirdness around 1 mo, because the month counter assumes a month is ~30.44 days, but the day counter assumes it's 31.
std::string humanFriendlyLongTime(int64_t time)
{
    int64_t timeSpan = time;

    std::string result("");

    char number[10];
    sprintf(number, "%ld", timeSpan % 1000);
    result.append(number);
    result.append(" microseconds");

    if (timeSpan < 1000)
        return result;

    timeSpan = (timeSpan - (timeSpan % 1000)) / 1000;

    result.insert(0, " miliseconds, and ");
    sprintf(number, "%ld", timeSpan % 1000);
    result.insert(0, number);

    if (timeSpan < 1000)
        return result;

    timeSpan = (timeSpan - (timeSpan % 1000)) / 1000;

    result.insert(0, " seconds, ");
    sprintf(number, "%ld", timeSpan % 60);
    result.insert(0, number);

    if (timeSpan < 60)
        return result;

    timeSpan = (timeSpan - (timeSpan % 60)) / 60;

    result.insert(0, " minutes, ");
    sprintf(number, "%ld", timeSpan % 60);
    result.insert(0, number);

    if (timeSpan < 60)
        return result;

    timeSpan = (timeSpan - (timeSpan % 60)) / 60;

    result.insert(0, " hours, ");
    sprintf(number, "%ld", timeSpan % 24);
    result.insert(0, number);

    if (timeSpan < 24)
        return result;

    timeSpan = (timeSpan - (timeSpan % 24)) / 24;

    result.insert(0, " days, ");
    sprintf(number, "%ld", timeSpan % 31);
    result.insert(0, number);

    if (time < monthLengthInMicroseconds)
        return result;

    timeSpan = (time - (time % monthLengthInMicroseconds)) / monthLengthInMicroseconds;

    result.insert(0, " months, ");
    sprintf(number, "%ld", timeSpan % 12);
    result.insert(0, number);

    if (timeSpan < 12)
        return result;

    timeSpan = (timeSpan - (timeSpan % 12)) / 12;

    result.insert(0, " years, ");
    sprintf(number, "%ld", timeSpan);
    result.insert(0, number);

    return result;
}

// takes a long long, and returns something like "1 months, 5 days, 17 hours, 28 minutes, 34 seconds, 690 miliseconds, and 125 microseconds"
// accurate for shorter times, but may drift at long lengths, because it doesn't account for leap years. Assumes a month is 30 days
std::string humanFriendlyTime(int64_t timeSpan)
{
    std::string result("");

    char number[10];
    sprintf(number, "%ld", timeSpan % 1000);
    result.append(number);
    result.append(" microseconds");

    if (timeSpan < 1000)
        return result;

    timeSpan = (timeSpan - (timeSpan % 1000)) / 1000;

    result.insert(0, " miliseconds, and ");
    sprintf(number, "%ld", timeSpan % 1000);
    result.insert(0, number);

    if (timeSpan < 1000)
        return result;

    timeSpan = (timeSpan - (timeSpan % 1000)) / 1000;

    result.insert(0, " seconds, ");
    sprintf(number, "%ld", timeSpan % 60);
    result.insert(0, number);
    if (timeSpan < 60)
        return result;

    timeSpan = (timeSpan - (timeSpan % 60)) / 60;

    result.insert(0, " minutes, ");
    sprintf(number, "%ld", timeSpan % 60);
    result.insert(0, number);

    if (timeSpan < 60)
        return result;

    timeSpan = (timeSpan - (timeSpan % 60)) / 60;

    result.insert(0, " hours, ");
    sprintf(number, "%ld", timeSpan % 24);
    result.insert(0, number);

    if (timeSpan < 24)
        return result;

    timeSpan = (timeSpan - (timeSpan % 24)) / 24;

    result.insert(0, " days, ");
    sprintf(number, "%ld", timeSpan % 30);
    result.insert(0, number);

    if (timeSpan < 30)
        return result;

    timeSpan = (timeSpan - (timeSpan % 30)) / 30;

    result.insert(0, " months, ");
    sprintf(number, "%ld", timeSpan % 12);
    result.insert(0, number);

    if (timeSpan < 12)
        return result;

    timeSpan = (timeSpan - (timeSpan % 12)) / 12;

    result.insert(0, " years, ");
    sprintf(number, "%ld", timeSpan);
    result.insert(0, number);

    return result;
}