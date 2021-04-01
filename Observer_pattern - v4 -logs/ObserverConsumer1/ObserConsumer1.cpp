#include "pch.h"
#include "ObserConsumer1.h"
#include "ObserConsumer1.g.cpp"
#include "Logger.h"

namespace winrt::ObserverConsumer1::implementation
{


    void ObserConsumer1::Register(const hstring& cmdStr)
    {
        //return  m_MyObservable.Register(cmdStr, m_callback);
        m_token = m_Observer.Register(cmdStr, {this, &ObserConsumer1::MyCallback });
    }


    void ObserConsumer1::DeRegister(const hstring& cmdStr)
    {
        return m_Observer.DeRegister(cmdStr, m_token);
    }


    void ObserConsumer1::MyCallback(hstring cmd, WinRTDLLObserver::PODData p_data) 
    {
        Log(string( string("DLL:Update:") + to_string(cmd) + string(":") + to_string(p_data.m_msg()) ) );
    }

    ObserConsumer1::ObserConsumer1() : m_Observer(WinRTDLLObserver::MyObserver())
    {
     /*   m_callback = [this](hstring cmd, WinRTDLLObserver::PODData p_data) {
            this->m_strData = to_hstring(string("Recev:ObserConsumer1 :") + to_string(cmd) + string(" => ") + to_string(p_data.m_msg()));
        };
        */
    }
}
