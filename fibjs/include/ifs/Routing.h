/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#pragma once

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"
#include "ifs/Handler.h"

namespace fibjs {

class Handler_base;

class Routing_base : public Handler_base {
    DECLARE_CLASS(Routing_base);

public:
    // Routing_base
    static result_t _new(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    static result_t _new(exlib::string method, v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    virtual result_t append(Routing_base* route, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t append(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t append(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t append(exlib::string method, exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t _host(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t _host(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t all(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t all(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t get(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t get(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t post(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t post(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t del(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t del(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t put(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t put(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t patch(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t patch(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t find(v8::Local<v8::Object> map, obj_ptr<Routing_base>& retVal) = 0;
    virtual result_t find(exlib::string pattern, Handler_base* hdlr, obj_ptr<Routing_base>& retVal) = 0;

public:
    template <typename T>
    static void __new(const T& args);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_append(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s__host(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_all(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_post(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_del(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_put(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_patch(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_find(const v8::FunctionCallbackInfo<v8::Value>& args);
};
}

namespace fibjs {
inline ClassInfo& Routing_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "append", s_append, false },
        { "host", s__host, false },
        { "all", s_all, false },
        { "get", s_get, false },
        { "post", s_post, false },
        { "del", s_del, false },
        { "put", s_put, false },
        { "patch", s_patch, false },
        { "find", s_find, false }
    };

    static ClassData s_cd = {
        "Routing", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, 0, NULL, 0, NULL, NULL, NULL,
        &Handler_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void Routing_base::s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CONSTRUCT_INIT();
    __new(args);
}

template <typename T>
void Routing_base::__new(const T& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("new Routing()");
    CONSTRUCT_ENTER();

    METHOD_OVER(1, 0);

    OPT_ARG(v8::Local<v8::Object>, 0, v8::Object::New(isolate));

    hr = _new(v0, vr, args.This());

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(v8::Local<v8::Object>, 1);

    hr = _new(v0, v1, vr, args.This());

    CONSTRUCT_RETURN();
}

inline void Routing_base::s_append(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("Routing.append");
    METHOD_INSTANCE(Routing_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(obj_ptr<Routing_base>, 0);

    hr = pInst->append(v0, vr);

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->append(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(obj_ptr<Handler_base>, 1);

    hr = pInst->append(v0, v1, vr);

    METHOD_OVER(3, 3);

    ARG(exlib::string, 0);
    ARG(exlib::string, 1);
    ARG(obj_ptr<Handler_base>, 2);

    hr = pInst->append(v0, v1, v2, vr);

    METHOD_RETURN();
}

inline void Routing_base::s__host(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("Routing.host");
    METHOD_INSTANCE(Routing_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->_host(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(obj_ptr<Handler_base>, 1);

    hr = pInst->_host(v0, v1, vr);

    METHOD_RETURN();
}

inline void Routing_base::s_all(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("Routing.all");
    METHOD_INSTANCE(Routing_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->all(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(obj_ptr<Handler_base>, 1);

    hr = pInst->all(v0, v1, vr);

    METHOD_RETURN();
}

inline void Routing_base::s_get(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("Routing.get");
    METHOD_INSTANCE(Routing_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->get(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(obj_ptr<Handler_base>, 1);

    hr = pInst->get(v0, v1, vr);

    METHOD_RETURN();
}

inline void Routing_base::s_post(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("Routing.post");
    METHOD_INSTANCE(Routing_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->post(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(obj_ptr<Handler_base>, 1);

    hr = pInst->post(v0, v1, vr);

    METHOD_RETURN();
}

inline void Routing_base::s_del(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("Routing.del");
    METHOD_INSTANCE(Routing_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->del(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(obj_ptr<Handler_base>, 1);

    hr = pInst->del(v0, v1, vr);

    METHOD_RETURN();
}

inline void Routing_base::s_put(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("Routing.put");
    METHOD_INSTANCE(Routing_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->put(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(obj_ptr<Handler_base>, 1);

    hr = pInst->put(v0, v1, vr);

    METHOD_RETURN();
}

inline void Routing_base::s_patch(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("Routing.patch");
    METHOD_INSTANCE(Routing_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->patch(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(obj_ptr<Handler_base>, 1);

    hr = pInst->patch(v0, v1, vr);

    METHOD_RETURN();
}

inline void Routing_base::s_find(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<Routing_base> vr;

    METHOD_NAME("Routing.find");
    METHOD_INSTANCE(Routing_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->find(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(obj_ptr<Handler_base>, 1);

    hr = pInst->find(v0, v1, vr);

    METHOD_RETURN();
}
}
