#pragma once
#include "MyObserverAutoRevoke.g.h"
#include "ObserverSingleton.h"

using Map = winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::WinRTDLLObserver::EventToken>;
using MapView = winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::WinRTDLLObserver::EventToken>;
using Vector = winrt::Windows::Foundation::Collections::IVector<winrt::hstring>;


namespace winrt::WinRTDLLObserver::implementation
{
    struct MyObserverAutoRevoke : MyObserverAutoRevokeT<MyObserverAutoRevoke>
    {
    private:

        winrt::WinRTDLLObserver::ObserverSingleton& m_ObserverSingleton;
        Map m_CmdTokenMap{nullptr};
        
    public:

        MyObserverAutoRevoke() ;
        ~MyObserverAutoRevoke();

        winrt::WinRTDLLObserver::EventToken Register(winrt::hstring const& cmdString, winrt::WinRTDLLObserver::UpdateOnDataChange const& func);

        void DeRegister(winrt::hstring const& cmdString, winrt::WinRTDLLObserver::EventToken const& token_value);
        
        MapView RegisterCmds(Vector const& cmdStrings, winrt::WinRTDLLObserver::UpdateOnDataChange const& func);

        void DeRegisterCmds(MapView const& reg_tokens);
        
        void DeRegisterAll();
    };
}
namespace winrt::WinRTDLLObserver::factory_implementation
{
    struct MyObserverAutoRevoke : MyObserverAutoRevokeT<MyObserverAutoRevoke, winrt::WinRTDLLObserver::implementation::MyObserverAutoRevoke>
    {
    };
}
