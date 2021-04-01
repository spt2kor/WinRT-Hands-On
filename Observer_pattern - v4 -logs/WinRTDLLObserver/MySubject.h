#pragma once
#include "MySubject.g.h"
#include "ObserverSingleton.h"

using namespace winrt;

namespace winrt::WinRTDLLObserver::implementation
{
    struct MySubject : MySubjectT<MySubject>
    {
    private:
        winrt::WinRTDLLObserver::ObserverSingleton& m_ObserverSingleton;

    public:
        MySubject();

        void NotifyAsyn(hstring const& cmdStr, winrt::WinRTDLLObserver::PODData const& myData);
    };
}
namespace winrt::WinRTDLLObserver::factory_implementation
{
    struct MySubject : MySubjectT<MySubject, implementation::MySubject>
    {
    };
}
