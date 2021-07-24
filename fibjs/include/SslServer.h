/*
 * SslServer.h
 *
 *  Created on: Apr 22, 2014
 *      Author: lion
 */

#pragma once

#include "ifs/SslServer.h"
#include "TcpServer.h"
#include "SslHandler.h"

namespace fibjs {

class SslServer : public SslServer_base {
    FIBER_FREE();

public:
    // TcpServer_base
    virtual result_t start();
    virtual result_t stop(AsyncEvent* ac);
    virtual result_t get_socket(obj_ptr<Socket_base>& retVal);
    virtual result_t get_handler(obj_ptr<Handler_base>& retVal);
    virtual result_t set_handler(Handler_base* newVal);

public:
    // SslServer_base
    virtual result_t get_verification(int32_t& retVal);
    virtual result_t set_verification(int32_t newVal);
    virtual result_t get_ca(obj_ptr<X509Cert_base>& retVal);

public:
    result_t create(X509Cert_base* crt, PKey_base* key, exlib::string addr, int32_t port,
        Handler_base* listener);
    result_t create(v8::Local<v8::Array> certs, exlib::string addr, int32_t port,
        Handler_base* listener);

private:
    obj_ptr<TcpServer_base> m_server;
    obj_ptr<SslHandler_base> m_hdlr;
};

} /* namespace fibjs */
