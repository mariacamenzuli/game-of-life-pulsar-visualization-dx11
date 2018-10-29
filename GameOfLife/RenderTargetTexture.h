#pragma once

#include <D3DX11tex.h>
#include <wrl/client.h>

class RenderTargetTexture {
public:
    RenderTargetTexture();
    ~RenderTargetTexture();

    void initialize(ID3D11Device* device, int width, int height);
    ID3D11ShaderResourceView** getTextureResource();
    void setAsRenderTargetAndClear(ID3D11DeviceContext* deviceContext);

private:
    Microsoft::WRL::ComPtr<ID3D11Texture2D> renderTargetTexture;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
    Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
    D3D11_VIEWPORT viewport;
};

