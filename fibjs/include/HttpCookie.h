/*
 * HttpCookie.h
 *
 *  Created on: Aug 23, 2014
 *      Author: lion
 */

#pragma once

#include "ifs/HttpCookie.h"

namespace fibjs {

class HttpCookie : public HttpCookie_base {
public:
    HttpCookie()
        : m_path("/")
        , m_httpOnly(false)
        , m_secure(false)
    {
    }

public:
    // HttpCookie_base
    virtual result_t parse(exlib::string header);
    virtual result_t match(exlib::string url, bool& retVal);
    virtual result_t get_name(exlib::string& retVal);
    virtual result_t set_name(exlib::string newVal);
    virtual result_t get_value(exlib::string& retVal);
    virtual result_t set_value(exlib::string newVal);
    virtual result_t get_domain(exlib::string& retVal);
    virtual result_t set_domain(exlib::string newVal);
    virtual result_t get_path(exlib::string& retVal);
    virtual result_t set_path(exlib::string newVal);
    virtual result_t get_expires(date_t& retVal);
    virtual result_t set_expires(date_t newVal);
    virtual result_t get_httpOnly(bool& retVal);
    virtual result_t set_httpOnly(bool newVal);
    virtual result_t get_secure(bool& retVal);
    virtual result_t set_secure(bool newVal);

public:
    // object_base
    virtual result_t toString(exlib::string& retVal);

public:
    result_t fill(v8::Local<v8::Object> opts, bool bBase);

private:
    exlib::string m_name;
    exlib::string m_value;
    exlib::string m_domain;
    exlib::string m_path;
    date_t m_expires;
    bool m_httpOnly;
    bool m_secure;
};

} /* namespace fibjs */
