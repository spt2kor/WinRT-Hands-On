#include "pch.h"
#include "EventToken.h"
#include "EventToken.g.cpp"

namespace winrt::WinRTDLLObserver::implementation
{
    int64_t EventToken::token_value()
    {
        return m_token_value;
    }
    
    EventToken::EventToken(int64_t tokenvalue) :m_token_value(tokenvalue)
    {
    }

}
