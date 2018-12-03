#pragma once

#include <Windows.h>
#include "D3D.h"
#include "Camera.h"
#include "SpecularShader.h"
#include "TextureShader.h"
#include "Model.h"
#include "Light.h"
#include "Bitmap.h"



const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCRENN_DEPTH = 10000.0f;
const float SCREEN_NEAR = 0.1f;


class Graphics
{
	D3D d3d;
	Camera camera;
	Model model;
	SpecularShader shader;
	TextureShader textureShader;
	Light light;
	float rotation{ 0.0f };
	Bitmap *bitmap{ nullptr };

	bool Render(float time);
public:
	Graphics();
	~Graphics();

	bool Initialize(HINSTANCE hinstance, int width, int height, HWND hwnd);
	bool Frame();
	void Shutdown();

	Camera &Camera() { return camera; }
};

