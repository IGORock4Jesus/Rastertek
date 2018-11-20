#pragma once

#include <Windows.h>
#include "D3D.h"
#include "Camera.h"
#include "ColorShader.h"
#include "Model.h"


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCRENN_DEPTH = 10000.0f;
const float SCREEN_NEAR = 0.1f;


class Graphics
{
	D3D d3d;
	Camera camera;
	Model model;
	ColorShader shader;

	bool Render();
public:
	Graphics();
	~Graphics();

	bool Initialize(int width, int height, HWND hwnd);
	bool Frame();
	void Shutdown();
};

