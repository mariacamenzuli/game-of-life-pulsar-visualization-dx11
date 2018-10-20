#pragma once
#include <string>

class ApplicationConfig {
public:
    ApplicationConfig();
    ~ApplicationConfig();

    bool isFullscreenEnabled();
    int getScreenHeight();
    int getScreenWidth();
    bool isVsyncEnabled();
    float getScreenDepth();
    float getScreenNear();

private:
    bool fullscreenEnabled = false;
    int screenWidth = 800;
    int screenHeight = 600;
    bool vsyncEnabled = true;
    float screenDepth = 1000.0f;
    float screenNear = 0.1f;

    bool readBoolean(const std::string& property);
};

