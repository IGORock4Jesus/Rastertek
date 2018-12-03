#pragma once

#include <Windows.h>
#include <string>
//
//enum class OFD_FILTER
//{
//	jpg = 0x01,
//	png = 0x02,
//	bmp = 0x04,
//	dds = 0x08,
//	obj = 0x10,
//	fbx = 0x20,
//};

class OpenFileDialog
{
	OPENFILENAME openFileName;
	wchar_t filename[MAX_PATH];
	wchar_t filter[MAX_PATH];

public:
	OpenFileDialog(HINSTANCE hinstance, HWND hwnd);
	~OpenFileDialog();

	bool ShowDialog();
	std::wstring GetFilename() { return filename; }

	template <int TSize>
	void SetFilter(const wchar_t (&filter)[TSize]) {
		wmemcpy_s(this->filter, MAX_PATH, filter, TSize);
	}

};

