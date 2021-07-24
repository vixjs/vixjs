/*
 * SslHandler.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: lion
 */

#include "object.h"
#include "ifs/mq.h"
#include "SslHandler.h"

namespace fibjs {

result_t SslHandler_base::_new(v8::Local<v8::Array> certs, Handler_base* hdlr,
    obj_ptr<SslHandler_base>& retVal, v8::Local<v8::Object> This)
{
    obj_ptr<SslHandler> sslHdlr = new SslHandler();

    sslHdlr->wrap(This);

    result_t hr = sslHdlr->init(certs, hdlr);
    if (hr < 0)
        return hr;

    retVal = sslHdlr;
    return 0;
}

result_t SslHandler_base::_new(X509Cert_base* crt, PKey_base* key,
    Handler_base* hdlr, obj_ptr<SslHandler_base>& retVal,
    v8::Local<v8::Object> This)
{
    obj_ptr<SslHandler> sslHdlr = new SslHandler();

    sslHdlr->wrap(This);

    result_t hr = sslHdlr->init(crt, key, hdlr);
    if (hr < 0)
        return hr;

    retVal = sslHdlr;
    return 0;
}

result_t SslHandler::init(v8::Local<v8::Array> certs, Handler_base* hdlr)
{
    result_t hr;

    set_handler(hdlr);

    hr = SslSocket_base::_new(certs, m_socket);
    if (hr < 0)
        return hr;

    m_socket->set_verification(ssl_base::C_VERIFY_NONE);
    return 0;
}
result_t SslHandler::init(X509Cert_base* crt, PKey_base* key, Handler_base* hdlr)
{
    result_t hr;

    set_handler(hdlr);

    hr = SslSocket_base::_new(crt, key, m_socket);
    if (hr < 0)
        return hr;

    m_socket->set_verification(ssl_base::C_VERIFY_NONE);
    return 0;
}

result_t SslHandler::invoke(object_base* v, obj_ptr<Handler_base>& retVal,
    AsyncEvent* ac)
{
    class asyncInvoke : public AsyncState {
    public:
        asyncInvoke(SslHandler* pThis, Stream_base* stm, AsyncEvent* ac)
            : AsyncState(ac)
            , m_pThis(pThis)
            , m_stm(stm)
        {
            next(accept);
        }

        ON_STATE(asyncInvoke, accept)
        {
            return m_pThis->m_socket->accept(m_stm, m_socket, next(invoke));
        }

        ON_STATE(asyncInvoke, invoke)
        {
            return mq_base::invoke(m_pThis->m_hdlr, m_socket, next(close));
        }

        ON_STATE(asyncInvoke, close)
        {
            return m_socket->close(next(exit));
        }

        ON_STATE(asyncInvoke, exit)
        {
            return next(CALL_RETURN_NULL);
        }

    private:
        obj_ptr<SslHandler> m_pThis;
        obj_ptr<Stream_base> m_stm;
        obj_ptr<SslSocket_base> m_socket;
    };

    if (ac->isSync())
        return CHECK_ERROR(CALL_E_NOSYNC);

    obj_ptr<Stream_base> stm = Stream_base::getInstance(v);
    if (stm == NULL)
        return CHECK_ERROR(CALL_E_BADVARTYPE);

    return (new asyncInvoke(this, stm, ac))->post(0);
}

result_t SslHandler::get_verification(int32_t& retVal)
{
    return m_socket->get_verification(retVal);
}

result_t SslHandler::set_verification(int32_t newVal)
{
    return m_socket->set_verification(newVal);
}

result_t SslHandler::get_ca(obj_ptr<X509Cert_base>& retVal)
{
    return m_socket->get_ca(retVal);
}

result_t SslHandler::get_handler(obj_ptr<Handler_base>& retVal)
{
    retVal = m_hdlr;
    return 0;
}

result_t SslHandler::set_handler(Handler_base* newVal)
{
    SetPrivate("handler", newVal->wrap());
    m_hdlr = newVal;

    return 0;
}
}
