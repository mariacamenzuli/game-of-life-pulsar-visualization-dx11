#pragma once

#include <windows.h>
#include <string>

#include "D3D11Renderer.h"

class Win32GraphicsApp {
public:
	Win32GraphicsApp(std::string applicationName, HINSTANCE& hInstance);
	~Win32GraphicsApp();

	void showWindow();
	HWND getWindowHandle() const;
	void assignGraphicsRenderer(D3D11Renderer &d3D11Renderer);
	void run();

private:
	HWND windowHandle;
	D3D11Renderer* d3D11Renderer;

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
