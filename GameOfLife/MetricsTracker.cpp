#include "MetricsTracker.h"

MetricsTracker::MetricsTracker(): framesPerSecond(0), frameCounter(0) {
    fpsCountStartTime = std::chrono::system_clock::now();
}

MetricsTracker::~MetricsTracker() = default;

void MetricsTracker::newFrameRendered() {
    const auto timeNow = std::chrono::system_clock::now();
    const auto timeElapsedInMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - fpsCountStartTime).count();

    if (toSeconds(timeElapsedInMilliseconds) >= 1.0f) {
        framesPerSecond = frameCounter;
        frameCounter = 0;
        fpsCountStartTime = std::chrono::system_clock::now();
    }

    ++frameCounter;
}

float MetricsTracker::toSeconds(long milliseconds) {
    return milliseconds / 1000.0f;
}
