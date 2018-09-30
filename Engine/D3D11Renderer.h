#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <dxgi.h>
#include <d3d11.h>
#include <exception>
#include <string>
#include <wrl.h>
#include <d3dx10math.h>

#include "Scene.h"
#include "Camera.h"
#include "ColorShader.h"

class D3D11Renderer {
public:
	D3D11Renderer(HWND windowHandle, const int screenWidth, const int screenHeight, Scene* scene, Camera* camera);
	~D3D11Renderer();

	void renderFrame();
	ID3D11Device* getDevice();

private:
	struct MonitorDescriptor {
		unsigned int refreshRateNumerator;
		unsigned int refreshRateDenominator;
	};
	struct VideoCardDescriptor {
		int memory;
		std::string description;
	};
	struct PhysicalDeviceDescriptor {
		VideoCardDescriptor videoCard;
		MonitorDescriptor monitor;
	};

	int screenWidth;
	int screenHeight;
	Scene* scene;
	Camera* camera;

	PhysicalDeviceDescriptor hardwareInfo;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterState;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;

	D3DXMATRIX projectionMatrix;
	D3DXMATRIX orthoMatrix;
	ColorShader colorShader;

	PhysicalDeviceDescriptor queryPhysicalDeviceDescriptors();
	void createSwapChainAndDevice(HWND windowHandle);
	void createDepthAndStencilBuffer();
	void createRasterizerState();
	void setupViewport();
	void setupVertexAndIndexBuffers();
};

class D3D11RendererException : public std::exception {
private:
	long errorCode;
	const char* msg;

public:
	D3D11RendererException(const char* msg, int errorCode) : errorCode(errorCode), msg(msg) { }

	long getErrorCode() const { return errorCode; }
	const char* what() const noexcept override {
		return msg;
	}
};
