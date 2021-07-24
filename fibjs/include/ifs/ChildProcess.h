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
class Stream_base;

class ChildProcess_base : public EventEmitter_base {
    DECLARE_CLASS(ChildProcess_base);

public:
    // ChildProcess_base
    virtual result_t kill(int32_t signal) = 0;
    virtual result_t join(AsyncEvent* ac) = 0;
    virtual result_t get_pid(int32_t& retVal) = 0;
    virtual result_t get_exitCode(int32_t& retVal) = 0;
    virtual result_t get_stdin(obj_ptr<Stream_base>& retVal) = 0;
    virtual result_t get_stdout(obj_ptr<Stream_base>& retVal) = 0;
    virtual result_t get_stderr(obj_ptr<Stream_base>& retVal) = 0;
    virtual result_t get_onexit(v8::Local<v8::Function>& retVal) = 0;
    virtual result_t set_onexit(v8::Local<v8::Function> newVal) = 0;

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        CONSTRUCT_INIT();

        Isolate* isolate = Isolate::current();

        isolate->m_isolate->ThrowException(
            isolate->NewString("not a constructor"));
    }

public:
    static void s_kill(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_join(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get_pid(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_exitCode(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_stdin(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_stdout(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_stderr(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_onexit(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_set_onexit(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args);

public:
    ASYNC_MEMBER0(ChildProcess_base, join);
};
}

#include "ifs/Stream.h"

namespace fibjs {
inline ClassInfo& ChildProcess_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "kill", s_kill, false },
        { "join", s_join, false },
        { "joinSync", s_join, false }
    };

    static ClassData::ClassProperty s_property[] = {
        { "pid", s_get_pid, block_set, false },
        { "exitCode", s_get_exitCode, block_set, false },
        { "stdin", s_get_stdin, block_set, false },
        { "stdout", s_get_stdout, block_set, false },
        { "stderr", s_get_stderr, block_set, false },
        { "onexit", s_get_onexit, s_set_onexit, false }
    };

    static ClassData s_cd = {
        "ChildProcess", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &EventEmitter_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void ChildProcess_base::s_kill(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("ChildProcess.kill");
    METHOD_INSTANCE(ChildProcess_base);
    METHOD_ENTER();

    METHOD_OVER(1, 1);

    ARG(int32_t, 0);

    hr = pInst->kill(v0);

    METHOD_VOID();
}

inline void ChildProcess_base::s_join(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("ChildProcess.join");
    METHOD_INSTANCE(ChildProcess_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(0, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_join(cb, args);
    else
        hr = pInst->ac_join();

    METHOD_VOID();
}

inline void ChildProcess_base::s_get_pid(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("ChildProcess.pid");
    METHOD_INSTANCE(ChildProcess_base);
    PROPERTY_ENTER();

    hr = pInst->get_pid(vr);

    METHOD_RETURN();
}

inline void ChildProcess_base::s_get_exitCode(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("ChildProcess.exitCode");
    METHOD_INSTANCE(ChildProcess_base);
    PROPERTY_ENTER();

    hr = pInst->get_exitCode(vr);

    METHOD_RETURN();
}

inline void ChildProcess_base::s_get_stdin(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<Stream_base> vr;

    METHOD_NAME("ChildProcess.stdin");
    METHOD_INSTANCE(ChildProcess_base);
    PROPERTY_ENTER();

    hr = pInst->get_stdin(vr);

    METHOD_RETURN();
}

inline void ChildProcess_base::s_get_stdout(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<Stream_base> vr;

    METHOD_NAME("ChildProcess.stdout");
    METHOD_INSTANCE(ChildProcess_base);
    PROPERTY_ENTER();

    hr = pInst->get_stdout(vr);

    METHOD_RETURN();
}

inline void ChildProcess_base::s_get_stderr(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<Stream_base> vr;

    METHOD_NAME("ChildProcess.stderr");
    METHOD_INSTANCE(ChildProcess_base);
    PROPERTY_ENTER();

    hr = pInst->get_stderr(vr);

    METHOD_RETURN();
}

inline void ChildProcess_base::s_get_onexit(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    v8::Local<v8::Function> vr;

    METHOD_NAME("ChildProcess.onexit");
    METHOD_INSTANCE(ChildProcess_base);
    PROPERTY_ENTER();

    hr = pInst->get_onexit(vr);

    METHOD_RETURN();
}

inline void ChildProcess_base::s_set_onexit(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args)
{
    METHOD_NAME("ChildProcess.onexit");
    METHOD_INSTANCE(ChildProcess_base);
    PROPERTY_ENTER();
    PROPERTY_VAL(v8::Local<v8::Function>);

    hr = pInst->set_onexit(v0);

    PROPERTY_SET_LEAVE();
}
}
