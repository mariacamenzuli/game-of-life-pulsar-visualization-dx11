#include "MetricsTracker.h"

MetricsTracker::MetricsTracker(): framesPerSecond(0), simulationUpdatesPerSecond(0), timeSinceLastSimulationUpdate(0), frameCounter(0), simulationUpdateCounter(0) {
    fpsCountStartTime = std::chrono::system_clock::now();
    simulationUpdateCountStartTime = std::chrono::system_clock::now();

    simulationSynchTimer = std::chrono::system_clock::now();
}

MetricsTracker::~MetricsTracker() = default;

void MetricsTracker::newFrameRendered() {
    const auto timeNow = std::chrono::system_clock::now();
    const auto timeElapsedInMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - fpsCountStartTime).count();

    if (toSeconds(timeElapsedInMilliseconds) >= 1.0f) {
        framesPerSecond = frameCounter;
        frameCounter = 0;
        fpsCountStartTime = timeNow;
    }

    ++frameCounter;
}

void MetricsTracker::newSimulationUpdate() {
    const auto timeNow = std::chrono::system_clock::now();
    const auto timeElapsedInMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - simulationUpdateCountStartTime).count();

    if (toSeconds(timeElapsedInMilliseconds) >= 1.0f) {
        simulationUpdatesPerSecond = simulationUpdateCounter;
        simulationUpdateCounter = 0;
        simulationUpdateCountStartTime = timeNow;
    }

    ++simulationUpdateCounter;
}

void MetricsTracker::incrementTimeSinceLastSimulationUpdate() {
    const auto timeNow = std::chrono::system_clock::now();
    timeSinceLastSimulationUpdate += toSeconds(std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - simulationSynchTimer).count());
    simulationSynchTimer = timeNow;
}

float MetricsTracker::toSeconds(long milliseconds) {
    return milliseconds / 1000.0f;
}
