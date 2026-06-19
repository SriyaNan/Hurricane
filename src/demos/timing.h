#ifndef HURRICANE_DEMOS_TIMING_H
#define HURRICANE_DEMOS_TIMING_H

class TimingData
{
public:
    unsigned lastFrameTimestamp;
    unsigned lastFrameDuration;

    static TimingData& get();
    void update();

private:
    TimingData();
};

#endif
