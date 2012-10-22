#include "hash.h"

byte* base64_encode(byte *buffer, unsigned int len, int *len_out) {
    BIO *bmem, *b64;
    BUF_MEM *bptr;
    byte* ret;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, buffer, len);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    ret = (byte *) malloc(bptr->length);
    memcpy(ret, bptr->data, bptr->length - 1);
    ret[bptr->length - 1] = 0;

    *len_out = bptr->length;

    BIO_free_all(b64);


    return ret;
}

byte* base64_decode(byte *buffer, unsigned int len, int *len_out) {

    BIO *b64, *bmem;

    byte* ret = (byte *) malloc(len);
    memset(ret, 0, len);

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new_mem_buf(buffer, len);
    bmem = BIO_push(b64, bmem);

    *len_out = BIO_read(bmem, ret, len);

    BIO_free_all(bmem);

    return ret;
}

byte* md5(const byte* input, size_t* len, int hex) {
    byte* output = NULL;
    size_t out_len;
    if (hex) {
        out_len = MD5_DIGEST_LENGTH * 2 + 1;
    } else {
        out_len = MD5_DIGEST_LENGTH;
    }
    output = malloc(out_len);

    if (output) {
        byte digest[MD5_DIGEST_LENGTH];
        (void) MD5(input, *len, digest);
        if (hex) {
            int i;
            for (i = 0; i<sizeof (digest); i++) {
                sprintf((char*) output + i * 2, "%02x", digest[i]);
            }
        } else {
            memcpy(output, digest, sizeof (digest));
        }
        *len = out_len;
    }
    return output;
}

byte* sha1(const byte* input, size_t* len, int hex) {
    byte* output = NULL;
    size_t out_len;
    if (hex) {
        out_len = SHA_DIGEST_LENGTH * 2 + 1;
    } else {
        out_len = SHA_DIGEST_LENGTH;
    }
    output = (byte *) malloc(out_len*sizeof(byte *));

    if (output) {
        byte digest[SHA_DIGEST_LENGTH];
        (void) SHA1(input, *len, digest);
        if (hex) {
            int i;
            for (i = 0; i<sizeof (digest); i++) {
                sprintf((char*) output + i * 2, "%02x", digest[i]);
            }
            output[out_len] = '\0';
        } else {
            memcpy(output, digest, sizeof (digest));
        }
        *len = out_len;
    }
    return output;
}

byte* url_encode(byte* input, int len_data, int *len_out) {
    byte* output = NULL;
    int i, j;

    output = (byte *) malloc(sizeof (byte *) * len_data*3);
    for (i = 0, j = 0; i < len_data; i++) {
        if (input[i] == ' ') {
            output[j++] = '+';
        } else if (strchr("_-.", input[i]) != NULL) {
            output[j++] = input[i];
        } else if (isalnum(input[i])) {
            output[j++] = input[i];
        } else {
            sprintf((char*) &output[j], "%%%.2x", input[i]);
            j += 3;
        }
    }
    output[j] = 0;
    *len_out = j;

    return output;
}

byte* url_decode(byte* input, int len_data, int *len_out) {
    byte *output = NULL;
    int i, j;
    int k;

    output = (byte *) malloc(len_data * sizeof (byte *));
    for (i = 0, j = 0; i < len_data; i++, j++) {
        if (input[i] == '+') {
            output[j] = ' ';
        } else if (strchr("_-.", input[i]) != NULL) {
            output[j] = input[i];
        } else if (isalnum(input[i])) {
            output[j] = input[i];
        } else {
            i++;
            sscanf((char *) &input[i], "%2x", &k);
            output[j] = (byte) k;
            i++;
        }
    }
    output[j] = 0;
    *len_out = j;
    return output;
}
