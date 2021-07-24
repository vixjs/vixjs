/*
 * AsyncWaitHandler.h
 *
 *  Created on: Dec 2, 2012
 *      Author: lion
 */

#pragma once

#include "ifs/Handler.h"
#include "Event.h"

namespace fibjs {

class AsyncWaitHandler : public Handler_base {

    FIBER_FREE();

public:
    class asyncWaiter : public AsyncEvent {
    public:
        asyncWaiter(AsyncEvent* ac)
            : m_ac(ac)
        {
        }

    public:
        virtual void invoke()
        {
            m_ac->post(CALL_RETURN_NULL);
            delete this;
        }

    private:
        AsyncEvent* m_ac;
    };

public:
    AsyncWaitHandler()
        : m_as(NULL)
        , m_stat(0)
        , m_invoked(0)
    {
    }

public:
    // Handler_base
    virtual result_t invoke(object_base* v, obj_ptr<Handler_base>& retVal,
        AsyncEvent* ac);

public:
    // AsyncWait_base
    virtual result_t end();

private:
    asyncWaiter* m_as;
    exlib::atomic m_stat;
    exlib::atomic m_invoked;
};

} /* namespace fibjs */
