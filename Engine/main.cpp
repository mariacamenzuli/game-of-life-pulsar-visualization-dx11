#include <iostream>
#include <windows.h>
#include <sstream>

#include "Win32Application.h"
#include "D3D11Renderer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	try {
		Win32Application win32Application("CMP502", hInstance);
		D3D11Renderer d3D11Renderer(win32Application.getWindowHandle());
		win32Application.assignD3D11Renderer(d3D11Renderer);
		win32Application.showWindow();
		win32Application.run();
	}
	catch (const D3D11RendererException& e) {
		std::cerr << e.what() << "; Error code: " << e.getErrorCode() << std::endl;
		std::ostringstream os;
		os << "Failed to initialize DirectX. Error code: " << e.getErrorCode();
		auto msgBoxMsg = os.str();
		MessageBox(nullptr, std::wstring(msgBoxMsg.begin(), msgBoxMsg.end()).c_str(), L"D3D11 Renderer Error", MB_OK);
		return EXIT_FAILURE;
	}
	catch (const Win32ApplicationException& e) {
		std::cerr << e.what() << "; Error code: " << e.getErrorCode() << std::endl;
		std::ostringstream os;
		os << "A windows application error has occurred. Error code: " << e.getErrorCode();
		auto msgBoxMsg = os.str();
		MessageBox(nullptr, std::wstring(msgBoxMsg.begin(), msgBoxMsg.end()).c_str(), L"Win32 Application Error", MB_OK);
		return EXIT_FAILURE;
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		MessageBox(nullptr, L"An unknown error has occurred", L"Unknown Error", MB_OK);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}