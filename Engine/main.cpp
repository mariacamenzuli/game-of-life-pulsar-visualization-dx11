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
        const int screenWidth = 800;
        const int screenHeight = 600;

        Scene scene;

        ObjModel treeModel = ObjModel::loadFromFile("../Engine/Resources/Models/lowpolytree.obj");
        SceneObject tree(&treeModel);
        scene.addSceneObject(&tree);

        // CubeModel cubeModel;
        // SceneObject cube(&cubeModel);
        // scene.addSceneObject(&cube);
        // cube.translate(4.0f, 0.0f, 0.0f);

        Camera camera;
        camera.moveStraight(-10.0f);

        Win32RenderingWindow renderingWindow("CMP502", screenWidth, screenHeight, hInstance);
        D3D11Renderer d3D11Renderer(renderingWindow.getWindowHandle(), screenWidth, screenHeight, &scene, &camera);
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
                camera.moveStraight(0.5f);
            }

            if (userInput.isSPressed()) {
                camera.moveStraight(-0.5f);
            }

            if (userInput.isAPressed()) {
                camera.moveSideways(-0.5f);
            }

            if (userInput.isDPressed()) {
                camera.moveSideways(0.5f);
            }

            if (userInput.isQPressed()) {
                camera.yaw(-0.05f);
            }

            if (userInput.isEPressed()) {
                camera.yaw(0.05f);
            }

            if (userInput.isZPressed()) {
                camera.pitch(-0.05f);
            }

            if (userInput.isCPressed()) {
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
