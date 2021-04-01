#pragma once

#include "MyDesktopWin32App.h"

class MyWindow2
{
};


DWORD  Window2ThreadFunc(LPVOID lpParam);


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass2(HINSTANCE hInstance);
BOOL                InitInstance2(HINSTANCE, int);
LRESULT CALLBACK    WndProc2(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About2(HWND, UINT, WPARAM, LPARAM);
void StartXamlIsland2();
//void StartXamlIsland2(DesktopWindowXamlSource desktopSource2);
