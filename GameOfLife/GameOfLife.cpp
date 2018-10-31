#include <iostream>
#include <Windows.h>

#include "Win32RenderingWindow.h"
#include "D3D11Renderer.h"
#include "Camera.h"
#include "UserInputReader.h"
#include "MetricsTracker.h"
#include "ApplicationConfig.h"
#include "GameOfLifeSimulator.h"

void logErrorAndNotifyUser(const std::string& log, const std::string& userNotification) {
    std::cerr << log << std::endl;
    std::cerr << userNotification << std::endl;
    OutputDebugString(std::wstring(log.begin(), log.end()).c_str());
    OutputDebugString(L"\n");
    OutputDebugString(std::wstring(userNotification.begin(), userNotification.end()).c_str());
    OutputDebugString(L"\n");

    MessageBox(nullptr,
               std::wstring(userNotification.begin(), userNotification.end()).c_str(),
               L"An Error has occurred",
               MB_OK);
}

void readUserInput(UserInputReader& userInput, Win32RenderingWindow& renderingWindow, D3D11Renderer& renderer, Camera& camera, float deltaTime) {
    userInput.read();

    if (userInput.isEscapePressed()) {
        renderingWindow.postQuitMessage();
    }

    if (userInput.isWPressed()) {
        camera.moveStraight(40.0f * deltaTime);
    }

    if (userInput.isSPressed()) {
        camera.moveStraight(-40.0f * deltaTime);
    }

    if (userInput.isAPressed()) {
        camera.moveSideways(-40.0f * deltaTime);
    }

    if (userInput.isDPressed()) {
        camera.moveSideways(40.0f * deltaTime);
    }

    if (userInput.isQPressed()) {
        camera.yaw(-0.5f * deltaTime);
    }

    if (userInput.isEPressed()) {
        camera.yaw(0.5f * deltaTime);
    }

    if (userInput.isZPressed()) {
        camera.pitch(-0.5f * deltaTime);
    }

    if (userInput.isCPressed()) {
        camera.pitch(0.5f * deltaTime);
    }

    if (userInput.isSpacebarPressed()) {
        renderer.writeCurrentShadowMapToDds();
    }

    int mouseChangeX;
    int mouseChangeY;
    userInput.getMouseLocationChange(mouseChangeX, mouseChangeY);

    camera.yaw(mouseChangeX * 0.15f * deltaTime);
    camera.pitch(mouseChangeY * 0.15f * deltaTime);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
    try {
        ApplicationConfig config;

        int screenWidth;
        int screenHeight;
        const bool isFullScreenEnabled = config.isFullscreenEnabled();

        if (isFullScreenEnabled) {
            screenWidth = GetSystemMetrics(SM_CXSCREEN);
            screenHeight = GetSystemMetrics(SM_CYSCREEN);
        } else {
            screenWidth = config.getScreenWidth();
            screenHeight = config.getScreenHeight();
        }

        Win32RenderingWindow renderingWindow("CMP502", isFullScreenEnabled, screenWidth, screenHeight, hInstance);
        D3D11Renderer d3D11Renderer(renderingWindow.getWindowHandle(),
                                    isFullScreenEnabled,
                                    config.isVsyncEnabled(),
                                    config.getScreenNear(),
                                    config.getScreenHeight(),
                                    screenWidth,
                                    screenHeight);

        GameOfLifeSimulator simulation;
        d3D11Renderer.setScene(&simulation);

        Camera camera;
        d3D11Renderer.setCamera(&camera);

        // set camera initial position
        camera.yaw(-1.5708f);
        camera.moveStraight(-275.0f);
        camera.moveVertical(50.0f);
        camera.pitch(0.261799f);
        UserInputReader userInput(hInstance, renderingWindow.getWindowHandle());

        renderingWindow.showWindow();

        MetricsTracker metricsTracker;
        const float timePerFrame = 1.0f / 60.0f;
        int fpsLogTracker = 0;

        MSG msg = {};
        while (msg.message != WM_QUIT) {
            if (fpsLogTracker % 150 == 0) {
                std::string log = "FPS: " + std::to_string(metricsTracker.framesPerSecond) + ", SUPS: " + std::to_string(metricsTracker.simulationUpdatesPerSecond) + "\n";
                OutputDebugStringW(std::wstring(log.begin(), log.end()).c_str());
                fpsLogTracker = 0;
            }

            metricsTracker.incrementTimeSinceLastSimulationUpdate();
            renderingWindow.pollForMessage(&msg);

            while (metricsTracker.timeSinceLastSimulationUpdate > timePerFrame) {
                metricsTracker.timeSinceLastSimulationUpdate -= timePerFrame;
                readUserInput(userInput, renderingWindow, d3D11Renderer, camera, timePerFrame);
                simulation.update(timePerFrame);
                metricsTracker.newSimulationUpdate();
            }

            d3D11Renderer.renderFrame();

            metricsTracker.newFrameRendered();
            fpsLogTracker++;
        }
    } catch (const D3D11RendererException& e) {
        logErrorAndNotifyUser(e.what(), "Failed to initialize DirectX. Error code " + std::to_string(e.getErrorCode()));
        return EXIT_FAILURE;
    } catch (const Win32RenderingWindowException& e) {
        logErrorAndNotifyUser(e.what(), "A windows application error has occurred. Error code " + std::to_string(e.getErrorCode()));
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        logErrorAndNotifyUser(e.what(), "An unknown error has occurred.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
