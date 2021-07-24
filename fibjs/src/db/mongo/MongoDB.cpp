/*
 * MongoDB.cpp
 *
 *  Created on: Oct 25, 2012
 *      Author: lion
 */

#include "object.h"
#include "ifs/db.h"
#include "MongoDB.h"
#include "MongoCollection.h"
#include "Socket_api.h"
#include <mongo/include/env.h>
#include "Url.h"
#include "encoding_bson.h"
#include "MongoID.h"

int32_t mongo_env_set_socket_op_timeout(mongo* conn, int32_t millis)
{
    return MONGO_OK;
}

int32_t mongo_env_read_socket(mongo* conn, void* buf, size_t len)
{
    if (fibjs::socket::c_read(conn->sock, buf, (int32_t)len) < 0) {
        __mongo_set_error(conn, MONGO_IO_ERROR, NULL,
            fibjs::Runtime::errNumber());
        return MONGO_ERROR;
    }

    return MONGO_OK;
}

int32_t mongo_env_write_socket(mongo* conn, const void* buf, size_t len)
{
    if (fibjs::socket::c_send(conn->sock, buf, (int32_t)len) < 0) {
        __mongo_set_error(conn, MONGO_IO_ERROR, NULL,
            fibjs::Runtime::errNumber());
        return MONGO_ERROR;
    }

    return MONGO_OK;
}

int32_t mongo_env_socket_connect(mongo* conn, const char* host, int32_t port)
{
    if (!(conn->sock = fibjs::socket::c_connect(host, port))) {
        __mongo_set_error(conn, MONGO_IO_ERROR, NULL,
            fibjs::Runtime::errNumber());
        return MONGO_ERROR;
    }

    conn->connected = 1;
    return MONGO_OK;
}

int32_t mongo_env_sock_init(void)
{
    return 0;
}

int32_t mongo_env_close_socket(void* socket)
{
    fibjs::socket::destroy(socket);
    return 0;
}

MONGO_EXPORT int32_t mongo_run_command(mongo* conn, const char* db,
    const bson* command, bson* out)
{
    bson response[1];
    bson_iterator it[1];
    size_t sl = fibjs::qstrlen(db);
    char* ns = (char*)bson_malloc(sl + 5 + 1);
    int32_t res = 0;

    strcpy(ns, db);
    strcpy(ns + sl, ".$cmd");

    res = mongo_find_one(conn, ns, command, bson_shared_empty(), response);
    bson_free(ns);

    if (res == MONGO_OK
        && (!bson_find(it, response, "ok") || !bson_iterator_bool(it))) {
        if (bson_find(it, response, "errmsg")) {
            int32_t result_len = bson_iterator_string_len(it);
            const char* result_string = bson_iterator_string(it);
            int32_t len = result_len < MONGO_ERR_LEN ? result_len : MONGO_ERR_LEN;
            memcpy(conn->lasterrstr, result_string, len);
            conn->lasterrcode = -1;
        } else
            conn->err = MONGO_COMMAND_FAILED;

        bson_destroy(response);
        res = MONGO_ERROR;
    }

    if (out)
        if (res == MONGO_OK)
            *out = *response;
        else
            bson_init_zero(out);
    else if (res == MONGO_OK)
        bson_destroy(response);

    return res;
}

namespace fibjs {

result_t MongoDB::error()
{
    static const char* s_msgs[] = {
        "Connection success!", "Could not create a socket.",
        "An error occured while calling connect().",
        "An error occured while calling getaddrinfo().",
        "Warning: connected to a non-master node (read-only).",
        "Given rs name doesn't match this replica set.",
        "Can't find primary in replica set. Connection closed.",
        "An error occurred while reading or writing on the socket.",
        "Other socket error.", "The response is not the expected length.",
        "The command returned with 'ok' value of 0.",
        "Write with given write_concern returned an error.",
        "The name for the ns (database or collection) is invalid.",
        "BSON not valid for the specified op.",
        "BSON object has not been finished.",
        "BSON object exceeds max BSON size.",
        "Supplied write concern object is invalid."
    };

    result_t hr = 0;

    if (m_conn->err == MONGO_IO_ERROR)
        hr = m_conn->errcode;
    else if (m_conn->err > 0 && m_conn->err <= MONGO_WRITE_CONCERN_INVALID)
        hr = Runtime::setError(s_msgs[m_conn->err]);
    else if (m_conn->lasterrcode != 0)
        hr = Runtime::setError(m_conn->lasterrstr);

    mongo_clear_errors(m_conn);
    return hr;
}

result_t db_base::openMongoDB(exlib::string connString,
    obj_ptr<MongoDB_base>& retVal, AsyncEvent* ac)
{
    if (ac->isSync())
        return CHECK_ERROR(CALL_E_NOSYNC);

    const char* c_str = connString.c_str();

    if (qstrcmp(c_str, "mongodb:", 8))
        return CHECK_ERROR(CALL_E_INVALIDARG);

    obj_ptr<MongoDB> db = new MongoDB();
    result_t hr = db->open(c_str);
    if (hr < 0)
        return hr;

    retVal = db;

    return 0;
}

result_t MongoDB::open(exlib::string connString)
{
    assert(!Runtime::check());

    obj_ptr<Url> u = new Url();
    int32_t result;
    int32_t nPort;

    result_t hr = u->parse(connString);
    if (hr < 0)
        return hr;

    if (qstrchr(u->m_host.c_str(), ',')) {
        const char* host = u->m_host.c_str();

        mongo_replset_init(m_conn, "");

        while (true) {
            exlib::string hostname;
            exlib::string port;

            Url::parseHost(host, hostname, port);

            nPort = 27017;
            if (!port.empty())
                nPort = atoi(port.c_str());

            mongo_replset_add_seed(m_conn, hostname.c_str(), nPort);

            if (*host != ',')
                break;

            host++;
        }

        result = mongo_replset_connect(m_conn);
    } else {
        nPort = 27017;
        if (!u->m_port.empty())
            nPort = atoi(u->m_port.c_str());

        mongo_init(m_conn);
        result = mongo_client(m_conn, u->m_hostname.c_str(), nPort);
    }

    if (result != MONGO_OK)
        return CHECK_ERROR(error());

    if (!u->m_pathname.empty())
        m_ns = u->m_pathname.substr(1);

    if (!u->m_username.empty())
        if (mongo_cmd_authenticate(m_conn, m_ns.c_str(), u->m_username.c_str(),
                u->m_password.c_str())
            != MONGO_OK)
            return CHECK_ERROR(error());

    return 0;
}

result_t MongoDB::getCollection(exlib::string name,
    obj_ptr<MongoCollection_base>& retVal)
{
    if (m_closed)
        return CALL_E_INVALID_CALL;

    exlib::string nsStr;
    const char* ns = name.c_str();

    if (!m_ns.empty()) {
        nsStr = m_ns;
        nsStr += '.';
        nsStr.append(name);
        ns = nsStr.c_str();
    }

    retVal = new MongoCollection(this, ns, name);

    return 0;
}

result_t MongoDB::_runCommand(bson* command, bson& out, AsyncEvent* ac)
{
    if (m_closed)
        return CALL_E_INVALID_CALL;

    if (ac->isSync())
        return CHECK_ERROR(CALL_E_NOSYNC);

    if (mongo_run_command(m_conn, m_ns.c_str(), command, &out) != MONGO_OK) {
        bson_destroy(&out);
        bson_destroy(command);
        return CHECK_ERROR(error());
    }
    return 0;
}

result_t MongoDB::bsonHandler(bson* command, v8::Local<v8::Object>& retVal)
{
    if (m_closed)
        return CALL_E_INVALID_CALL;

    bson out;

    result_t hr = ac__runCommand(command, out);
    if (hr < 0)
        return hr;

    hr = decodeObject(holder(), &out, retVal);
    if (hr < 0)
        return hr;

    bson_destroy(&out);
    bson_destroy(command);

    return 0;
}

result_t MongoDB::runCommand(v8::Local<v8::Object> cmd,
    v8::Local<v8::Object>& retVal)
{
    if (m_closed)
        return CALL_E_INVALID_CALL;

    bson bbq;
    result_t hr;

    hr = encodeObject(holder(), &bbq, cmd);
    if (hr < 0)
        return hr;

    return bsonHandler(&bbq, retVal);
}

result_t MongoDB::runCommand(exlib::string cmd, v8::Local<v8::Value> arg,
    v8::Local<v8::Object>& retVal)
{
    if (m_closed)
        return CALL_E_INVALID_CALL;

    bson bbq;

    bson_init(&bbq);
    encodeValue(holder(), &bbq, cmd.c_str(), arg);
    bson_finish(&bbq);

    return bsonHandler(&bbq, retVal);
}

result_t MongoDB::_named_getter(exlib::string property,
    obj_ptr<MongoCollection_base>& retVal)
{
    if (m_closed)
        return CALL_RETURN_NULL;

    return getCollection(property, retVal);
}

result_t MongoDB::_named_enumerator(v8::Local<v8::Array>& retVal)
{
    return 0;
}

result_t MongoDB::oid(exlib::string hexStr, obj_ptr<MongoID_base>& retVal)
{
    if (m_closed)
        return CALL_E_INVALID_CALL;

    retVal = new MongoID(hexStr);
    return 0;
}

result_t MongoDB::close(AsyncEvent* ac)
{
    if (m_closed)
        return CALL_E_INVALID_CALL;

    m_closed = true;
    return 0;
}

} /* namespace fibjs */
