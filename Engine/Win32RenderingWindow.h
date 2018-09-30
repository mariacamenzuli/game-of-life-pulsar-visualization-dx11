#pragma once

#include <windows.h>
#include <string>

#include "D3D11Renderer.h"
#include "Scene.h"
#include "Camera.h"

class Win32RenderingWindow {
public:
	Win32RenderingWindow(std::string applicationName, int screenWidth, int screenHeight, HINSTANCE& hInstance);
	~Win32RenderingWindow();

	void showWindow();
	HWND getWindowHandle() const;
	void setGraphicsRenderer(D3D11Renderer& d3D11Renderer);
	void setSceneAndCamera(Scene& scene, Camera& camera);
	void run();

private:
	HWND windowHandle;
	D3D11Renderer* d3D11Renderer;
	Scene* scene;
	Camera* camera;

	static LRESULT CALLBACK WindowProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam);

	LRESULT handleWindowMsg(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam);
};

class Win32RenderingWindowException : public std::exception {
private:
	DWORD errorCode;
	const char* msg;

public:
	Win32RenderingWindowException(const char* msg) : errorCode(GetLastError()), msg(msg) { }

	DWORD getErrorCode() const { return errorCode; }
	const char* what() const noexcept override {
		return msg;
	}
};
