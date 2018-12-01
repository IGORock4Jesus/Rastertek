#pragma once

#include <Windows.h>
#include "D3D.h"
#include "Camera.h"
#include "DiffuseShader.h"
#include "Model.h"
#include "Light.h"


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCRENN_DEPTH = 10000.0f;
const float SCREEN_NEAR = 0.1f;


class Graphics
{
	D3D d3d;
	Camera camera;
	Model model;
	DiffuseShader shader;
	Light light;
	float rotation{ 0.0f };

	bool Render(float time);
public:
	Graphics();
	~Graphics();

	bool Initialize(int width, int height, HWND hwnd);
	bool Frame();
	void Shutdown();

	Camera &Camera() { return camera; }
};

