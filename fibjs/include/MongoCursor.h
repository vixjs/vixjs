/*
 * MongoCursor.h
 *
 *  Created on: Oct 31, 2012
 *      Author: lion
 */

#pragma once

#include "ifs/MongoCursor.h"
#include "MongoDB.h"

namespace fibjs {

class MongoCursor : public MongoCursor_base {
public:
    MongoCursor(MongoDB* db, const exlib::string& ns, const exlib::string& name,
        v8::Local<v8::Object> query, v8::Local<v8::Object> projection);
    ~MongoCursor();

public:
    virtual bool enterTask(exlib::Task_base* current)
    {
        return m_cursor->m_db->enterTask(current);
    }

    virtual void enter()
    {
        m_cursor->m_db->enter();
    }

    virtual void leave(exlib::Task_base* current = NULL)
    {
        m_cursor->m_db->leave(current);
    }

public:
    // object_base
    virtual result_t toJSON(exlib::string key, v8::Local<v8::Value>& retVal);

public:
    // MongoCursor_base
    virtual result_t skip(int32_t num, obj_ptr<MongoCursor_base>& retVal, AsyncEvent* ac);
    virtual result_t limit(int32_t size, obj_ptr<MongoCursor_base>& retVal, AsyncEvent* ac);
    virtual result_t sort(v8::Local<v8::Object> opts, obj_ptr<MongoCursor_base>& retVal);
    virtual result_t hasNext(bool& retVal);
    virtual result_t next(v8::Local<v8::Object>& retVal);
    virtual result_t count(bool applySkipLimit, int32_t& retVal);
    virtual result_t size(int32_t& retVal);
    virtual result_t forEach(v8::Local<v8::Function> func);
    virtual result_t map(v8::Local<v8::Function> func, v8::Local<v8::Array>& retVal);
    virtual result_t toArray(v8::Local<v8::Array>& retVal);
    virtual result_t hint(v8::Local<v8::Object> opts, obj_ptr<MongoCursor_base>& retVal);

private:
    void ensureSpecial();
    result_t _addSpecial(const char* name, v8::Local<v8::Value> opts,
        obj_ptr<MongoCursor_base>& retVal);

    result_t _initCursor(MongoDB* db, AsyncEvent* ac);
    ASYNC_MEMBER1_AC(MongoCursor, _initCursor, MongoDB*);

    result_t _nextCursor(int32_t& retVal, AsyncEvent* ac);
    ASYNC_MEMBERVALUE1_AC(MongoCursor, _nextCursor, int32_t);

public:
    class cursor : public mongo_cursor {
    public:
        obj_ptr<MongoDB> m_db;
    };

private:
    exlib::string m_ns;
    exlib::string m_name;
    cursor* m_cursor;
    bson m_bbq, m_bbp;
    bool m_bInit;
    bool m_bSpecial;
    v8::Global<v8::Object> m_query;
    enum {
        CUR_NONE,
        CUR_DATA,
        CUR_NODATA
    } m_state;
};

} /* namespace fibjs */
