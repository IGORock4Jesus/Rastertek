#include "Camera.h"



Camera::Camera()
	:position{ 0.0f, 0.0f, 0.0f }, rotation{ 0.0f, 0.0f, 0.0f }
{
	D3DXMatrixIdentity(&view);
}


Camera::~Camera()
{
}

void Camera::Render()
{
	D3DXMATRIX rotm;
	D3DXMatrixRotationYawPitchRoll(&rotm, D3DXToRadian(rotation.x), D3DXToRadian(rotation.y), D3DXToRadian(rotation.z));

	D3DXVECTOR3 lookAt{ 0,0,1 }, up{ 0,1,0 };
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotm);
	D3DXVec3TransformCoord(&up, &up, &rotm);

	lookAt += position;

	D3DXMatrixLookAtLH(&view, &position, &lookAt, &up);
}
