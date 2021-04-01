#pragma once


#include "MyDesktopWin32App.h"

class MyWindow1
{
};

DWORD  Window1ThreadFunc(LPVOID lpParam);


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass1(HINSTANCE hInstance);
BOOL                InitInstance1(HINSTANCE, int);
LRESULT CALLBACK    WndProc1(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About1(HWND, UINT, WPARAM, LPARAM);
void StartXamlIsland1(DesktopWindowXamlSource desktopSource1);