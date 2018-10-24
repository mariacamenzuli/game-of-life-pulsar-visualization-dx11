#include "Camera.h"

Camera::Camera() {
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;

    rotation.x = 0.0f;
    rotation.y = 0.0f;
    rotation.z = 0.0f;

    initOrientation();

    lookAtPoint = position + orientation.forward;
}

Camera::~Camera() = default;

D3DXVECTOR3 Camera::getPosition() {
    return position;
}

void Camera::moveStraight(float motion) {
    position += motion * orientation.forward;
    lookAtPoint = position + orientation.forward;
}

void Camera::moveSideways(float motion) {
    position += motion * orientation.right;
    lookAtPoint = position + orientation.forward;
}

void Camera::pitch(float rotationX) {
    this->rotation.x += rotationX;
    initOrientation();
    lookAtPoint = position + orientation.forward;
}

void Camera::yaw(float rotationY) {
    this->rotation.y += rotationY;
    initOrientation();
    lookAtPoint = position + orientation.forward;
}

void Camera::roll(float rotationZ) {
    this->rotation.z += rotationZ;
    initOrientation();
    lookAtPoint = position + orientation.forward;
}

void Camera::calculateViewMatrix() {
    D3DXMatrixLookAtLH(&viewMatrix, &position, &lookAtPoint, &orientation.up);
}

void Camera::getViewMatrix(D3DXMATRIX& viewMatrix) const {
    viewMatrix = this->viewMatrix;
}

void Camera::initOrientation() {
    D3DXMATRIX rotationMatrix;
    D3DXMatrixRotationYawPitchRoll(&rotationMatrix, rotation.y, rotation.x, rotation.z);

    // Reset orientation to starting positions
    orientation.forward.x = 0.0f;
    orientation.forward.y = 0.0f;
    orientation.forward.z = 1.0f;
    orientation.up.x = 0.0f;
    orientation.up.y = 1.0f;
    orientation.up.z = 0.0f;

    // Rotate about origin
    D3DXVec3TransformCoord(&orientation.forward, &orientation.forward, &rotationMatrix);
    D3DXVec3TransformCoord(&orientation.up, &orientation.up, &rotationMatrix);

    D3DXVec3Cross(&orientation.right, &orientation.up, &orientation.forward);
}
