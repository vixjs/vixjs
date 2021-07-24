/*
 * RedisSortedSet.h
 *
 *  Created on: Aug 6, 2014
 *      Author: lion
 */

#pragma once

#include "Redis.h"

namespace fibjs {

class RedisSortedSet : public RedisSortedSet_base {
public:
    RedisSortedSet(Buffer_base* key, Redis* rdb)
        : m_rdb(rdb)
    {
        key->toString(m_key);
    }

public:
    virtual bool enterTask(exlib::Task_base* current)
    {
        return m_rdb->enterTask(current);
    }

    virtual void enter()
    {
        m_rdb->enter();
    }

    virtual void leave(exlib::Task_base* current = NULL)
    {
        m_rdb->leave(current);
    }

public:
    // RedisSortedSet_base
    virtual result_t add(v8::Local<v8::Object> sms, int32_t& retVal);
    virtual result_t add(OptArgs sms, int32_t& retVal);
    virtual result_t score(Buffer_base* member, obj_ptr<Buffer_base>& retVal);
    virtual result_t incr(Buffer_base* member, int64_t num, obj_ptr<Buffer_base>& retVal);
    virtual result_t remove(v8::Local<v8::Array> members, int32_t& retVal);
    virtual result_t remove(OptArgs members, int32_t& retVal);
    virtual result_t len(int32_t& retVal);
    virtual result_t count(int32_t min, int32_t max, int32_t& retVal);
    virtual result_t range(int32_t start, int32_t stop, bool withScores, obj_ptr<NArray>& retVal);
    virtual result_t rangeRev(int32_t start, int32_t stop, bool withScores, obj_ptr<NArray>& retVal);
    virtual result_t rank(Buffer_base* member, int32_t& retVal);
    virtual result_t rankRev(Buffer_base* member, int32_t& retVal);

private:
    exlib::string m_key;
    obj_ptr<Redis> m_rdb;
};
}
