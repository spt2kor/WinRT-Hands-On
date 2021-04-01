


#include "framework.h"
#include "MyWindow2.h"


// Global Variables:
HINSTANCE g_hInst2;                                // current instance
WCHAR g_szTitle2[MAX_LOADSTRING] = L"second_Window_title";                  // The title bar text
WCHAR g_szWindowClass2[MAX_LOADSTRING] = L"second_Window_class";            // the main window class name

HWND g_hWnd2;
winrt::MyUWPApp::App g_hostApp{ nullptr };
DesktopWindowXamlSource g_desktopSource2{nullptr};
winrt::MyUWPApp::MyUserControl g_myUserControl{ nullptr };


DWORD  Window2ThreadFunc(LPVOID lpParam)
{
    Log("starting the thread");

    // Initialize global strings
    //LoadStringW(g_hInstance, IDS_APP_TITLE, g_szTitle2, MAX_LOADSTRING);
    //LoadStringW(g_hInstance, IDC_MYDESKTOPWIN32APP, g_szWindowClass2, MAX_LOADSTRING);

    Log("registering the class");
    MyRegisterClass2(g_hInstance);

    Log("init instance");
    // Perform application initialization:
    if (!InitInstance2(g_hInstance, SW_SHOW))
    {
        return FALSE;
    }

    //DesktopWindowXamlSource desktopSource2;
    StartXamlIsland2();


    //HACCEL hAccelTable = LoadAccelerators(g_hInstance, MAKEINTRESOURCE(IDC_MYDESKTOPWIN32APP));

    MSG msg;

    Log("starting message loop for the thread");
    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
 //       if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }


    Log("closing the thread");
    return 0;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//

void StartXamlIsland2()
{
    // Begin XAML Island section.

    // The call to winrt::init_apartment initializes COM; by default, in a multithreaded apartment.
    winrt::init_apartment(apartment_type::single_threaded);

    // Initialize the XAML framework's core window for the current thread.
    //WindowsXamlManager winxamlmanager = WindowsXamlManager::InitializeForCurrentThread();

    // This DesktopWindowXamlSource is the object that enables a non-UWP desktop application 
    // to host WinRT XAML controls in any UI element that is associated with a window handle (HWND).
    g_hostApp = winrt::MyUWPApp::App{};
    g_desktopSource2 = DesktopWindowXamlSource();

    // Get handle to the core window.
    auto interop = g_desktopSource2.as<IDesktopWindowXamlSourceNative>();

    // Parent the DesktopWindowXamlSource object to the current window.
    check_hresult(interop->AttachToWindow(g_hWnd2));

    // This HWND will be the window handler for the XAML Island: A child window that contains XAML.  
    HWND hWndXamlIsland = nullptr;

    // Get the new child window's HWND. 
    interop->get_WindowHandle(&hWndXamlIsland);

    RECT windowRect;
    ::GetWindowRect(g_hWnd2, &windowRect);
    ::SetWindowPos(hWndXamlIsland, NULL, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_SHOWWINDOW);
    g_myUserControl = winrt::MyUWPApp::MyUserControl();
    g_desktopSource2.Content(g_myUserControl);

    // End XAML Island section.
}
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass2(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc2;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = g_szWindowClass2;

    auto result = RegisterClassExW(&wcex);
    auto lastError = GetLastError();

    return result;

}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance2(HINSTANCE hInstance, int nCmdShow)
{
    g_hInst2 = hInstance; // Store instance handle in our global variable

    g_hWnd2 = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, g_szWindowClass2, g_szTitle2, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd2)
    {
        auto lastError = GetLastError();
        return FALSE;
    }

    ShowWindow(g_hWnd2, nCmdShow);
    UpdateWindow(g_hWnd2);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            Log("received IDM_ABOUT 2 message");
            DialogBox(g_hInst2, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About2);
            break;
        case IDM_EXIT:
            Log("received IDM_EXIT 2 message");
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        Log("received WM_DESTROY 2 message");
        PostQuitMessage(0);
        if (g_desktopSource2 != nullptr)
        {
            g_desktopSource2.Close();
            g_desktopSource2 = nullptr;
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
