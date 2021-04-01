#include "pch.h"
#include "PODData.h"
#include "PODData.g.cpp"
#include "Logger.h"


namespace winrt::WinRTDLLObserver::implementation
{
    PODData::PODData():_status(0) {
        Log("PODData CTOR");
    }

    PODData::~PODData() {
        Log("PODData DTOR");
    }

    void PODData::copy(const PODData& obj) {
        _msg    = obj._msg;
        _value  = obj._value;
        _status = obj._status;
    }

    PODData::PODData(const PODData& obj) {
        copy(obj);
        Log("PODData Copy CTOR");
    }

    PODData& PODData::operator=(const PODData& obj) {
        Log("PODData operator=()");
        copy(obj);
        return *this;
    }

    hstring PODData::m_msg()
    {
        return _msg;
    }
    void PODData::m_msg(hstring const& value)
    {
        _msg = value;
    }
    hstring PODData::m_value()
    {
        return _value;
    }
    void PODData::m_value(hstring const& value)
    {
        _value = value;
    }
    int16_t PODData::m_status()
    {
        return _status;
    }
    void PODData::m_status(int16_t value)
    {
        _status = value;
    }
}
