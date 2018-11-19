#pragma once




class Input
{
	bool keys[256];

public:
	Input();
	~Input();

	void Initialize();

	void KeyDown(int key);
	void KeyUp(int key);

	bool IsKeyDown(int key);
	//bool IsKeyUp(int key);
};

