#include "Input.h"
#include <Windows.h>


Input::Input()
{
}


Input::~Input()
{
}

void Input::Initialize()
{
	ZeroMemory(keys, sizeof(bool) * 256);
}

void Input::KeyDown(int key)
{
	keys[key] = true;
}

void Input::KeyUp(int key)
{
	keys[key] = false;
}

bool Input::IsKeyDown(int key)
{
	return keys[key];
}
