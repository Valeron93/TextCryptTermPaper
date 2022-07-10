#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static const char base64_encode_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int base64_decode_table[] = { 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
                                           59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
                                           6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                                           21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
                                           29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
                                           43, 44, 45, 46, 47, 48, 49, 50, 51 };

static inline size_t base64_size_encode(size_t len)
{
    size_t result;
    result = len;
    if (len % 3 != 0) {
        result += 3 - (len % 3);
    }
    result /= 3;
    result *= 4;
    return result;
}

static inline size_t base64_size_decode(char * string)
{
    if (string == NULL)
        return 0;

    size_t len = strlen(string);
    size_t result = len / 4 * 3;

    for (size_t idx=len; idx-- > 0;) {
        if (string[idx] == '=') {
            result--;
        } else {
            break;
        }
    }
    return result;
}

static inline bool base64_validate_char(char c)
{
    if (c >= '0' && c <= '9') return true;
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= 'a' && c <= 'z') return true;
    if (c == '+' || c == '/' || c == '=') return true;
    return true;
}

char *base64_encode(const unsigned char *string, size_t len)
{
    if (string == NULL || len == 0)
        return NULL;

    size_t out_size = base64_size_encode(len);
    char *result = malloc(out_size + 1);
    result[out_size] = '\0';

    size_t r;

    for (size_t i=0,j=0; i<len; i+=3, j+=4) {
        r = string[i];
        r = i + 1 < len ? r << 8 | string[i + 1] : r << 8;
        r = i + 2 < len ? r << 8 | string[i + 2] : r << 8;

        result[j]   = base64_encode_table[(r >> 18) & 0x3F];
        result[j + 1] = base64_encode_table[(r >> 12) & 0x3F];
        if (i+1 < len) {
            result[j + 2] = base64_encode_table[(r >> 6) & 0x3F];
        } else {
            result[j + 2] = '=';
        }
        if (i+2 < len) {
            result[j + 3] = base64_encode_table[r & 0x3F];
        } else {
            result[j + 3] = '=';
        }
    }
    return result;
}

bool base64_decode(const unsigned char *string, char **out, size_t *out_size)
{
    if (string == NULL || out == NULL)
        return false;

    size_t len = strlen(string);
    if (len % 4 != 0)
        return false;

    for (size_t i=0; i<len; i++) {
        if (!base64_validate_char(string[i])) {
            return false;
        }
    }
    size_t out_len = base64_size_decode(string);
    *out_size = out_len;
    char *result = malloc(out_len + 1);
    result[out_len] = 0;

    for (size_t i=0, j=0; i<len; i+=4, j+=3) {
        int r = base64_decode_table[string[i] - 43];
        r = (r << 6) | base64_decode_table[string[i + 1] - 43];
        r = string[i + 2] == '=' ? r << 6 : (r << 6) | base64_decode_table[string[i + 2] - 43];
        r = string[i + 3] == '=' ? r << 6 : (r << 6) | base64_decode_table[string[i + 3] - 43];

        result[j] = (r >> 16) & 0xFF;
        if (string[i + 2] != '=')
            result[j + 1] = (r >> 8) & 0xFF;
        if (string[i + 3] != '=')
            result[j + 2] = r & 0xFF;
    }
    *out = result;
    return true;
}
