#pragma once

#include <D3DX10math.h>

class Camera {
public:
    Camera();
    ~Camera();

    void moveStraight(float motion);
    void moveSideways(float motion);

    void pitch(float rotationX);
    void yaw(float rotationY);
    void roll(float rotationZ);

    void calculateViewMatrix();
    void getViewMatrix(D3DXMATRIX& viewMatrix) const;
private:
    struct Orientation {
        D3DXVECTOR3 forward, up, right;
    };

    Orientation orientation;
    D3DXVECTOR3 position, rotation, lookAtPoint;
    D3DXMATRIX viewMatrix;

    void initOrientation();
};
