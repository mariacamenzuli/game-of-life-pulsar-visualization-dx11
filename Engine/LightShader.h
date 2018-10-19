#pragma once

#include <D3DX10math.h>
#include <D3D11.h>
#include <wrl/client.h>

class LightShader {
public:

    LightShader();
    ~LightShader();

    void compile(ID3D11Device* device);
    void prepareShaderInput(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, D3DXVECTOR4 ambientLightColor);

private:
    struct TransformationMatricesBuffer {
        D3DXMATRIX world;
        D3DXMATRIX view;
        D3DXMATRIX projection;
    };

    struct AmbientLightBuffer {
        D3DXVECTOR4 ambientLightColor;
    };

    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
    Microsoft::WRL::ComPtr<ID3D11Buffer> transformationMatricesBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> ambientLightBuffer;
};
