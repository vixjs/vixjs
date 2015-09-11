/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef _websocket_base_H_
#define _websocket_base_H_

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"

namespace fibjs
{

class WebSocketMessage_base;
class WebSocketHandler_base;
class Socket_base;

class websocket_base : public object_base
{
    DECLARE_CLASS(websocket_base);

public:
    enum{
        _CONTINUE = 0,
        _TEXT = 1,
        _BINARY = 2,
        _CLOSE = 8,
        _PING = 9,
        _PONG = 10
    };

public:
    // websocket_base
    static result_t connect(const char* url, obj_ptr<Socket_base>& retVal, AsyncEvent* ac);

public:
    static void s_get_CONTINUE(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args);
    static void s_get_TEXT(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args);
    static void s_get_BINARY(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args);
    static void s_get_CLOSE(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args);
    static void s_get_PING(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args);
    static void s_get_PONG(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args);
    static void s_connect(const v8::FunctionCallbackInfo<v8::Value>& args);

public:
    ASYNC_STATICVALUE2(websocket_base, connect, const char*, obj_ptr<Socket_base>);
};

}

#include "WebSocketMessage.h"
#include "WebSocketHandler.h"
#include "Socket.h"

namespace fibjs
{
    inline ClassInfo& websocket_base::class_info()
    {
        static ClassData::ClassMethod s_method[] = 
        {
            {"connect", s_connect, true}
        };

        static ClassData::ClassObject s_object[] = 
        {
            {"Message", WebSocketMessage_base::class_info},
            {"Handler", WebSocketHandler_base::class_info}
        };

        static ClassData::ClassProperty s_property[] = 
        {
            {"CONTINUE", s_get_CONTINUE, block_set, true},
            {"TEXT", s_get_TEXT, block_set, true},
            {"BINARY", s_get_BINARY, block_set, true},
            {"CLOSE", s_get_CLOSE, block_set, true},
            {"PING", s_get_PING, block_set, true},
            {"PONG", s_get_PONG, block_set, true}
        };

        static ClassData s_cd = 
        { 
            "websocket", NULL, 
            1, s_method, 2, s_object, 6, s_property, NULL, NULL,
            NULL
        };

        static ClassInfo s_ci(s_cd);
        return s_ci;
    }

    inline void websocket_base::s_get_CONTINUE(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args)
    {
        int32_t vr = _CONTINUE;
        PROPERTY_ENTER();
        METHOD_RETURN();
    }

    inline void websocket_base::s_get_TEXT(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args)
    {
        int32_t vr = _TEXT;
        PROPERTY_ENTER();
        METHOD_RETURN();
    }

    inline void websocket_base::s_get_BINARY(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args)
    {
        int32_t vr = _BINARY;
        PROPERTY_ENTER();
        METHOD_RETURN();
    }

    inline void websocket_base::s_get_CLOSE(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args)
    {
        int32_t vr = _CLOSE;
        PROPERTY_ENTER();
        METHOD_RETURN();
    }

    inline void websocket_base::s_get_PING(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args)
    {
        int32_t vr = _PING;
        PROPERTY_ENTER();
        METHOD_RETURN();
    }

    inline void websocket_base::s_get_PONG(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value> &args)
    {
        int32_t vr = _PONG;
        PROPERTY_ENTER();
        METHOD_RETURN();
    }

    inline void websocket_base::s_connect(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        obj_ptr<Socket_base> vr;

        METHOD_ENTER(1, 1);

        ARG(arg_string, 0);

        hr = ac_connect(v0, vr);

        METHOD_RETURN();
    }

}

#endif
