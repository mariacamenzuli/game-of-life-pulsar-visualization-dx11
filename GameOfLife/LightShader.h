#pragma once

#include <D3DX10math.h>
#include <D3D11.h>
#include <wrl/client.h>

#include "PointLight.h"

class LightShader {
public:
    LightShader();
    ~LightShader();

    void initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
    void updateTransformationMatricesBuffer(ID3D11DeviceContext* deviceContext,
                                            D3DXMATRIX worldMatrix,
                                            D3DXMATRIX viewMatrix,
                                            D3DXMATRIX projectionMatrix);
    void updateCameraBuffer(ID3D11DeviceContext* deviceContext, D3DXVECTOR3 cameraPosition);
    void updateAmbientLightBuffer(ID3D11DeviceContext* deviceContext, D3DXVECTOR4 ambientLightColor);
    void updatePointLightBuffer(ID3D11DeviceContext* deviceContext,  D3DXVECTOR4 diffuse, D3DXVECTOR4 specular, D3DXMATRIX worldMatrix);
    void updateMaterialBuffer(ID3D11DeviceContext* deviceContext,D3DXVECTOR4 materialAmbientColor, D3DXVECTOR4 materialDiffuseColor, D3DXVECTOR4 materialSpecularColor);

private:
    struct TransformationMatricesBuffer {
        D3DXMATRIX world;
        D3DXMATRIX view;
        D3DXMATRIX projection;
    };

    struct CameraBuffer {
        D3DXVECTOR4 cameraPosition;
    };

    struct AmbientLightBuffer {
        D3DXVECTOR4 sceneAmbientColor;
    };

    struct PointLightBuffer {
        D3DXVECTOR4 pointLightPosition;
        D3DXVECTOR4 pointLightDiffuse;
        D3DXVECTOR4 pointLightSpecular;
    };

    struct MaterialBuffer {
        D3DXVECTOR4 materialAmbientColor;
        D3DXVECTOR4 materialDiffuseColor;
        D3DXVECTOR4 materialSpecularColor;
    };

    Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
    Microsoft::WRL::ComPtr<ID3D11Buffer> transformationMatricesBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> cameraBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> ambientLightBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> pointLightBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer> materialBuffer;

    void setupVertexShader(ID3D11Device* device);
    void setupPixelShader(ID3D11Device* device);
};
