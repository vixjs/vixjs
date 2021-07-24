/*
 * WebSocket.h
 *
 *  Created on: Feb 16, 2016
 *      Author: lion
 */

#pragma once

#include "ifs/WebSocket.h"
#include "ifs/ws.h"
#include "ifs/Stream.h"
#include "ZlibStream.h"

namespace fibjs {

#define WS_DEF_SIZE 67108864

class WebSocket : public WebSocket_base {
public:
    WebSocket(exlib::string url, exlib::string protocol, exlib::string origin, bool enableCompress, int32_t maxSize)
        : m_ac(NULL)
        , m_url(url)
        , m_protocol(protocol)
        , m_origin(origin)
        , m_masked(true)
        , m_compress(false)
        , m_enableCompress(enableCompress)
        , m_maxSize(maxSize)
        , m_readyState(ws_base::C_CONNECTING)
        , m_closeState(ws_base::C_OPEN)
        , m_ioState(1)
    {
    }

    WebSocket(Stream_base* stream, exlib::string protocol, AsyncEvent* ac, bool enableCompress, int32_t maxSize)
        : m_stream(stream)
        , m_ac(ac)
        , m_protocol(protocol)
        , m_masked(false)
        , m_compress(false)
        , m_enableCompress(enableCompress)
        , m_maxSize(maxSize)
        , m_readyState(ws_base::C_OPEN)
        , m_closeState(ws_base::C_OPEN)
        , m_ioState(1)
    {
    }

    ~WebSocket();

    EVENT_SUPPORT();

public:
    // object_base
    virtual result_t onEventChange(v8::Local<v8::Function> func, exlib::string ev, exlib::string type)
    {
        startRecv(holder());
        return 0;
    }

    virtual result_t onEventEmit(exlib::string ev)
    {
        if (m_closeState == ws_base::C_CLOSED)
            m_readyState.xchg(ws_base::C_CLOSED);
        return 0;
    }

public:
    // WebSocket_base
    virtual result_t get_url(exlib::string& retVal);
    virtual result_t get_protocol(exlib::string& retVal);
    virtual result_t get_origin(exlib::string& retVal);
    virtual result_t get_readyState(int32_t& retVal);
    virtual result_t close(int32_t code, exlib::string reason);
    virtual result_t send(exlib::string data);
    virtual result_t send(Buffer_base* data);
    virtual result_t ref(obj_ptr<WebSocket_base>& retVal);
    virtual result_t unref(obj_ptr<WebSocket_base>& retVal);

public:
    EVENT_FUNC(open);
    EVENT_FUNC(message);
    EVENT_FUNC(close);
    EVENT_FUNC(error);

public:
    void startRecv(Isolate* isolate);
    void endConnect(int32_t code, exlib::string reason);
    void endConnect(SeekableStream_base* body);
    void enableCompress();

    void free_mem();

public:
    obj_ptr<Stream_base> m_stream;
    AsyncEvent* m_ac;

    obj_ptr<ZlibStream> m_deflate;
    obj_ptr<ZlibStream> m_inflate;
    obj_ptr<Buffer_base> m_flushTail;

    obj_ptr<SeekableStream_base> m_buffer;
    exlib::Locker m_lockEncode;
    exlib::Locker m_lockBuffer;
    exlib::Locker m_lockSend;

    exlib::string m_url;
    exlib::string m_protocol;
    exlib::string m_origin;

    bool m_masked;
    bool m_compress;
    bool m_enableCompress;
    int32_t m_maxSize;

    exlib::atomic m_readyState;
    exlib::atomic m_readState;
    exlib::atomic m_closeState;
    exlib::atomic m_ioState;

    int32_t m_code;
    exlib::string m_reason;

    obj_ptr<ValueHolder> m_holder;
};

} /* namespace fibjs */
