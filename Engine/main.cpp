#include <iostream>
#include <windows.h>

#include "Win32RenderingWindow.h"
#include "D3D11Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "CubeModel.h"
#include "UserInputInterpreter.h"
#include "MetricsTracker.h"
#include "ObjModel.h"
#include "ApplicationConfig.h"

void logErrorAndNotifyUser(const std::string& log, const std::string& userNotification) {
    std::cerr << log << std::endl;
    std::cerr << userNotification << std::endl;
    OutputDebugString(std::wstring(log.begin(), log.end()).c_str());
    OutputDebugString(std::wstring(userNotification.begin(), userNotification.end()).c_str());

    MessageBox(nullptr,
               std::wstring(userNotification.begin(), userNotification.end()).c_str(),
               L"An Error has occurred",
               MB_OK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
    try {
        ApplicationConfig config;

        int screenWidth;
        int screenHeight;

        if (config.isFullscreenEnabled()) {
            screenWidth = GetSystemMetrics(SM_CXSCREEN);
            screenHeight = GetSystemMetrics(SM_CYSCREEN);
        } else {
            screenWidth = config.getScreenWidth();
            screenHeight = config.getScreenHeight();
        }

        Scene scene;

        ObjModel treeModel = ObjModel::loadFromFile("Resources/Models/lowpolytree.obj");
        SceneObject tree(&treeModel);
        scene.addSceneObject(&tree);

        // CubeModel cubeModel;
        // SceneObject cube(&cubeModel);
        // scene.addSceneObject(&cube);
        // cube.translate(4.0f, 0.0f, 0.0f);

        Camera camera;
        camera.moveStraight(-10.0f);

        Win32RenderingWindow renderingWindow("CMP502", config.isFullscreenEnabled(), screenWidth, screenHeight, hInstance);
        D3D11Renderer d3D11Renderer(renderingWindow.getWindowHandle(),
                                    config.isFullscreenEnabled(),
                                    config.isVsyncEnabled(),
                                    config.getScreenNear(),
                                    config.getScreenHeight(),
                                    screenWidth,
                                    screenHeight,
                                    &scene,
                                    &camera);
        UserInputInterpreter userInput(screenWidth, screenHeight, hInstance, renderingWindow.getWindowHandle());

        renderingWindow.showWindow();

        const float deltaTime = 1.0f / 60.0f; //todo: https://gafferongames.com/post/fix_your_timestep/

        MetricsTracker metricsTracker;
        int fpsLogTracker = 0;

        MSG msg = {};
        while (msg.message != WM_QUIT) {
            if (fpsLogTracker % 300 == 0) {
                std::string log = "FPS: " + std::to_string(metricsTracker.framesPerSecond) + "\n";
                OutputDebugStringW(std::wstring(log.begin(), log.end()).c_str());
                fpsLogTracker = 0;
            }

            userInput.detect();

            if (userInput.isEscapePressed()) {
                renderingWindow.postQuitMessage();
            }

            if (userInput.isWPressed()) {
                camera.moveStraight(4.0f * deltaTime);
            }

            if (userInput.isSPressed()) {
                camera.moveStraight(-4.0f * deltaTime);
            }

            if (userInput.isAPressed()) {
                camera.moveSideways(-4.0f * deltaTime);
            }

            if (userInput.isDPressed()) {
                camera.moveSideways(4.0f * deltaTime);
            }

            if (userInput.isQPressed() * deltaTime) {
                camera.yaw(-0.05f);
            }

            if (userInput.isEPressed() * deltaTime) {
                camera.yaw(0.05f);
            }

            if (userInput.isZPressed() * deltaTime) {
                camera.pitch(-0.05f);
            }

            if (userInput.isCPressed() * deltaTime) {
                camera.pitch(0.05f);
            }

            renderingWindow.pollForMessage(&msg);

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
