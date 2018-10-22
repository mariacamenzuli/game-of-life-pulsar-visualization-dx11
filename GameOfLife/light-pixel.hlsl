cbuffer AmbientLightBuffer {
    float4 sceneAmbientColor;
};

cbuffer PointLightBuffer {
    float4 pointLightPosition;
    float4 pointLightDiffuse;
};

cbuffer MaterialBuffer {
    float4 materialAmbientColor;
    float4 materialDiffuseColor;
    float4 materialSpecularColor;
};

// Type Definitions
// - Input
struct PixelDescriptor {
    float4 screenSpacePosition : SV_POSITION;
    float4 worldSpacePosition : POSITION;
    float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
};

float4 ambientColor() {
    return materialAmbientColor * sceneAmbientColor;
}

float4 diffuseColor(PixelDescriptor pixel) {
    float4 color = 0;
    float lightIntensity;

    float3 pointToLightVector = pointLightPosition - pixel.worldSpacePosition;
    float pointToLightVectorLength = length(pointToLightVector);

    // make unit vector
    pointToLightVector /= pointToLightVectorLength;

    lightIntensity = saturate(dot(pixel.normal, pointToLightVector)); //todo: to saturate or not to saturate? when should we saturate?
    if (lightIntensity > 0.0f) {
        color += (lightIntensity * materialDiffuseColor * pointLightDiffuse);
    }

    return color;
}

float4 colorPixel(PixelDescriptor pixel) : SV_TARGET {
    float4 pixelColor = 0;

    // start out with the ambient color
    pixelColor += ambientColor();

    // add any diffuse light from point light
    pixelColor += diffuseColor(pixel);

    return pixelColor;
}