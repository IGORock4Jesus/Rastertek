#pragma once

#include <D3DX10math.h>


class Light
{
	D3DXVECTOR4 diffuse;
	D3DXVECTOR4 ambient;
	D3DXVECTOR3 direction;
	float power;
	D3DXVECTOR4 specular;

public:
	Light();
	~Light();

	D3DXVECTOR4 GetDiffuse() { return diffuse; }
	D3DXVECTOR4 GetAmbient() { return ambient; }
	D3DXVECTOR3 GetDirection() { return direction; }
	float GetPower() { return power; }
	D3DXVECTOR4 GetSpecular() { return specular; }

	void SetDiffuse(D3DXVECTOR4 color) { diffuse = color; }
	void SetAmbient(D3DXVECTOR4 color) { ambient = color; }
	void SetDirection(D3DXVECTOR3 dir) { direction = dir; }
	void SetPower(float pow) { power = pow; }
	void SetSpecular(D3DXVECTOR4 color) { specular = color; }
};

