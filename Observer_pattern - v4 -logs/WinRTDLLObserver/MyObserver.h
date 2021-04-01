#pragma once
#include "MyObserver.g.h"
#include "ObserverSingleton.h"

using namespace std;

namespace winrt::WinRTDLLObserver::implementation
{
    struct MyObserver : MyObserverT<MyObserver>
    {
    private:
        WinRTDLLObserver::ObserverSingleton& m_ObserverSingleton;

    public:

        MyObserver();

        WinRTDLLObserver::EventToken Register(hstring const& cmdString, WinRTDLLObserver::UpdateOnDataChange const& func);

        void DeRegister(hstring const& cmdString, WinRTDLLObserver::EventToken const& token_value);
    };
}
namespace winrt::WinRTDLLObserver::factory_implementation
{
    struct MyObserver : MyObserverT<MyObserver, implementation::MyObserver>
    {
    };
}
