#include <gmp.h>
#include <openssl/sha.h>

#include <libff/algebra/fields/bigint.hpp>
#include <libff/common/rng.hpp>
#include <libff/common/utils.hpp>

template<typename FieldT>
FieldT my_SHA512_rng(const uint64_t idx)
{
    (void)idx;
    const long a = 10;
    FieldT A(a);
    return A;  
}

void my_SHA512(unsigned char *out, const unsigned char *in, int in_len){
    
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, &in, in_len);
    SHA512_Final(out, &sha512);
}

