// MyDesktopWin32App.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MyDesktopWin32App.h"

#include "MyWindow1.h"
#include "MyWindow2.h"
HINSTANCE g_hInstance;
std::fstream g_fs;
#define MAX_THREADS 2

DWORD (*ThreadFuncArr[])(LPVOID lpParam) = {NULL, NULL};

//===========================================================
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    g_fs.open("XAML_islan_log.txt", std::fstream::out );

    Log("starting main function");
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    g_hInstance = hInstance;
    // TODO: Place code here.
    HANDLE  hThreadArray[MAX_THREADS];
    ThreadFuncArr[0] = &Window1ThreadFunc;
    ThreadFuncArr[1] = &Window2ThreadFunc;

    for (int i = 0; i < MAX_THREADS; i++)
    {
        // Allocate memory for thread data.

        // Create the thread to begin execution on its own.
        Log("creating thread");
        hThreadArray[i] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size  
            ThreadFuncArr[i],       // thread function name
            NULL,          // argument to thread function 
            0,                      // use default creation flags 
            NULL);   // returns the thread identifier 


        // Check the return value for success.
        // If CreateThread fails, terminate execution. 
        // This will automatically clean up threads and memory. 

        if (hThreadArray[i] == NULL)
        {
            Log("Error unable to create a thread");
            ExitProcess(3);
        }
    } // End of main thread creation loop.

    // Wait until all threads have terminated.
    Log("waiting for threads main function");
    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
    Log("got all threads , closing now.");
    // Close all thread handles and free memory allocations.

    for (int i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]);
    }

    Log("closing main function");
    g_fs.close();
    return 0;
}

