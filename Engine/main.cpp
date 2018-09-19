#include <iostream>
#include <windows.h>

#include "Win32GraphicsApp.h"
#include "D3D11Renderer.h"

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
		Win32GraphicsApp win32GraphicsApp("CMP502", hInstance);

		D3D11Renderer d3D11Renderer(win32GraphicsApp.getWindowHandle());
		win32GraphicsApp.assignD3D11Renderer(d3D11Renderer);

		win32GraphicsApp.showWindow();
		win32GraphicsApp.run();
	} catch (const D3D11RendererException& e) {
		logErrorAndNotifyUser(e.what(), "Failed to initialize DirectX. Error code " + std::to_string(e.getErrorCode()));
		return EXIT_FAILURE;
	} catch (const Win32GraphicsAppException& e) {
		logErrorAndNotifyUser(e.what(), "A windows application error has occurred. Error code " + std::to_string(e.getErrorCode()));
		return EXIT_FAILURE;
	} catch (const std::exception& e) {
		logErrorAndNotifyUser(e.what(), "An unknown error has occurred.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}