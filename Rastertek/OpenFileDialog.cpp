#include "OpenFileDialog.h"
//#include <ShObjIdl_core.h>
#include <exception>
#include <wchar.h>


OpenFileDialog::OpenFileDialog(HINSTANCE hinstance, HWND hwnd)
	: filename{ 0 }, filter{ 0 },
	openFileName {sizeof(OPENFILENAME), hwnd, hinstance, filter, nullptr, 1, 0, filename, MAX_PATH, nullptr, 0, nullptr, L"Выберите текстуру", OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 0, 0, nullptr, 0, nullptr, nullptr, nullptr, 0, 0
}
{
	/*IFileDialog *fileDialog{ nullptr };
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&fileDialog));
	if (FAILED(hr))
		throw std::exception("CoCreateInstance() - failed");

	IFileDialogEvents *events{ nullptr };
	if (FAILED(hr = cdialogeventhandler_createinstance(IID_PPV_ARGS(&events))))
		throw std::exception("CDialogEventHandler_CreateInstance() - failed");*/

}


OpenFileDialog::~OpenFileDialog()
{
}

bool OpenFileDialog::ShowDialog()
{
	wchar_t dir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, dir);
	auto result = GetOpenFileName(&openFileName);
	SetCurrentDirectory(dir);
	return result;
}

//void OpenFileDialog::SetFilter(wchar_t filter[], size_t size)
//{
//	wmemcpy_s(this->filter, MAX_PATH,  filter, size);
//}
