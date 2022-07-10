#pragma once

#include <stdlib.h>
#include <string.h>
#include "base64.h"

char *encrypt_xor(char *input, char *passwd)
{
    if (input == NULL || passwd == NULL) return NULL;

    size_t input_sz = strlen(input);
    size_t passw_sz = strlen(passwd);

    if (input_sz == 0 || passw_sz == 0) return NULL;

    char *result = malloc(input_sz + 1);

    result[input_sz] = 0;
    strcpy(result, input);

    for (int i = 0; i < input_sz; i++) {
        result[i] ^= passwd[i % passw_sz];
    }
    char *b64_res = base64_encode((unsigned char *) result, input_sz);
    free(result);
    return b64_res;
}

char *decrypt_xor(char *input, char *passwd)
{

    if (input == NULL || passwd == NULL) return NULL;
    size_t input_sz = strlen(input);
    size_t passw_sz = strlen(passwd);
    if (input_sz == 0 || passw_sz == 0) return NULL;

    char *result;
    size_t sz = 0;
    if (!base64_decode(input, &result, &sz)) return NULL;
    for (int i = 0; i < sz; i++) {
        result[i] ^= passwd[i % passw_sz];
    }
    return result;
}
