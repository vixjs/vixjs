/*
 * Cipher.h
 *
 *  Created on: Apr 8, 2014
 *      Author: lion
 */

#pragma once

#include "ifs/Cipher.h"
#include <mbedtls/mbedtls/cipher.h>

namespace fibjs {

class Cipher : public Cipher_base {
public:
    Cipher(const mbedtls_cipher_info_t* ci);
    ~Cipher();

public:
    // Cipher_base
    virtual result_t get_name(exlib::string& retVal);
    virtual result_t get_keySize(int32_t& retVal);
    virtual result_t get_ivSize(int32_t& retVal);
    virtual result_t get_blockSize(int32_t& retVal);
    virtual result_t paddingMode(int32_t mode);
    virtual result_t encrypt(Buffer_base* data, obj_ptr<Buffer_base>& retVal, AsyncEvent* ac);
    virtual result_t decrypt(Buffer_base* data, obj_ptr<Buffer_base>& retVal, AsyncEvent* ac);

public:
    result_t init(exlib::string& key, exlib::string& iv);

private:
    void reset();
    result_t process(const mbedtls_operation_t operation, Buffer_base* data, obj_ptr<Buffer_base>& retVal);

private:
    const mbedtls_cipher_info_t* m_info;
    mbedtls_cipher_context_t m_ctx;
    exlib::string m_key;
    exlib::string m_iv;
};
}
