/*
 * string.cpp
 *
 *  Created on: Apr 25, 2021
 *      Author: lion
 */

#include "object.h"
#include "Isolate.h"
#include <limits.h>

namespace fibjs {

class ExtStringW : public v8::String::ExternalStringResource {
public:
    ExtStringW(v8::Isolate* _isolate, exlib::wstring _buffer)
        : m_isolate(_isolate)
        , m_buffer(_buffer)
    {
        m_isolate->AdjustAmountOfExternalAllocatedMemory(m_buffer.length() * 2);
    }

    ~ExtStringW()
    {
        m_isolate->AdjustAmountOfExternalAllocatedMemory(-(int64_t)m_buffer.length() * 2);
    }

public:
    virtual const uint16_t* data() const
    {
        return (const uint16_t*)m_buffer.c_str();
    }

    virtual size_t length() const
    {
        return m_buffer.length();
    }

    exlib::string str()
    {
        return utf16to8String(m_buffer);
    }

private:
    v8::Isolate* m_isolate;
    exlib::wstring m_buffer;
};

class ExtString : public v8::String::ExternalOneByteStringResource {
public:
    ExtString(v8::Isolate* _isolate, exlib::string _buffer)
        : m_isolate(_isolate)
        , m_buffer(_buffer)
    {
        m_isolate->AdjustAmountOfExternalAllocatedMemory(m_buffer.length());
    }

    ~ExtString()
    {
        m_isolate->AdjustAmountOfExternalAllocatedMemory(-(int64_t)m_buffer.length());
    }

public:
    virtual const char* data() const
    {
        return m_buffer.c_str();
    }

    virtual size_t length() const
    {
        return m_buffer.length();
    }

    exlib::string str()
    {
        return m_buffer;
    }

private:
    v8::Isolate* m_isolate;
    exlib::string m_buffer;
};

inline bool is_safe_string(exlib::string& str)
{
    const char* s = str.c_str();
    size_t len = str.length();

    const uint64_t* w = (const uint64_t*)s;
    size_t lenw = len / sizeof(uint64_t);

    for (size_t i = 0; i < lenw; i++)
        if (w[i] & 0x8080808080808080)
            return false;

    for (size_t i = lenw * sizeof(uint64_t); i < len; i++)
        if (s[i] & 0x80)
            return false;

    return true;
}

v8::Local<v8::String> NewString(v8::Isolate* isolate, exlib::string str)
{
    ssize_t length = str.length();

    if (length > INT_MAX) {
        ThrowResult(CALL_E_OVERFLOW);
        return v8::Local<v8::String>();
    }

    v8::MaybeLocal<v8::String> mstr;
    if (is_safe_string(str))
        mstr = v8::String::NewExternalOneByte(isolate, new ExtString(isolate, str));
    else
        mstr = v8::String::NewExternalTwoByte(isolate, new ExtStringW(isolate, utf8to16String(str)));

    if (mstr.IsEmpty()) {
        return v8::Local<v8::String>();
    }

    return mstr.ToLocalChecked();
}

v8::Local<v8::String> NewString(v8::Isolate* isolate, const char* data, ssize_t length)
{
    if (length == -1)
        length = (ssize_t)qstrlen(data);

    return NewString(isolate, exlib::string(data, length));
}

exlib::string ToString(v8::Isolate* isolate, v8::Local<v8::String> str)
{
    exlib::string n;

    if (str->IsExternalOneByte())
        return ((ExtString*)str->GetExternalOneByteStringResource())->str();
    else if (str->IsExternal())
        return ((ExtStringW*)str->GetExternalStringResource())->str();

    int32_t bufUtf8Len = str->Utf8Length(isolate);
    n.resize(bufUtf8Len);
    int flags = v8::String::HINT_MANY_WRITES_EXPECTED | v8::String::NO_NULL_TERMINATION;

    str->WriteUtf8(isolate, n.c_buffer(), bufUtf8Len, NULL, flags);
    return n;
}

exlib::string ToString(v8::Isolate* isolate, v8::Local<v8::Value> v)
{
    exlib::string n;
    v8::Local<v8::String> str;

    v->ToString(isolate->GetCurrentContext()).ToLocal(&str);
    if (str.IsEmpty())
        return n;

    return ToString(isolate, str);
}

result_t GetArgumentValue(v8::Local<v8::Value> v, exlib::string& n, bool bStrict)
{
    if (v.IsEmpty())
        return CALL_E_TYPEMISMATCH;

    v8::Local<v8::String> str;

    Isolate* isolate = Isolate::current();
    if (!isolate)
        return CALL_E_JAVASCRIPT;

    if (v->IsString())
        str = v8::Local<v8::String>::Cast(v);
    else if (v->IsStringObject())
        str = v8::Local<v8::StringObject>::Cast(v)->ValueOf();
    else if (!bStrict)
        v->ToString(isolate->m_isolate->GetCurrentContext()).ToLocal(&str);
    else
        return CALL_E_TYPEMISMATCH;

    if (str.IsEmpty())
        return CALL_E_JAVASCRIPT;

    n = ToString(isolate->m_isolate, str);
    return 0;
}

} // namespace fibjs