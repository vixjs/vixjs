/*
 * DBField.h
 *
 *  Created on: Jul 28, 2012
 *      Author: lion
 */

#pragma once

#include "utils.h"

namespace fibjs {

class DBField : public obj_base {
public:
    DBField(int32_t sz)
    {
        m_fields.resize(sz);
    }

public:
    void setField(int32_t i, exlib::string& s)
    {
        m_fields[i] = s;
    }

    uint32_t index(exlib::string name)
    {
        uint32_t i;

        for (i = 0; i < (uint32_t)m_fields.size(); i++)
            if (!qstricmp(name.c_str(), m_fields[i].c_str()))
                return i;

        return -1;
    }

    exlib::string& name(int32_t i)
    {
        return m_fields[i];
    }

    void names(v8::Isolate* isolate, v8::Local<v8::Array>& retVal)
    {
        int32_t i;

        retVal = v8::Array::New(isolate);
        for (i = 0; i < (int32_t)m_fields.size(); i++)
            retVal->Set(i, GetReturnValue(isolate, m_fields[i]));
    }

private:
    std::vector<exlib::string> m_fields;
};
}
