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
#include "ifs/EventEmitter.h"

namespace fibjs {

class EventEmitter_base;

class LruCache_base : public EventEmitter_base {
    DECLARE_CLASS(LruCache_base);

public:
    // LruCache_base
    static result_t _new(int32_t size, int32_t timeout, obj_ptr<LruCache_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    virtual result_t get_size(int32_t& retVal) = 0;
    virtual result_t get_timeout(int32_t& retVal) = 0;
    virtual result_t set_timeout(int32_t newVal) = 0;
    virtual result_t clear() = 0;
    virtual result_t has(exlib::string name, bool& retVal) = 0;
    virtual result_t get(exlib::string name, v8::Local<v8::Value>& retVal) = 0;
    virtual result_t get(exlib::string name, v8::Local<v8::Function> updater, v8::Local<v8::Value>& retVal) = 0;
    virtual result_t set(exlib::string name, v8::Local<v8::Value> value) = 0;
    virtual result_t set(v8::Local<v8::Object> map) = 0;
    virtual result_t remove(exlib::string name) = 0;
    virtual result_t isEmpty(bool& retVal) = 0;
    virtual result_t get_onexpire(v8::Local<v8::Function>& retVal) = 0;
    virtual result_t set_onexpire(v8::Local<v8::Function> newVal) = 0;

public:
    template <typename T>
    static void __new(const T& args);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get_size(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_timeout(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_set_timeout(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args);
    static void s_clear(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_has(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_set(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_remove(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_isEmpty(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get_onexpire(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_set_onexpire(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args);
};
}

namespace fibjs {
inline ClassInfo& LruCache_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "clear", s_clear, false },
        { "has", s_has, false },
        { "get", s_get, false },
        { "set", s_set, false },
        { "remove", s_remove, false },
        { "isEmpty", s_isEmpty, false }
    };

    static ClassData::ClassProperty s_property[] = {
        { "size", s_get_size, block_set, false },
        { "timeout", s_get_timeout, s_set_timeout, false },
        { "onexpire", s_get_onexpire, s_set_onexpire, false }
    };

    static ClassData s_cd = {
        "LruCache", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &EventEmitter_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void LruCache_base::s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CONSTRUCT_INIT();
    __new(args);
}

template <typename T>
void LruCache_base::__new(const T& args)
{
    obj_ptr<LruCache_base> vr;

    METHOD_NAME("new LruCache()");
    CONSTRUCT_ENTER();

    METHOD_OVER(2, 1);

    ARG(int32_t, 0);
    OPT_ARG(int32_t, 1, 0);

    hr = _new(v0, v1, vr, args.This());

    CONSTRUCT_RETURN();
}

inline void LruCache_base::s_get_size(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("LruCache.size");
    METHOD_INSTANCE(LruCache_base);
    PROPERTY_ENTER();

    hr = pInst->get_size(vr);

    METHOD_RETURN();
}

inline void LruCache_base::s_get_timeout(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("LruCache.timeout");
    METHOD_INSTANCE(LruCache_base);
    PROPERTY_ENTER();

    hr = pInst->get_timeout(vr);

    METHOD_RETURN();
}

inline void LruCache_base::s_set_timeout(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args)
{
    METHOD_NAME("LruCache.timeout");
    METHOD_INSTANCE(LruCache_base);
    PROPERTY_ENTER();
    PROPERTY_VAL(int32_t);

    hr = pInst->set_timeout(v0);

    PROPERTY_SET_LEAVE();
}

inline void LruCache_base::s_clear(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("LruCache.clear");
    METHOD_INSTANCE(LruCache_base);
    METHOD_ENTER();

    METHOD_OVER(0, 0);

    hr = pInst->clear();

    METHOD_VOID();
}

inline void LruCache_base::s_has(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    bool vr;

    METHOD_NAME("LruCache.has");
    METHOD_INSTANCE(LruCache_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->has(v0, vr);

    METHOD_RETURN();
}

inline void LruCache_base::s_get(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::Local<v8::Value> vr;

    METHOD_NAME("LruCache.get");
    METHOD_INSTANCE(LruCache_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->get(v0, vr);

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(v8::Local<v8::Function>, 1);

    hr = pInst->get(v0, v1, vr);

    METHOD_RETURN();
}

inline void LruCache_base::s_set(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("LruCache.set");
    METHOD_INSTANCE(LruCache_base);
    METHOD_ENTER();

    METHOD_OVER(2, 2);

    ARG(exlib::string, 0);
    ARG(v8::Local<v8::Value>, 1);

    hr = pInst->set(v0, v1);

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = pInst->set(v0);

    METHOD_VOID();
}

inline void LruCache_base::s_remove(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("LruCache.remove");
    METHOD_INSTANCE(LruCache_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    hr = pInst->remove(v0);

    METHOD_VOID();
}

inline void LruCache_base::s_isEmpty(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    bool vr;

    METHOD_NAME("LruCache.isEmpty");
    METHOD_INSTANCE(LruCache_base);
    METHOD_ENTER();

    METHOD_OVER(0, 0);

    hr = pInst->isEmpty(vr);

    METHOD_RETURN();
}

inline void LruCache_base::s_get_onexpire(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    v8::Local<v8::Function> vr;

    METHOD_NAME("LruCache.onexpire");
    METHOD_INSTANCE(LruCache_base);
    PROPERTY_ENTER();

    hr = pInst->get_onexpire(vr);

    METHOD_RETURN();
}

inline void LruCache_base::s_set_onexpire(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args)
{
    METHOD_NAME("LruCache.onexpire");
    METHOD_INSTANCE(LruCache_base);
    PROPERTY_ENTER();
    PROPERTY_VAL(v8::Local<v8::Function>);

    hr = pInst->set_onexpire(v0);

    PROPERTY_SET_LEAVE();
}
}
