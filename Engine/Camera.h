#pragma once

#include <d3dx10math.h>

class Camera {
public:
	Camera();
	Camera(const Camera& camera);
	~Camera();

	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);

	D3DXVECTOR3 getPosition() const;
	D3DXVECTOR3 getRotation() const;

	void calculateViewMatrix();
	void getViewMatrix(D3DXMATRIX& viewMatrix) const;
private:
	float positionX, positionY, positionZ = 0;
	float rotationX, rotationY, rotationZ = 0;
	D3DXMATRIX viewMatrix;
};