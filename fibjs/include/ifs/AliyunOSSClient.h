/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef _AliyunOSSClient_base_H_
#define _AliyunOSSClient_base_H_

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"

namespace fibjs {

class AliyunOSSClient_base : public object_base {
    DECLARE_CLASS(AliyunOSSClient_base);

public:
    // AliyunOSSClient_base
    static result_t _new(v8::Local<v8::Object> config, obj_ptr<AliyunOSSClient_base>& retVal, v8::Local<v8::Object> This = v8::Local<v8::Object>());
    virtual result_t ListBuckets(AsyncEvent* ac) = 0;

public:
    template <typename T>
    static void __new(const T& args);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void s_ListBuckets(const v8::FunctionCallbackInfo<v8::Value>& args);

public:
    ASYNC_MEMBER0(AliyunOSSClient_base, ListBuckets);
};
}

namespace fibjs {
inline ClassInfo& AliyunOSSClient_base::class_info()
{
    static ClassData::ClassMethod s_method[] = {
        { "ListBuckets", s_ListBuckets, false },
        { "ListBucketsSync", s_ListBuckets, false }
    };

    static ClassData s_cd = {
        "AliyunOSSClient", false, s__new, NULL,
        ARRAYSIZE(s_method), s_method, 0, NULL, 0, NULL, 0, NULL, NULL, NULL,
        &object_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void AliyunOSSClient_base::s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CONSTRUCT_INIT();
    __new(args);
}

template <typename T>
void AliyunOSSClient_base::__new(const T& args)
{
    obj_ptr<AliyunOSSClient_base> vr;

    METHOD_NAME("new AliyunOSSClient()");
    CONSTRUCT_ENTER();

    METHOD_OVER(1, 1);

    ARG(v8::Local<v8::Object>, 0);

    hr = _new(v0, vr, args.This());

    CONSTRUCT_RETURN();
}

inline void AliyunOSSClient_base::s_ListBuckets(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    METHOD_NAME("AliyunOSSClient.ListBuckets");
    METHOD_INSTANCE(AliyunOSSClient_base);
    METHOD_ENTER();

    ASYNC_METHOD_OVER(0, 0);

    if (!cb.IsEmpty())
        hr = pInst->acb_ListBuckets(cb, args);
    else
        hr = pInst->ac_ListBuckets();

    METHOD_VOID();
}
}

#endif
