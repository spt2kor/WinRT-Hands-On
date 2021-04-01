

#include "framework.h"

#include "MyWindow1.h"

// Global Variables:
HINSTANCE g_hInst1;                                // current instance
WCHAR g_szTitle1[MAX_LOADSTRING] = L"first_Window_title";                  // The title bar text
WCHAR g_szWindowClass1[MAX_LOADSTRING] = L"first_Window_class";            // the main window class name

HWND g_hWnd1;


DWORD  Window1ThreadFunc(LPVOID lpParam)
{
    Log("starting the thread");

    // Initialize global strings
    //LoadStringW(g_hInstance, IDS_APP_TITLE, g_szTitle, MAX_LOADSTRING);
    //LoadStringW(g_hInstance, IDC_MYDESKTOPWIN32APP, g_szWindowClass, MAX_LOADSTRING);

    
    Log("registering the class");
    MyRegisterClass1(g_hInstance);

    Log("init instance");
    // Perform application initialization:
    if (!InitInstance1(g_hInstance, SW_SHOW))
    {
        auto lastError = GetLastError();
        return FALSE;
    }
    //
    //===========================================================
    DesktopWindowXamlSource desktopSource1;
    StartXamlIsland1(desktopSource1);
   
//    HACCEL hAccelTable = LoadAccelerators(g_hInstance, MAKEINTRESOURCE(IDC_MYDESKTOPWIN32APP));

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

void StartXamlIsland1(DesktopWindowXamlSource desktopSource1)
{
    // Begin XAML Island section.

    // The call to winrt::init_apartment initializes COM; by default, in a multithreaded apartment.
    winrt::init_apartment(apartment_type::single_threaded);

    // Initialize the XAML framework's core window for the current thread.
    WindowsXamlManager winxamlmanager = WindowsXamlManager::InitializeForCurrentThread();

    // This DesktopWindowXamlSource is the object that enables a non-UWP desktop application 
    // to host WinRT XAML controls in any UI element that is associated with a window handle (HWND).
    

    //DesktopWindowXamlSource desktopSource1;
    // Get handle to the core window.
    auto interop = desktopSource1.as<IDesktopWindowXamlSourceNative>();

    // Parent the DesktopWindowXamlSource object to the current window.
    check_hresult(interop->AttachToWindow(g_hWnd1));

    // This HWND will be the window handler for the XAML Island: A child window that contains XAML.  
    HWND hWndXamlIsland = nullptr;

    // Get the new child window's HWND. 
    interop->get_WindowHandle(&hWndXamlIsland);

    // Update the XAML Island window size because initially it is 0,0.
    SetWindowPos(hWndXamlIsland, 0, 50, 50, 1200, 100, SWP_SHOWWINDOW);

    // Create the XAML content.
    Windows::UI::Xaml::Controls::StackPanel xamlContainer;
    xamlContainer.Background(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::LightGray() });

    Windows::UI::Xaml::Controls::TextBlock tb;
    tb.Text(L"Hello World from Xaml Islands -1");
    tb.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
    tb.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
    tb.FontSize(24);

    xamlContainer.Children().Append(tb);
    xamlContainer.UpdateLayout();
    desktopSource1.Content(xamlContainer);

    // End XAML Island section.
}
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass1(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc1;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = g_szWindowClass1;

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
BOOL InitInstance1(HINSTANCE hInstance, int nCmdShow)
{
    g_hInst1 = hInstance; // Store instance handle in our global variable

    g_hWnd1 = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, g_szWindowClass1, g_szTitle1, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,  nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd1)
    {
        auto lastError = GetLastError();
        return FALSE;
    }

    ShowWindow(g_hWnd1, nCmdShow);
    UpdateWindow(g_hWnd1);
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
LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
            DialogBox(g_hInst1, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About1);
            Log("received IDM_ABOUT message");
            break;
        case IDM_EXIT:
            Log("received IDM_EXIT message");
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
        Log("received WM_DESTROY message");
        PostQuitMessage(0);
        break;
//    case WM_SIZE:
//        AdjustLayout(hWnd);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
