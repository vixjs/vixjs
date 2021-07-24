/*
 * punycode.cpp
 *
 *  Created on: Aug 22, 2017
 *      Author: lion
 */

#include "ifs/punycode.h"
#include "utf8.h"
#include "qstring.h"
#include "parse.h"
#include <limits.h>

namespace fibjs {

DECLARE_MODULE(punycode);

#define min(a, b) ((a) < (b) ? (a) : (b))

#define BASE 36
#define TMIN 1
#define TMAX 26
#define SKEW 38
#define DAMP 700
#define INITIAL_N 128
#define INITIAL_BIAS 72
#define delimiter '-'

static exlib::wchar32 adapt_bias(exlib::wchar32 delta, uint32_t n_points, bool is_first)
{
    exlib::wchar32 k;

    delta /= is_first ? DAMP : 2;
    delta += delta / n_points;

    /* while delta > 455: delta /= 35 */
    for (k = 0; delta > ((BASE - TMIN) * TMAX) / 2; k += BASE) {
        delta /= (BASE - TMIN);
    }

    return k + (((BASE - TMIN + 1) * delta) / (delta + SKEW));
}

static char encode_digit(int32_t c)
{
    if (c > 25) {
        return c + 22; /* '0'..'9' */
    } else {
        return c + 'a'; /* 'a'..'z' */
    }
}

static int32_t decode_digit(int32_t codePoint)
{
    if (codePoint >= 0x16 && codePoint - 0x30 < 0x0A)
        return codePoint - 0x16;

    if (codePoint >= 0x41 && codePoint - 0x41 < 0x1A)
        return codePoint - 0x41;

    if (codePoint >= 0x61 && codePoint - 0x61 < 0x1A)
        return codePoint - 0x61;

    return BASE;
};

static int32_t encode_var_int(int32_t bias, int32_t delta, char* dst, int32_t dstlen)
{
    int32_t i, k, q, t;

    i = 0;
    k = BASE;
    q = delta;

    while (i < dstlen) {
        if (k <= bias)
            t = TMIN;
        else if (k >= bias + TMAX)
            t = TMAX;
        else
            t = k - bias;

        if (q < t)
            break;

        dst[i++] = encode_digit(t + (q - t) % (BASE - t));

        q = (q - t) / (BASE - t);
        k += BASE;
    }

    if (i < dstlen) {
        dst[i++] = encode_digit(q);
    }

    return i;
}

result_t punycode_base::encode(exlib::string domain, exlib::string& retVal)
{
    exlib::wstring32 wdomain = utf8to32String(domain);
    const exlib::wchar32* src = wdomain.c_str();
    int32_t srclen = (int32_t)wdomain.length();

    exlib::string new_domain;
    int32_t output_length = srclen * 5;
    new_domain.resize(output_length);
    char* dst = new_domain.c_buffer();

    int32_t b, h;
    int32_t delta, bias;
    exlib::wchar32 m, n;
    int32_t si, di;

    for (si = 0, di = 0; si < srclen && di < output_length; si++)
        if (src[si] < 128)
            dst[di++] = src[si];

    b = h = di;

    if (di > 0 && di < output_length)
        dst[di++] = '-';

    n = INITIAL_N;
    bias = INITIAL_BIAS;
    delta = 0;

    for (; h < srclen && di < output_length; n++, delta++) {
        for (m = INT_MAX, si = 0; si < srclen; si++)
            if (src[si] >= n && src[si] < m)
                m = src[si];

        if ((int32_t)(m - n) > (INT_MAX - delta) / (h + 1))
            return CHECK_ERROR(CALL_E_INVALID_DATA);

        delta += (m - n) * (h + 1);
        n = m;

        for (si = 0; si < srclen; si++) {
            if (src[si] < n) {
                if (++delta == 0)
                    return CHECK_ERROR(CALL_E_INVALID_DATA);

            } else if (src[si] == n) {
                di += encode_var_int(bias, delta, &dst[di], output_length - di);
                bias = adapt_bias(delta, h + 1, h == b);
                delta = 0;
                h++;
            }
        }
    }

    new_domain.resize(di);

    retVal = new_domain;
    return 0;
}

result_t punycode_base::decode(exlib::string domain, exlib::string& retVal)
{
    const char* src = domain.c_str();
    int32_t srclen = (int32_t)domain.length();

    exlib::wstring32 new_domain;
    new_domain.resize(srclen);

    exlib::wchar32* dst = new_domain.c_buffer();

    const char* p;
    int32_t b, n, t;
    int32_t i, k, w;
    int32_t si, di;
    int32_t digit;
    int32_t org_i;
    int32_t bias;

    for (si = 0; si < srclen; si++)
        if (src[si] & 0x80)
            return CHECK_ERROR(CALL_E_INVALID_DATA);

    for (p = src + srclen - 1; p > src && *p != '-'; p--)
        ;
    b = (int32_t)(p - src);
    if (b < 0)
        b = 0;

    di = min(b, srclen);

    for (i = 0; i < di; i++)
        dst[i] = src[i];

    i = 0;
    n = INITIAL_N;
    bias = INITIAL_BIAS;

    for (si = (b > 0) ? b + 1 : b; si < srclen && di < srclen; di++) {
        org_i = i;

        for (w = 1, k = BASE; si < srclen && di < srclen; k += BASE) {
            digit = decode_digit(src[si++]);

            if (digit == INT_MAX)
                return CHECK_ERROR(CALL_E_INVALID_DATA);

            if (digit > (INT_MAX - i) / w)
                return CHECK_ERROR(CALL_E_INVALID_DATA);

            i += digit * w;

            if (k <= bias)
                t = TMIN;
            else if (k >= bias + TMAX)
                t = TMAX;
            else
                t = k - bias;

            if (digit < t)
                break;

            if (w > INT_MAX / (BASE - t))
                return CHECK_ERROR(CALL_E_INVALID_DATA);

            w *= BASE - t;
        }

        bias = adapt_bias(i - org_i, di + 1, org_i == 0);

        if (i / (di + 1) > INT_MAX - n)
            return CHECK_ERROR(CALL_E_INVALID_DATA);

        n += i / (di + 1);
        i %= (di + 1);

        memmove(dst + i + 1, dst + i, (di - i) * sizeof(exlib::wchar32));
        dst[i++] = n;
    }

    new_domain.resize(di);
    retVal = utf32to8String(new_domain);

    return 0;
}

result_t punycode_base::toASCII(exlib::string domain, exlib::string& retVal)
{
    result_t hr;
    exlib::string left;
    exlib::string result;
    exlib::string str;
    exlib::wstring32 wdomain;
    exlib::wstring32 wStr;
    size_t length;
    bool notAscii = false;
    bool finished = false;
    _parser p(domain);
    size_t p1 = 0;

    p.skipUntil('@');
    if (p.get() == '@') {
        p.skip();
        result.append(p.string, p.pos);
    } else
        p.pos = 0;

    p.getLeft(left);
    wdomain = utf8to32String(left);
    length = wdomain.length();
    for (size_t i = 0; i < length; i++) {
        if (i + 1 == length || wdomain[i] == '\x2E' || wdomain[i] == 0x3002 || wdomain[i] == 0xff0e || wdomain[i] == 0xff61) {
            if (i + 1 == length) {
                finished = true;
                i++;
            }
            for (size_t j = p1; j < i; j++)
                if (wdomain[j] > '\x7E' || wdomain[j] < '\x20') {
                    notAscii = true;
                    break;
                }
            wStr = wdomain.substr(p1, i - p1);
            str = utf32to8String(wStr);
            if (notAscii) {
                hr = encode(str, str);
                if (hr < 0)
                    return CHECK_ERROR(hr);
                result += "xn--";
            }
            result += str;
            if (!finished)
                result += ".";
            notAscii = false;
            p1 = i + 1;
        }
    }

    retVal = result;

    return 0;
}

result_t punycode_base::toUnicode(exlib::string domain, exlib::string& retVal)
{
    result_t hr;
    exlib::string left;
    exlib::string result;
    exlib::string str;
    size_t length;
    bool finished = false;
    _parser p(domain);
    size_t p1 = 0;

    p.skipUntil('@');
    if (p.get() == '@') {
        p.skip();
        result.append(p.string, p.pos);
    } else
        p.pos = 0;

    p.getLeft(left);
    length = left.length();
    const char* _left = left.c_str();
    for (size_t i = 0; i < length; i++) {
        if (left[i] == '\x2E' || i + 1 == length) {
            if (i + 1 == length) {
                i++;
                finished = true;
            }

            if (qstrcmp(_left + p1, "xn--", 4) == 0) {
                str = left.substr(p1 + 4, i - p1 - 4);
                str.tolower();
                hr = decode(str, str);
                if (hr < 0)
                    return CHECK_ERROR(hr);
            } else
                str = left.substr(p1, i - p1);

            result += str;
            if (!finished)
                result += ".";
            p1 = i + 1;
        }
    }

    retVal = result;

    return 0;
}
}