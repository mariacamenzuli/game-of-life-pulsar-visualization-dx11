#pragma once

#include <d3dx10math.h>
#include <d3d11.h>
#include <memory>
#include <wrl/client.h>

class ColorShader {
public:
	ColorShader();

	void compile(ID3D11Device* device, WCHAR* vsFilename, WCHAR* psFilename);
	void prepareShaderInput(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix);

private:
	struct MatrixBufferType {
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> matrixBuffer;
};
