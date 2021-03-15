/**
 * @author richardo2016@gmail.com
 * @email richardo2016
 * @create date 2021-03-15 11:25:30
 * @modify date 2021-03-15 11:25:30
 * @desc [description]
 */

#include "object.h"
#include "AliyunOSSClient.h"

namespace fibjs {

result_t AliyunOSSClient::ListBuckets(AsyncEvent* ac)
{
    if (ac->isSync())
        return CALL_E_NOSYNC;

    return 0;
};

}