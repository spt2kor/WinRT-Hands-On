// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Logger.h"


BOOL APIENTRY DllMain( HMODULE ,
                       DWORD  ul_reason_for_call,
                       LPVOID 
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_fs.open("Observer_1_log.txt", std::fstream::out);

        
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        g_fs.close();

        break;
    }
    return TRUE;
}
