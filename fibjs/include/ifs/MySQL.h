/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef _MySQL_base_H_
#define _MySQL_base_H_

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"
#include "ifs/DbConnection.h"

namespace fibjs {

class DbConnection_base;

class MySQL_base : public DbConnection_base {
    DECLARE_CLASS(MySQL_base);

public:
    // MySQL_base
    virtual result_t use(exlib::string dbName, AsyncEvent* ac) = 0;
    virtual result_t get_rxBufferSize(int32_t& retVal) = 0;
    virtual result_t set_rxBufferSize(int32_t newVal) = 0;
    virtual result_t get_txBufferSize(int32_t& retVal) = 0;
    virtual result_t set_txBufferSize(int32_t newVal) = 0;

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        CONSTRUCT_INIT();

        Isolate* isolate = Isolate::current();

        isolate->m_isolate->ThrowException(
            isolate->NewString("not a constructor"));
    }

public:
    static void s_use(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get_rxBufferSize(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_set_rxBufferSize(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args);
    static void s_get_txBufferSize(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_set_txBufferSize(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args);

public:
    ASYNC_MEMBER1(MySQL_base, use, exlib::string);
};
}

namespace fibjs {
inline ClassInfo& MySQL_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "use", s_use, false },
        { "useSync", s_use, false }
    };

    static ClassData::ClassProperty s_property[] = {
        { "rxBufferSize", s_get_rxBufferSize, s_set_rxBufferSize, false },
        { "txBufferSize", s_get_txBufferSize, s_set_txBufferSize, false }
    };

    static ClassData s_cd = {
        "MySQL", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &DbConnection_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void MySQL_base::s_use(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("MySQL.use");
    METHOD_INSTANCE(MySQL_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(exlib::string, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_use(v0, cb, args);
    else
        hr = pInst->ac_use(v0);

    METHOD_VOID();
}

inline void MySQL_base::s_get_rxBufferSize(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("MySQL.rxBufferSize");
    METHOD_INSTANCE(MySQL_base);
    PROPERTY_ENTER();

    hr = pInst->get_rxBufferSize(vr);

    METHOD_RETURN();
}

inline void MySQL_base::s_set_rxBufferSize(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args)
{
    METHOD_NAME("MySQL.rxBufferSize");
    METHOD_INSTANCE(MySQL_base);
    PROPERTY_ENTER();
    PROPERTY_VAL(int32_t);

    hr = pInst->set_rxBufferSize(v0);

    PROPERTY_SET_LEAVE();
}

inline void MySQL_base::s_get_txBufferSize(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("MySQL.txBufferSize");
    METHOD_INSTANCE(MySQL_base);
    PROPERTY_ENTER();

    hr = pInst->get_txBufferSize(vr);

    METHOD_RETURN();
}

inline void MySQL_base::s_set_txBufferSize(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args)
{
    METHOD_NAME("MySQL.txBufferSize");
    METHOD_INSTANCE(MySQL_base);
    PROPERTY_ENTER();
    PROPERTY_VAL(int32_t);

    hr = pInst->set_txBufferSize(v0);

    PROPERTY_SET_LEAVE();
}
}

#endif
