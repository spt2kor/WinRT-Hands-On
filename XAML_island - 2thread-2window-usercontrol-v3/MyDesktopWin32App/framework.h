// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

//#include "targetver.h"
//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#undef GetCurrentTime
// C RunTime Header Files
#include <iostream>
#include <fstream>
#include <thread>
using namespace std;


//===================================================
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.system.h>
#include <winrt/windows.ui.xaml.hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/Windows.ui.xaml.media.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/MyUWPApp.h>

using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI::Xaml::Controls;
//===================================================
#define MAX_LOADSTRING 100

extern HINSTANCE g_hInstance;
extern std::fstream g_fs;

#define Log(msg) g_fs << __LINE__<<":"<<__func__<<"["<<std::this_thread::get_id()<<"] : "<<(msg) << endl;
