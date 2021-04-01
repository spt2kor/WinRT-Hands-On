#include "pch.h"
#include "MyObserver.h"

#include "Logger.h"
#include "MyObserver.g.cpp"

namespace winrt::WinRTDLLObserver::implementation
{
    MyObserver::MyObserver() :m_ObserverSingleton(ObserverSingleton::GetInstance())
    {

    }

    winrt::WinRTDLLObserver::EventToken MyObserver::Register(hstring const& cmdString, winrt::WinRTDLLObserver::UpdateOnDataChange const& aDelegate)
    {
        Log(string("reg@cmd:" + to_string(cmdString)));
        return m_ObserverSingleton.AddEventHandler(cmdString, aDelegate);
    }

    void MyObserver::DeRegister(hstring const& cmdString, winrt::WinRTDLLObserver::EventToken const& token_value)
    {

        Log(string("Dereg@ccmd:" + to_string(cmdString)));
        m_ObserverSingleton.RemoveEventHandler(cmdString, token_value);
    }
}
