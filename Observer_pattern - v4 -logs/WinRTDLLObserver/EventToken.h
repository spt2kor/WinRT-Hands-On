#pragma once
#include "EventToken.g.h"

namespace winrt::WinRTDLLObserver::implementation
{
    struct EventToken : EventTokenT<EventToken>
    {
        EventToken() = default;
        explicit EventToken(int64_t tokenvalue);
        int64_t token_value();
    private:
        int64_t m_token_value{0};
    };
}
namespace winrt::WinRTDLLObserver::factory_implementation
{
    struct EventToken : EventTokenT<EventToken, implementation::EventToken>
    {
    };
}