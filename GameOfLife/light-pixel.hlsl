// Global Variables
cbuffer AmbientLightBuffer {
    float4 ambientLightColor;
};

cbuffer PointLightBuffer {
    float4 pointLightPosition;
    float4 pointLightDiffuse;
};

// Type Definitions
// - Input
struct PixelDescriptor {
    float4 screenSpacePosition : SV_POSITION;
    float4 worldSpacePosition : POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
};

float4 diffuse(PixelDescriptor pixel) {
    float4 color = 0;
    float lightIntensity;

    float3 lightVec = pointLightPosition - pixel.worldSpacePosition;

    lightIntensity = saturate(dot(pixel.normal, lightVec));
    if (lightIntensity > 0.0f) {
        color += (pointLightDiffuse * lightIntensity);
    }

    return color;
}

float4 colorPixel(PixelDescriptor pixel) : SV_TARGET {
    float4 pixelColor;

    // start out with the ambient color
    pixelColor = ambientLightColor;

    // add any diffuse light from point light
    pixelColor += diffuse(pixel);

    return pixelColor;
}