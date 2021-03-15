/***************************************************************************
 *                                                                         *
 *   This file was automatically generated using idlc.js                   *
 *   PLEASE DO NOT EDIT!!!!                                                *
 *                                                                         *
 ***************************************************************************/

#ifndef _alicloud_base_H_
#define _alicloud_base_H_

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"

namespace fibjs {

class AliyunOSSClient_base;

class alicloud_base : public object_base {
    DECLARE_CLASS(alicloud_base);

public:
    // alicloud_base
    static result_t get_regions(v8::Local<v8::Object>& retVal);

public:
    static void s__new(const v8::FunctionCallbackInfo<v8::Value>& args)
    {
        CONSTRUCT_INIT();

        Isolate* isolate = Isolate::current();

        isolate->m_isolate->ThrowException(
            isolate->NewString("not a constructor"));
    }

public:
    static void s_static_get_regions(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args);
};
}

#include "ifs/AliyunOSSClient.h"

namespace fibjs {
inline ClassInfo& alicloud_base::class_info()
{
    static ClassData::ClassObject s_object[] = {
        { "OSSClient", AliyunOSSClient_base::class_info }
    };

    static ClassData::ClassProperty s_property[] = {
        { "regions", s_static_get_regions, block_set, true }
    };

    static ClassData s_cd = {
        "alicloud", true, s__new, NULL,
        0, NULL, ARRAYSIZE(s_object), s_object, ARRAYSIZE(s_property), s_property, 0, NULL, NULL, NULL,
        &object_base::class_info()
    };

    static ClassInfo s_ci(s_cd);
    return s_ci;
}

inline void alicloud_base::s_static_get_regions(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& args)
{
    v8::Local<v8::Object> vr;

    METHOD_NAME("alicloud.regions");
    PROPERTY_ENTER();

    hr = get_regions(vr);

    METHOD_RETURN();
}
}

#endif
