#pragma once

#include <D3DX10.h>


class Camera
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXMATRIX view;

public:
	Camera();
	~Camera();

	void SetPosition(D3DXVECTOR3 pos) { position = pos; }
	void SetRotation(D3DXVECTOR3 rot) { rotation = rot; }

	D3DXVECTOR3 GetPosition() { return position; }
	D3DXVECTOR3 GetRotation() { return rotation; }

	void Render();
	D3DXMATRIX GetViewMatrix() { return view; }

	void Move(D3DXVECTOR3 v) { position += v; }

};

