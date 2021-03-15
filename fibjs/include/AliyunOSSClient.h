/**
 * @author richardo2016@gmail.com
 * @email richardo2016
 * @create date 2021-03-15 11:25:25
 * @modify date 2021-03-15 11:25:25
 * @desc [description]
 */

#ifndef ALIYUNOSSCLIENT_H_
#define ALIYUNOSSCLIENT_H_

#include "ifs/AliyunOSSClient.h"
// #include <alibabacloud/oss/OssClient.h>

namespace fibjs {

class AliyunOSSClient : public AliyunOSSClient_base {
public:
    AliyunOSSClient(
        exlib::string region,
        exlib::string accessKeyId,
        exlib::string accessKeySecret)
        : m_region(region)
        , m_accessKeyId(accessKeyId)
        , m_accessKeySecret(accessKeySecret)
    {
        // AlibabaCloud::OSS::InitializeSdk();

        // AlibabaCloud::OSS::ClientConfiguration conf;
        // AlibabaCloud::OSS::OssClient client(m_region, m_accessKeyId, m_accessKeySecret, conf);

        // m_ossClient = &client;
    }

    ~AliyunOSSClient() {
        // AlibabaCloud::OSS::ShutdownSdk();
    };

public:
    // AliyunOSSClient_base
    virtual result_t ListBuckets(AsyncEvent* ac);

public:
    // result_t connect(const char* host, int32_t port, const char* username,
    //     const char* password, const char* dbName);
    // result_t execute(const char* sql, int32_t sLen, obj_ptr<NArray>& retVal);

private:
    // AlibabaCloud::OSS::OssClient* m_ossClient;
    // inline result_t error()
    // {
    //     const char* errorMessage = NULL;
    //     int32_t errCode;
    //     int32_t errType;

    //     if (UMConnection_GetLastError(m_conn, &errorMessage, &errCode,
    //             &errType))
    //         return Runtime::setError(errorMessage);
    //     return Runtime::errNumber();
    // }

public:
    exlib::string m_region;
    exlib::string m_accessKeyId;
    exlib::string m_accessKeySecret;
    // UMConnection m_conn;
};

} /* namespace fibjs */
#endif /* ALIYUNOSSCLIENT_H_ */
