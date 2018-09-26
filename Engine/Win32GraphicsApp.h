#pragma once

#include <windows.h>
#include <string>

#include "D3D11Renderer.h"
#include "Scene.h"

class Win32GraphicsApp {
public:
	Win32GraphicsApp(std::string applicationName, HINSTANCE& hInstance);
	~Win32GraphicsApp();

	void showWindow();
	HWND getWindowHandle() const;
	void setGraphicsRenderer(D3D11Renderer& d3D11Renderer);
	void setScene(Scene& scene);
	void run();

private:
	HWND windowHandle;
	D3D11Renderer* d3D11Renderer;
	Scene* scene;

	static LRESULT CALLBACK WindowProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam);

	LRESULT handleWindowMsg(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam);
};

class Win32GraphicsAppException : public std::exception {
private:
	DWORD errorCode;
	const char* msg;

public:
	Win32GraphicsAppException(const char* msg) : msg(msg), errorCode(GetLastError()) { }

	DWORD getErrorCode() const { return errorCode; }
	const char* what() const noexcept override {
		return msg;
	}
};
