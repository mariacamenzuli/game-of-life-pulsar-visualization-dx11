#pragma once

#include <windows.h>
#include <string>

#include "D3D11Renderer.h"

class Win32Application {
public:
	Win32Application(std::string applicationName, HINSTANCE& hInstance);
	~Win32Application();

	void showWindow();
	HWND getWindowHandle();
	void assignD3D11Renderer(D3D11Renderer &d3D11Renderer);
	void run();

private:
	HINSTANCE& hInstance;
	WNDCLASS windowClass;
	HWND windowHandle;
	D3D11Renderer* d3D11Renderer;

	static LRESULT CALLBACK WindowProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam);

	LRESULT handleWindowMsg(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam);
};

class Win32ApplicationException : public std::exception {
private:
	DWORD errorCode;
	const char* msg;

public:
	Win32ApplicationException(const char* msg) : std::exception(), msg(msg), errorCode(GetLastError()) { }

	DWORD getErrorCode() const { return errorCode; }
	const char* what() const throw() override {
		return msg;
	}
};
