#include "Win32GraphicsApp.h"

#include <stdexcept>

Win32GraphicsApp::Win32GraphicsApp(std::string applicationName, HINSTANCE& hInstance) : d3D11Renderer(nullptr) {
	WNDCLASS windowClass;
	windowClass.lpszClassName = L"CMP502 Window Class";
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	windowClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.lpszMenuName = nullptr;

	RegisterClass(&windowClass);

	windowHandle = CreateWindowEx(
		0,                                                                      // Optional window styles.
		windowClass.lpszClassName,                                              // Window class
		std::wstring(applicationName.begin(), applicationName.end()).c_str(),   // Window text
		WS_OVERLAPPEDWINDOW,                                                    // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		nullptr,       // Parent window
		nullptr,       // Menu
		hInstance,     // Instance handle
		this           // Additional application data
	);

	if (windowHandle == nullptr) {
		throw Win32GraphicsAppException("failed to create window");
	}
}

Win32GraphicsApp::~Win32GraphicsApp() = default;

void Win32GraphicsApp::showWindow() {
	ShowWindow(windowHandle, SW_SHOW);
	SetForegroundWindow(windowHandle);
	SetFocus(windowHandle);
}

HWND Win32GraphicsApp::getWindowHandle() const {
	return windowHandle;
}

void Win32GraphicsApp::assignGraphicsRenderer(D3D11Renderer &d3D11Renderer) {
	this->d3D11Renderer = &d3D11Renderer;
}

void Win32GraphicsApp::run() {
	if (!d3D11Renderer) {
		return;
	}

	MSG msg = { };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		d3D11Renderer->renderFrame();
	}
}

LRESULT Win32GraphicsApp::handleWindowMsg(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(windowHandle, msg, wParam, lParam);
	}
}

LRESULT Win32GraphicsApp::WindowProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam) {
	Win32GraphicsApp* win32GraphicsApp = nullptr;

	if (msg == WM_NCCREATE) {
		auto * pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		win32GraphicsApp = static_cast<Win32GraphicsApp*>(pCreate->lpCreateParams);
		SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(win32GraphicsApp));
	}
	else {
		win32GraphicsApp = reinterpret_cast<Win32GraphicsApp*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
	}

	if (win32GraphicsApp) {
		return win32GraphicsApp->handleWindowMsg(windowHandle, msg, wParam, lParam);
	}
	else {
		return DefWindowProc(windowHandle, msg, wParam, lParam);
	}
}
