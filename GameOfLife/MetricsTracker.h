#pragma once

#include <chrono>

class MetricsTracker {
public:
    MetricsTracker();
    ~MetricsTracker();

    unsigned int framesPerSecond;

    void newFrameRendered();

private:
    unsigned int frameCounter;
    std::chrono::time_point<std::chrono::system_clock> fpsCountStartTime;

    static float toSeconds(long milliseconds);
};
