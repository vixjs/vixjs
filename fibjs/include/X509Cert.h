/*
 * X509Cert.h
 *
 *  Created on: Apr 15, 2014
 *      Author: lion
 */

#pragma once

#include "ifs/X509Cert.h"
#include <mbedtls/mbedtls/x509_crt.h>

namespace fibjs {

class X509Cert : public X509Cert_base {
public:
    X509Cert();
    X509Cert(X509Cert* root, int32_t no);
    ~X509Cert();

public:
    // X509Cert_base
    virtual result_t load(Buffer_base* derCert);
    virtual result_t load(exlib::string txtCert);
    virtual result_t loadFile(exlib::string filename);
    virtual result_t loadRootCerts();
    virtual result_t verify(X509Cert_base* cert, bool& retVal, AsyncEvent* ac);
    virtual result_t dump(bool pem, v8::Local<v8::Array>& retVal);
    virtual result_t clear();
    virtual result_t get_version(int32_t& retVal);
    virtual result_t get_serial(exlib::string& retVal);
    virtual result_t get_issuer(exlib::string& retVal);
    virtual result_t get_subject(exlib::string& retVal);
    virtual result_t get_notBefore(date_t& retVal);
    virtual result_t get_notAfter(date_t& retVal);
    virtual result_t get_ca(bool& retVal);
    virtual result_t get_pathlen(int32_t& retVal);
    virtual result_t get_usage(exlib::string& retVal);
    virtual result_t get_type(exlib::string& retVal);
    virtual result_t get_sig_md(int32_t& retVal);
    virtual result_t get_sig_pk(int32_t& retVal);
    virtual result_t get_publicKey(obj_ptr<PKey_base>& retVal);
    virtual result_t get_next(obj_ptr<X509Cert_base>& retVal);

public:
    result_t load(const mbedtls_x509_crt* crt);

public:
    struct _name {
        int32_t id;
        const char* name;
    };

    static _name g_usages[];
    static _name g_types[];

public:
    mbedtls_x509_crt m_crt;

private:
    mbedtls_x509_crt* get_crt();

private:
    struct _cert {
        int32_t size;
        const char* data;
    };

    static _cert g_root_ca[];

private:
    obj_ptr<X509Cert> m_root;
    int32_t m_no;
    bool m_rootLoaded;
};
}
