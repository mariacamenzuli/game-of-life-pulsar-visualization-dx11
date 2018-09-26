#include "Camera.h"

Camera::Camera() {
	positionX = 0.0f;
	positionY = 0.0f;
	positionZ = 0.0f;

	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;
}

Camera::Camera(const Camera& camera) {
	positionX = camera.positionX;
	positionY = camera.positionY;
	positionZ = camera.positionZ;

	rotationX = camera.rotationX;
	rotationY = camera.rotationY;
	rotationZ = camera.rotationZ;
}

Camera::~Camera() = default;

void Camera::setPosition(float x, float y, float z) {
	positionX = x;
	positionY = y;
	positionZ = z;
}

void Camera::setRotation(float x, float y, float z) {
	rotationX = x;
	rotationY = y;
	rotationZ = z;
}

D3DXVECTOR3 Camera::getPosition() const {
	return { positionX, positionY, positionZ };
}

D3DXVECTOR3 Camera::getRotation() const {
	return { rotationX, rotationY, rotationZ };
}

void Camera::calculateViewMatrix() {
	D3DXVECTOR3 up, position, lookAt;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = positionX;
	position.y = positionY;
	position.z = positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	float pitch = rotationX * 0.0174532925f;
	float yaw = rotationY * 0.0174532925f;
	float roll = rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&viewMatrix, &position, &lookAt, &up);
}

void Camera::getViewMatrix(D3DXMATRIX& viewMatrix) const {
	viewMatrix = this->viewMatrix;
}
