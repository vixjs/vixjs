/*
 * encoding_iconv.cpp
 *
 *  Created on: Jul 13, 2014
 *      Author: lion
 */

#ifdef _WIN32
#include <winiconv/win_iconv.h>
#else

#include "config.h"

#ifdef HAVE_ICONV_H
#include <iconv.h>
#else
#include <stddef.h>
#endif

#include <dlfcn.h>

#endif

#include "object.h"
#include "encoding_iconv.h"
#include "ifs/encoding.h"

namespace fibjs {

DECLARE_MODULE(iconv);

#ifdef _WIN32

#define _iconv_open iconv_open
#define _iconv_close iconv_close
#define _iconv iconv

inline void init_iconv()
{
}

#elif !defined(FreeBSD)

#define _iconv_open iconv_open
#define _iconv_close iconv_close
#define _iconv ((size_t(*)(iconv_t, const char**, size_t*, char**, size_t*)) & iconv)

inline void init_iconv()
{
}

#else

#ifndef HAVE_ICONV_H

typedef void* iconv_t;

static iconv_t iconv_open(const char* tocode, const char* fromcode)
{
    return (iconv_t)-1;
}

static int32_t iconv_close(iconv_t cd)
{
    return 0;
}

static size_t iconv(iconv_t cd, const char** inbuf, size_t* inbytesleft,
    char** outbuf, size_t* outbytesleft)
{
    return 0;
}

#endif

static size_t (*_iconv)(iconv_t, const char**, size_t*, char**, size_t*);
static iconv_t (*_iconv_open)(const char*, const char*);
static int32_t (*_iconv_close)(iconv_t);

inline void init_iconv()
{
    static bool _init = false;

    if (!_init) {
        _init = true;

        void* handle = dlopen("libiconv.so", RTLD_LAZY);

        if (handle) {
            _iconv = (size_t(*)(iconv_t, const char**, size_t*, char**, size_t*))dlsym(handle, "iconv");
            if (!_iconv)
                _iconv = (size_t(*)(iconv_t, const char**, size_t*, char**, size_t*))dlsym(handle, "libiconv");

            _iconv_open = (iconv_t(*)(const char*, const char*))dlsym(handle, "iconv_open");
            if (!_iconv_open)
                _iconv_open = (iconv_t(*)(const char*, const char*))dlsym(handle, "libiconv_open");

            _iconv_close = (int32_t(*)(iconv_t))dlsym(handle, "iconv_close");
            if (!_iconv_close)
                _iconv_close = (int32_t(*)(iconv_t))dlsym(handle, "libiconv_close");
        }

        if (!_iconv || !_iconv_open || !_iconv_close) {
            _iconv = (size_t(*)(iconv_t, const char**, size_t*, char**, size_t*))iconv;
            _iconv_open = iconv_open;
            _iconv_close = iconv_close;
        }
    }
}

#endif

encoding_iconv::encoding_iconv()
    : m_iconv_en(NULL)
    , m_iconv_de(NULL)
    , m_iconv_ec(NULL)
{
    init_iconv();
    m_charset = "utf-8";
}

encoding_iconv::encoding_iconv(exlib::string charset)
    : m_iconv_en(NULL)
    , m_iconv_de(NULL)
    , m_iconv_ec(NULL)
{
    init_iconv();
    m_charset = (charset == "gb2312") ? "gbk" : charset;
}

encoding_iconv::~encoding_iconv()
{
    if (m_iconv_en)
        _iconv_close((iconv_t)m_iconv_en);

    if (m_iconv_de)
        _iconv_close((iconv_t)m_iconv_de);

    if (m_iconv_ec)
        _iconv_close((iconv_t)m_iconv_ec);
}

void encoding_iconv::open(const char* charset)
{
    if (m_iconv_en) {
        _iconv_close((iconv_t)m_iconv_en);
        m_iconv_en = NULL;
    }

    if (m_iconv_de) {
        _iconv_close((iconv_t)m_iconv_de);
        m_iconv_de = NULL;
    }

    if (m_iconv_ec) {
        _iconv_close((iconv_t)m_iconv_ec);
        m_iconv_ec = NULL;
    }
    m_charset = charset;
}

inline bool is_ucs2(exlib::string codec)
{
    if ((codec == "ucs2") || (codec == "ucs-2")
        || (codec == "utf16") || (codec == "utf-16"))
        return true;

    if (is_big_endian()) {
        if ((codec == "ucs2be") || (codec == "ucs-2be")
            || (codec == "utf16be") || (codec == "utf-16be"))
            return true;
    } else {
        if ((codec == "ucs2le") || (codec == "ucs-2le")
            || (codec == "utf16le") || (codec == "utf-16le"))
            return true;
    }

    return false;
}

inline bool is_ucs2_s(exlib::string codec)
{
    if (!is_big_endian()) {
        if ((codec == "ucs2be") || (codec == "ucs-2be")
            || (codec == "utf16be") || (codec == "utf-16be"))
            return true;
    } else {
        if ((codec == "ucs2le") || (codec == "ucs-2le")
            || (codec == "utf16le") || (codec == "utf-16le"))
            return true;
    }

    return false;
}

inline bool is_ucs4(exlib::string codec)
{
    if ((codec == "ucs4") || (codec == "ucs-4")
        || (codec == "utf32") || (codec == "utf-32"))
        return true;

    if (is_big_endian()) {
        if ((codec == "ucs4be") || (codec == "ucs-4be")
            || (codec == "utf32be") || (codec == "utf-32be"))
            return true;
    } else {
        if ((codec == "ucs4le") || (codec == "ucs-4le")
            || (codec == "utf32le") || (codec == "utf-32le"))
            return true;
    }

    return false;
}

inline bool is_ucs4_s(exlib::string codec)
{
    if (!is_big_endian()) {
        if ((codec == "ucs4be") || (codec == "ucs-4be")
            || (codec == "utf32be") || (codec == "utf-32be"))
            return true;
    } else {
        if ((codec == "ucs4le") || (codec == "ucs-4le")
            || (codec == "utf32le") || (codec == "utf-32le"))
            return true;
    }

    return false;
}

result_t encoding_iconv::encode(exlib::string data, exlib::string& retVal)
{
    if ((m_charset == "utf8") || (m_charset == "utf-8")) {
        retVal = data;
        return 0;
    }

    if ((m_charset == "binary") || (m_charset == "latin1")) {
        exlib::wstring wdata = utf8to16String(data);
        size_t sz = wdata.length();
        const exlib::wchar* s = wdata.c_str();

        retVal.resize(sz);
        char* s1 = retVal.c_buffer();
        for (size_t i = 0; i < sz; i++)
            *s1++ = (char)*s++;
        return 0;
    }

    if (is_ucs2(m_charset)) {
        ssize_t n = utf_convert(data.c_str(), data.length(), (exlib::wchar*)NULL, 0);
        retVal.resize(n * sizeof(exlib::wchar));
        utf_convert(data.c_str(), data.length(), (exlib::wchar*)retVal.c_buffer(), n);

        return 0;
    }

    if (is_ucs4(m_charset)) {
        ssize_t n = utf_convert(data.c_str(), data.length(), (exlib::wchar32*)NULL, 0);
        retVal.resize(n * sizeof(exlib::wchar32));
        utf_convert(data.c_str(), data.length(), (exlib::wchar32*)retVal.c_buffer(), n);

        return 0;
    }

    if (is_ucs2_s(m_charset)) {
        ssize_t n = utf_convert_s(data.c_str(), data.length(), (exlib::wchar*)NULL, 0);
        retVal.resize(n * sizeof(exlib::wchar));
        utf_convert_s(data.c_str(), data.length(), (exlib::wchar*)retVal.c_buffer(), n);

        return 0;
    }

    if (is_ucs4_s(m_charset)) {
        ssize_t n = utf_convert_s(data.c_str(), data.length(), (exlib::wchar32*)NULL, 0);
        retVal.resize(n * sizeof(exlib::wchar32));
        utf_convert_s(data.c_str(), data.length(), (exlib::wchar32*)retVal.c_buffer(), n);

        return 0;
    }

    if (!m_iconv_en) {
        m_iconv_en = _iconv_open(m_charset.c_str(), "utf-8");
        if (m_iconv_en == (iconv_t)(-1)) {
            m_iconv_en = NULL;
            return CHECK_ERROR(Runtime::setError("encoding: Unknown charset."));
        }
    }

    const char* _data = data.c_str();
    size_t sz = data.length();

    retVal.resize(sz * 2);
    char* output_buf = retVal.c_buffer();
    size_t output_size = retVal.length();

    size_t n = _iconv((iconv_t)m_iconv_en, &_data, &sz, &output_buf, &output_size);

    if (n == (size_t)-1)
        return CHECK_ERROR(Runtime::setError("encoding: convert error."));

    retVal.resize(retVal.length() - output_size);

    return 0;
}

result_t encoding_iconv::encode(exlib::string data, obj_ptr<Buffer_base>& retVal)
{
    exlib::string strBuf;

    result_t hr = encode(data, strBuf);
    if (hr < 0)
        return hr;

    retVal = new Buffer(strBuf);

    return 0;
}

result_t encoding_iconv::decode(const exlib::string& data, exlib::string& retVal)
{
    if ((m_charset == "utf8") || (m_charset == "utf-8")) {
        retVal = data;
        return 0;
    }

    if ((m_charset == "binary") || (m_charset == "latin1")) {
        size_t sz = data.length();
        const char* s = data.c_str();

        exlib::wstring wdata;
        wdata.resize(sz);
        exlib::wchar* s1 = wdata.c_buffer();
        for (size_t i = 0; i < sz; i++)
            *s1++ = *s++;

        retVal = utf16to8String(wdata);
        return 0;
    }

    if (is_ucs2(m_charset)) {
        retVal = utf16to8String((const exlib::wchar*)data.c_str(), data.length() / sizeof(exlib::wchar));
        return 0;
    }

    if (is_ucs4(m_charset)) {
        retVal = utf32to8String((const exlib::wchar32*)data.c_str(), data.length() / sizeof(exlib::wchar32));
        return 0;
    }

    if (is_ucs2_s(m_charset)) {
        retVal = utf16to8String_s((const exlib::wchar*)data.c_str(), data.length() / sizeof(exlib::wchar));
        return 0;
    }

    if (is_ucs4_s(m_charset)) {
        retVal = utf32to8String_s((const exlib::wchar32*)data.c_str(), data.length() / sizeof(exlib::wchar32));
        return 0;
    }

    if (!m_iconv_de) {
        m_iconv_de = _iconv_open("utf-8", m_charset.c_str());
        if (m_iconv_de == (iconv_t)(-1)) {
            m_iconv_de = NULL;
            return CHECK_ERROR(Runtime::setError("encoding: Unknown charset."));
        }
    }

    size_t sz = data.length();
    const char* ptr = data.c_str();
    exlib::string strBuf;

    strBuf.resize(sz * 2);
    char* output_buf = strBuf.c_buffer();
    size_t output_size = strBuf.length();

    size_t n = _iconv((iconv_t)m_iconv_de, &ptr, &sz, &output_buf, &output_size);

    if (n == (size_t)-1)
        return CHECK_ERROR(Runtime::setError("encoding: convert error."));

    strBuf.resize(strBuf.length() - output_size);

    retVal = strBuf;

    return 0;
}

result_t encoding_iconv::decode(Buffer_base* data, exlib::string& retVal)
{
    exlib::string strData;
    data->toString(strData);

    return decode(strData, retVal);
}

result_t encoding_iconv::isEncoding(bool& retVal)
{
    if ((m_charset == "utf8") || (m_charset == "utf-8")

        || (m_charset == "ucs2") || (m_charset == "ucs-2")
        || (m_charset == "utf16") || (m_charset == "utf-16")

        || (m_charset == "ucs2le") || (m_charset == "ucs-2le")
        || (m_charset == "utf16le") || (m_charset == "utf-16le")

        || (m_charset == "ucs2be") || (m_charset == "ucs-2be")
        || (m_charset == "utf16be") || (m_charset == "utf-16be")

        || (m_charset == "ucs4") || (m_charset == "ucs-4")
        || (m_charset == "utf32") || (m_charset == "utf-32")

        || (m_charset == "ucs4le") || (m_charset == "ucs-4le")
        || (m_charset == "utf32le") || (m_charset == "utf-32le")

        || (m_charset == "ucs4be") || (m_charset == "ucs-4be")
        || (m_charset == "utf32be") || (m_charset == "utf-32be")) {
        retVal = true;
        return 0;
    }

    if (m_charset == "binary")
        m_charset = "latin1";

    if (!m_iconv_ec) {
        m_iconv_ec = _iconv_open(m_charset.c_str(), "utf-8");
        if (m_iconv_ec == (iconv_t)(-1)) {
            m_iconv_ec = NULL;
            retVal = false;
            return 0;
        }
    }
    retVal = true;
    return 0;
}

result_t iconv_base::encode(exlib::string charset, exlib::string data,
    obj_ptr<Buffer_base>& retVal)
{
    return encoding_iconv(charset).encode(data, retVal);
}

result_t iconv_base::decode(exlib::string charset, Buffer_base* data,
    exlib::string& retVal)
{
    return encoding_iconv(charset).decode(data, retVal);
}

result_t iconv_base::isEncoding(exlib::string charset, bool& retVal)
{
    return encoding_iconv(charset).isEncoding(retVal);
}
}
