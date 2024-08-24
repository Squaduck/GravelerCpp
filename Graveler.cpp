#include <iostream>
#include "timestuff.h"
#include <chrono>
#include <thread>
#include <random>
#include <future>
#include <bit>

void roll_rounds(long count, std::promise<uint8_t> &&promise)
{
    std::random_device rd; // secure, but slow random to seed faster random
    std::default_random_engine randEngine(rd());
    std::uniform_int_distribution<uint64_t> randDistribution(0,UINT64_MAX);

    uint8_t localTotal;
    uint8_t bestLocalTotal = 0;

    for(int x = 0; x < count; x++)
    {
        localTotal = 0;
        for (uint32_t i = 0; i < 231 / 64; i++)
        {
            localTotal += std::__popcount(randDistribution(randEngine) & randDistribution(randEngine));
        }
        localTotal += std::__popcount((randDistribution(randEngine) & randDistribution(randEngine)) & 0b111111111111111111111111111111111111111);
        if (localTotal > bestLocalTotal)
            bestLocalTotal = localTotal;
    }

    promise.set_value(bestLocalTotal);
}

uint8_t multithreadRoll_rounds(uint32_t count)
{
    unsigned int threadCount = std::thread::hardware_concurrency() >= count ? count : std::thread::hardware_concurrency(); // Only use all threads if there are more than the count

    std::thread threads[threadCount];
    std::promise<uint8_t> promises[threadCount];
    std::future<uint8_t> futures[threadCount];

    uint32_t leftover = count % threadCount;
    uint32_t baseThreadCount = (count - leftover) / threadCount;

    // eg count 13 threads 5, base would be 2
    // there will be three left over that should be given to first three threads

    for (uint32_t i = 0; i < threadCount; i++)
    {
        futures[i] = promises[i].get_future();

        if (i >= leftover)
            threads[i] = std::thread(roll_rounds, baseThreadCount, std::move(promises[i]));
        else
            threads[i] = std::thread(roll_rounds, baseThreadCount + 1, std::move(promises[i]));
    }

    uint8_t bestTotal = 0;

    for (uint32_t i = 0; i < threadCount; i++)
    {
        threads[i].join();
        uint8_t val = futures[i].get();
        if (val > bestTotal)
            bestTotal = val;
    }

    return bestTotal;
}

int main(int argc, char *argv[])
{
    auto startTime = std::chrono::steady_clock::now();
    uint8_t result = multithreadRoll_rounds(100000000);
    auto elapsedTime = since(startTime);
    printf("Highest number of 1s rolled in %d rounds: %d\nRan in %s\n", 100000000, result, humanFriendlyTime(elapsedTime.count()).c_str());
}