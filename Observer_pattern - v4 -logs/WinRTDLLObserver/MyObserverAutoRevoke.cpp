
#include "pch.h"
#include "Logger.h"
#include "MyObserverAutoRevoke.h"
#include "MyObserverAutoRevoke.g.cpp"

namespace winrt::WinRTDLLObserver::implementation
{
    MyObserverAutoRevoke::MyObserverAutoRevoke() 
        : m_ObserverSingleton(ObserverSingleton::GetInstance())
        , m_CmdTokenMap(winrt::single_threaded_map<winrt::hstring, winrt::WinRTDLLObserver::EventToken>())
    {

    }

    MyObserverAutoRevoke::~MyObserverAutoRevoke() {
        DeRegisterAll();
    }

    winrt::WinRTDLLObserver::EventToken MyObserverAutoRevoke::Register(winrt::hstring const& cmdString, UpdateOnDataChange const& func)
    {
        Log(string("reg@cmd:" + to_string(cmdString)));
        return m_ObserverSingleton.AddEventHandler(cmdString, func);
    }

    void MyObserverAutoRevoke::DeRegister(winrt::hstring const& cmdString, winrt::WinRTDLLObserver::EventToken const& token_value)
    {

        Log(string("Dereg@cmd:" + to_string(cmdString)));
        m_ObserverSingleton.RemoveEventHandler(cmdString, token_value);
    }


    MapView MyObserverAutoRevoke::RegisterCmds(Vector const& cmdStrings, UpdateOnDataChange const& func)
    {
        Map map_cmdVsToken = winrt::single_threaded_map<winrt::hstring, winrt::WinRTDLLObserver::EventToken>();
        for (auto cmd : cmdStrings) {
            auto token = m_ObserverSingleton.AddEventHandler(cmd, func);
            m_CmdTokenMap.Insert(cmd, token);
            map_cmdVsToken.Insert(cmd, token);

            Log(string("reg@cmd:" + to_string(cmd)));
        }
        return map_cmdVsToken.GetView();
    }

    void MyObserverAutoRevoke::DeRegisterCmds(MapView const& reg_tokens)
    {
        for (const auto& apair : reg_tokens) {
            m_ObserverSingleton.RemoveEventHandler(apair.Key(), apair.Value());
            m_CmdTokenMap.TryRemove(apair.Key());

            Log(string("Dereg@cmd:" + to_string(apair.Key())));
        }
    }

    void MyObserverAutoRevoke::DeRegisterAll()
    {
        for (const auto& apair : m_CmdTokenMap) {
            m_ObserverSingleton.RemoveEventHandler(apair.Key(), apair.Value());

            Log(string("Dereg@cmd:" + to_string(apair.Key())));
        }
        m_CmdTokenMap.Clear();
    }
}
