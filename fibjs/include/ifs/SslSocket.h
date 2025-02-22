/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef _SslSocket_base_H_
#define _SslSocket_base_H_

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"
#include "ifs/Stream.h"

namespace fibjs {

class Stream_base;
class X509Cert_base;
class PKey_base;

class SslSocket_base : public Stream_base {
    DECLARE_CLASS(SslSocket_base);

public:
    // SslSocket_base
    static result_t _new(v8::Local<v8::Array> certs, obj_ptr<SslSocket_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    static result_t _new(X509Cert_base* crt, PKey_base* key, obj_ptr<SslSocket_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    virtual result_t get_verification(int32_t& retVal) = 0;
    virtual result_t set_verification(int32_t newVal) = 0;
    virtual result_t get_ca(obj_ptr<X509Cert_base>& retVal) = 0;
    virtual result_t get_peerCert(obj_ptr<X509Cert_base>& retVal) = 0;
    virtual result_t get_hostname(exlib::string& retVal) = 0;
    virtual result_t get_stream(obj_ptr<Stream_base>& retVal) = 0;
    virtual result_t connect(Stream_base* s, exlib::string server_name, int32_t& retVal, AsyncEvent* ac) = 0;
    virtual result_t accept(Stream_base* s, obj_ptr<SslSocket_base>& retVal, AsyncEvent* ac) = 0;

public:
    template <typename T>
    static void __new(const T& args);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_get_verification(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_set_verification(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args);
    static void s_get_ca(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_peerCert(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_hostname(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_get_stream(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
    static void s_connect(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_accept(const v8::FunctionCallbackInfo<v8::Value>& args);

public:
    ASYNC_MEMBERVALUE3(SslSocket_base, connect, Stream_base*, exlib::string, int32_t);
    ASYNC_MEMBERVALUE2(SslSocket_base, accept, Stream_base*, obj_ptr<SslSocket_base>);
};
}

#include "ifs/X509Cert.h"
#include "ifs/PKey.h"

namespace fibjs {
inline ClassInfo& SslSocket_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "connect", s_connect, false },
        { "connectSync", s_connect, false },
        { "accept", s_accept, false },
        { "acceptSync", s_accept, false }
    };

    static ClassData::ClassProperty s_property[] = {
        { "verification", s_get_verification, s_set_verification, false },
        { "ca", s_get_ca, block_set, false },
        { "peerCert", s_get_peerCert, block_set, false },
        { "hostname", s_get_hostname, block_set, false },
        { "stream", s_get_stream, block_set, false }
    };

    static ClassData s_cd = {
        "SslSocket", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &Stream_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void SslSocket_base::s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CONSTRUCT_INIT();
    __new(args);
}

template <typename T>
void SslSocket_base::__new(const T& args)
{
    obj_ptr<SslSocket_base> vr;

    METHOD_NAME("new SslSocket()");
    CONSTRUCT_ENTER();

    METHOD_OVER(1, 0);

    OPT_ARG(v8::Local<v8::Array>, 0, v8::Array::New(isolate));

    hr = _new(v0, vr, args.This());

    METHOD_OVER(2, 2);

    ARG(obj_ptr<X509Cert_base>, 0);
    ARG(obj_ptr<PKey_base>, 1);

    hr = _new(v0, v1, vr, args.This());

    CONSTRUCT_RETURN();
}

inline void SslSocket_base::s_get_verification(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("SslSocket.verification");
    METHOD_INSTANCE(SslSocket_base);
    PROPERTY_ENTER();

    hr = pInst->get_verification(vr);

    METHOD_RETURN();
}

inline void SslSocket_base::s_set_verification(v8::Local<v8::Name> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& args)
{
    METHOD_NAME("SslSocket.verification");
    METHOD_INSTANCE(SslSocket_base);
    PROPERTY_ENTER();
    PROPERTY_VAL(int32_t);

    hr = pInst->set_verification(v0);

    PROPERTY_SET_LEAVE();
}

inline void SslSocket_base::s_get_ca(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<X509Cert_base> vr;

    METHOD_NAME("SslSocket.ca");
    METHOD_INSTANCE(SslSocket_base);
    PROPERTY_ENTER();

    hr = pInst->get_ca(vr);

    METHOD_RETURN();
}

inline void SslSocket_base::s_get_peerCert(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<X509Cert_base> vr;

    METHOD_NAME("SslSocket.peerCert");
    METHOD_INSTANCE(SslSocket_base);
    PROPERTY_ENTER();

    hr = pInst->get_peerCert(vr);

    METHOD_RETURN();
}

inline void SslSocket_base::s_get_hostname(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    exlib::string vr;

    METHOD_NAME("SslSocket.hostname");
    METHOD_INSTANCE(SslSocket_base);
    PROPERTY_ENTER();

    hr = pInst->get_hostname(vr);

    METHOD_RETURN();
}

inline void SslSocket_base::s_get_stream(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    obj_ptr<Stream_base> vr;

    METHOD_NAME("SslSocket.stream");
    METHOD_INSTANCE(SslSocket_base);
    PROPERTY_ENTER();

    hr = pInst->get_stream(vr);

    METHOD_RETURN();
}

inline void SslSocket_base::s_connect(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    int32_t vr;

    METHOD_NAME("SslSocket.connect");
    METHOD_INSTANCE(SslSocket_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(2, 1);

    ARG(obj_ptr<Stream_base>, 0);
    OPT_ARG(exlib::string, 1, "");

    if (!cb.IsEmpty())
        hr = pInst->acb_connect(v0, v1, cb, args);
    else
        hr = pInst->ac_connect(v0, v1, vr);

    METHOD_RETURN();
}

inline void SslSocket_base::s_accept(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    obj_ptr<SslSocket_base> vr;

    METHOD_NAME("SslSocket.accept");
    METHOD_INSTANCE(SslSocket_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(1, 1);

    ARG(obj_ptr<Stream_base>, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_accept(v0, cb, args);
    else
        hr = pInst->ac_accept(v0, vr);

    METHOD_RETURN();
}
}

#endif
