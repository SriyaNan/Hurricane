#include "timing.h"

#include <chrono>

namespace {
    unsigned currentMilliseconds()
    {
        using Clock = std::chrono::steady_clock;
        static const Clock::time_point start = Clock::now();
        return static_cast<unsigned>(
            std::chrono::duration_cast<std::chrono::milliseconds>(
                Clock::now() - start).count());
    }
}

TimingData::TimingData()
    : lastFrameTimestamp(currentMilliseconds()),
      lastFrameDuration(0)
{
}

TimingData& TimingData::get()
{
    static TimingData data;
    return data;
}

void TimingData::update()
{
    unsigned currentFrameTimestamp = currentMilliseconds();
    lastFrameDuration = currentFrameTimestamp - lastFrameTimestamp;
    lastFrameTimestamp = currentFrameTimestamp;
}
