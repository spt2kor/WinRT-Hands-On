#include "pch.h"
#include "MySubject.h"

#include "Logger.h"
#include "MySubject.g.cpp"

namespace winrt::WinRTDLLObserver::implementation
{
    MySubject::MySubject():m_ObserverSingleton(ObserverSingleton::GetInstance())
    {

    }

    void MySubject::NotifyAsyn(hstring const& cmdStr, winrt::WinRTDLLObserver::PODData const& myData)
    {

        Log(string("Trigger@" + to_string(cmdStr)+string("@") + to_string(myData.m_msg())));
        m_ObserverSingleton.NotifyAsyn(cmdStr,myData);
    }
}
