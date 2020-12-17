#ifndef MY_SHA_HPP_
#define MY_SHA_HPP_

#include <openssl/sha.h>

#define HASH_FUNC "SHA256"
#define my_SHA my_SHA256
#define HASH_SIZE SHA256_DIGEST_LENGTH

void my_SHA256(unsigned char *out, const unsigned char *in, int in_len);
void my_SHA512(unsigned char *out, const unsigned char *in, int in_len);

void my_SHA256(unsigned char *out, const unsigned char *in, int in_len){
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, in, in_len);
    SHA256_Final(out, &sha256);
}

void my_SHA512(unsigned char *out, const unsigned char *in, int in_len){
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, in, in_len);
    SHA512_Final(out, &sha512);
}

#endif // MY_SHA_HPP_
