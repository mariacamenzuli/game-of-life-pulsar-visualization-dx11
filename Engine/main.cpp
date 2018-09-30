#include <iostream>
#include <windows.h>

#include "Win32RenderingWindow.h"
#include "D3D11Renderer.h"
#include "Scene.h"
#include "Camera.h"

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
		Win32RenderingWindow renderingWindow("CMP502", screenWidth, screenHeight, hInstance);
		D3D11Renderer d3D11Renderer(renderingWindow.getWindowHandle(), screenWidth, screenHeight);

		Scene scene { d3D11Renderer.getDevice() };
		Camera camera {};
		camera.setPosition(0.0f, 0.0f, -10.0f);

		renderingWindow.setGraphicsRenderer(d3D11Renderer);
		renderingWindow.setSceneAndCamera(scene, camera);
		renderingWindow.showWindow();
		renderingWindow.run();
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