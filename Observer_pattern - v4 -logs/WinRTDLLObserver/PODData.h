#pragma once
#include "PODData.g.h"

namespace winrt::WinRTDLLObserver::implementation
{
    struct PODData : PODDataT<PODData>
    {
        PODData();
        PODData(const PODData& obj);
        ~PODData();
        PODData& operator=(const PODData& obj);
        
        hstring m_msg();
        void m_msg(winrt::hstring const& value);
        winrt::hstring m_value();
        void m_value(winrt::hstring const& value);
        int16_t m_status();
        void m_status(int16_t value);

    private:
        void copy(const PODData& obj);

        winrt::hstring _msg;
        winrt::hstring _value;
        int16_t _status{0};

    };
}

namespace winrt::WinRTDLLObserver::factory_implementation
{
    struct PODData : PODDataT<PODData, implementation::PODData>
    {
    };
}