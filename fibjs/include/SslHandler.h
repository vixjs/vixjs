/*
 * SslHandler.h
 *
 *  Created on: Apr 22, 2014
 *      Author: lion
 */

#pragma once

#include "ifs/SslHandler.h"
#include "SslSocket.h"

namespace fibjs {

class SslHandler : public SslHandler_base {
    FIBER_FREE();

public:
    // Handler_base
    virtual result_t invoke(object_base* v, obj_ptr<Handler_base>& retVal,
        AsyncEvent* ac);

public:
    // SslHandler_base
    virtual result_t get_verification(int32_t& retVal);
    virtual result_t set_verification(int32_t newVal);
    virtual result_t get_ca(obj_ptr<X509Cert_base>& retVal);
    virtual result_t get_handler(obj_ptr<Handler_base>& retVal);
    virtual result_t set_handler(Handler_base* newVal);

public:
    result_t init(v8::Local<v8::Array> certs, Handler_base* hdlr);
    result_t init(X509Cert_base* crt, PKey_base* key, Handler_base* hdlr);

private:
    obj_ptr<Handler_base> m_hdlr;
    obj_ptr<SslSocket_base> m_socket;
};

} /* namespace fibjs */
