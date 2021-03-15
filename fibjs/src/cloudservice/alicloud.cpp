/**
 * @author richardo2016@gmail.com
 * @email richardo2016
 * @create date 2021-03-15 11:09:42
 * @modify date 2021-03-15 11:09:42
 * @desc alicloud service
 */

#include "object.h"
#include "ifs/alicloud.h"
#include "AliyunOSSClient.h"

namespace fibjs {

DECLARE_MODULE(alicloud);

result_t alicloud_base::get_regions(v8::Local<v8::Object>& retVal)
{
    Isolate* isolate = Isolate::current();

    retVal = v8::Object::New(isolate->m_isolate);

    return 0;
};

result_t AliyunOSSClient_base::_new(v8::Local<v8::Object> config, obj_ptr<AliyunOSSClient_base>& retVal, v8::Local<v8::Object> This)
{
    Isolate* isolate = Isolate::current();

    exlib::string regionId;
    result_t hr;

    hr = GetConfigValue(isolate->m_isolate, config, "region", regionId, true);
    if (hr < 0 && hr != CALL_E_PARAMNOTOPTIONAL)
        return hr;

    exlib::string accessKeyId;
    hr = GetConfigValue(isolate->m_isolate, config, "accessKeyId", accessKeyId, true);
    if (hr < 0 && hr != CALL_E_PARAMNOTOPTIONAL)
        return hr;

    exlib::string accessKeySecret;
    hr = GetConfigValue(isolate->m_isolate, config, "accessKeySecret", accessKeySecret, true);
    if (hr < 0 && hr != CALL_E_PARAMNOTOPTIONAL)
        return hr;

    obj_ptr<AliyunOSSClient> oss = new AliyunOSSClient(regionId, accessKeyId, accessKeySecret);

    retVal = oss;
    return 0;
}
}