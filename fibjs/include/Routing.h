/*
 * Routing.h
 *
 *  Created on: Aug 26, 2012
 *      Author: lion
 */

#pragma once

#include "ifs/Routing.h"
#include <pcre/pcre.h>
#include <vector>

namespace fibjs {

class Routing : public Routing_base {
public:
    class rule : public obj_base {
    public:
        rule(exlib::string method, pcre* re, Handler_base* hdlr, bool bSub)
            : m_method(method)
            , m_re(re)
            , m_hdlr(hdlr)
            , m_bSub(bSub)
        {
        }

        ~rule()
        {
            pcre_free(m_re);
        }

    public:
        exlib::string m_method;
        pcre* m_re;
        obj_ptr<Handler_base> m_hdlr;
        bool m_bSub;
    };

public:
    // Handler_base
    virtual result_t invoke(object_base* v,
        obj_ptr<Handler_base>& retVal, AsyncEvent* ac);

public:
    // Routing_base
    virtual result_t append(Routing_base* route, obj_ptr<Routing_base>& retVal);
    virtual result_t append(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    virtual result_t append(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);
    virtual result_t append(exlib::string method, exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);
    virtual result_t _host(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    virtual result_t _host(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);
    virtual result_t all(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    virtual result_t all(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);
    virtual result_t get(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    virtual result_t get(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);
    virtual result_t post(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    virtual result_t post(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);
    virtual result_t del(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    virtual result_t del(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);
    virtual result_t put(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    virtual result_t put(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);
    virtual result_t patch(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    virtual result_t patch(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);
    virtual result_t find(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    virtual result_t find(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal);

public:
    result_t _append(exlib::string method, v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal);
    static exlib::string host2RegExp(exlib::string pattern);
    static exlib::string path2RegExp(exlib::string pattern);

private:
    std::vector<obj_ptr<rule>> m_array;
};

} /* namespace fibjs */
