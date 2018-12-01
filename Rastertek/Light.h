#pragma once

#include <D3DX10math.h>


class Light
{
	D3DXVECTOR4 diffuse;
	D3DXVECTOR3 direction;
public:
	Light();
	~Light();

	D3DXVECTOR4 GetDiffuse() { return diffuse; }
	D3DXVECTOR3 GetDirection() { return direction; }

	void SetDiffuse(D3DXVECTOR4 color) { diffuse = color; }
	void SetDirection(D3DXVECTOR3 dir) { direction = dir; }


};

