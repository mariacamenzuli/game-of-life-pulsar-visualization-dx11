#include "Win32Application.h"

#include <stdexcept>

Win32Application::Win32Application(std::string applicationName, HINSTANCE& hInstance) : hInstance(hInstance), d3D11Renderer(nullptr) {
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

	auto applicationNameWideString = std::wstring(applicationName.begin(), applicationName.end()).c_str();
	windowHandle = CreateWindowEx(
		0,                              // Optional window styles.
		windowClass.lpszClassName,      // Window class
		applicationNameWideString,      // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		nullptr,       // Parent window
		nullptr,       // Menu
		hInstance,     // Instance handle
		this           // Additional application data
	);

	if (windowHandle == nullptr) {
		throw Win32ApplicationException("failed to create window");
	}
}

Win32Application::~Win32Application() {

}

void Win32Application::showWindow() {
	ShowWindow(windowHandle, SW_SHOW);
	SetForegroundWindow(windowHandle);
	SetFocus(windowHandle);
}

HWND Win32Application::getWindowHandle() {
	return windowHandle;
}

void Win32Application::assignD3D11Renderer(D3D11Renderer &d3D11Renderer) {
	this->d3D11Renderer = &d3D11Renderer;
}

void Win32Application::run() {
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

LRESULT Win32Application::handleWindowMsg(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(windowHandle, msg, wParam, lParam);
	}
}

LRESULT Win32Application::WindowProc(HWND windowHandle, UINT msg, WPARAM wParam, LPARAM lParam) {
	Win32Application* win32Application = nullptr;

	if (msg == WM_NCCREATE) {
		auto * pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		win32Application = static_cast<Win32Application*>(pCreate->lpCreateParams);
		SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(win32Application));
	}
	else {
		win32Application = reinterpret_cast<Win32Application*>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));
	}

	if (win32Application) {
		return win32Application->handleWindowMsg(windowHandle, msg, wParam, lParam);
	}
	else {
		return DefWindowProc(windowHandle, msg, wParam, lParam);
	}
}
