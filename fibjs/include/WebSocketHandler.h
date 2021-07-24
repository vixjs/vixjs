/*
 * WebSocketHandler.h
 *
 *  Created on: Sep 11, 2015
 *      Author: lion
 */

#pragma once

#include "ifs/Handler.h"

namespace fibjs {

class WebSocketHandler : public Handler_base {
    FIBER_FREE();

public:
    WebSocketHandler(v8::Local<v8::Function> accept, bool enableCompress, int32_t maxSize);

public:
    // Handler_base
    virtual result_t invoke(object_base* v, obj_ptr<Handler_base>& retVal,
        AsyncEvent* ac);

public:
    bool m_enableCompress;
    int32_t m_maxSize;
};

} /* namespace fibjs */
