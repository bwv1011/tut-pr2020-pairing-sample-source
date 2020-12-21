#ifndef MY_HASH_HPP_
#define MY_HASH_HPP_

#include <openssl/sha.h>

#include <libff/algebra/curves/public_params.hpp>

#include "my_util.hpp"

using namespace libff;
using namespace std;

#define HASH_FUNC "SHA256"
#define my_SHA my_SHA256
#define HASH_SIZE SHA256_DIGEST_LENGTH

unsigned char *my_SHA256(const unsigned char *in, int in_len);
unsigned char *my_SHA512(const unsigned char *in, int in_len);

unsigned char *my_SHA256(const unsigned char *in, int in_len){
    unsigned char *out = (unsigned char *)malloc(HASH_SIZE);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, in, in_len);
    SHA256_Final(out, &sha256);
    return out;
}

unsigned char *my_SHA512(const unsigned char *in, int in_len){
    unsigned char *out = (unsigned char *)malloc(HASH_SIZE);
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, in, in_len);
    SHA512_Final(out, &sha512);
    return out;
}

template<typename ppT>
Fq<ppT> get_element_from_id(const unsigned char *in, int in_len);

template<typename ppT>
Fq<ppT> get_element_from_id(const unsigned char *in, int in_len)
{
    assert(GMP_NUMB_BITS == 64); // current Python code cannot handle larger values, so testing here for some assumptions.
    assert(is_little_endian());

    assert(Fq<ppT>::size_in_bits() <= SHA512_DIGEST_LENGTH * 8);

    bigint<Fq<ppT>::num_limbs> rval;
    uint64_t iter = 0;
    do
    {
        mp_limb_t hash[((SHA512_DIGEST_LENGTH*8) + GMP_NUMB_BITS - 1)/GMP_NUMB_BITS];

        SHA512_CTX sha512;
        SHA512_Init(&sha512);
        SHA512_Update(&sha512, in, in_len);
        SHA512_Update(&sha512, &iter, sizeof(iter));
        SHA512_Final((unsigned char*)hash, &sha512);

        for (mp_size_t i = 0; i < Fq<ppT>::num_limbs; ++i)
        {
            rval.data[i] = hash[i];
        }

        /* clear all bits higher than MSB of modulus */
        size_t bitno = GMP_NUMB_BITS * Fq<ppT>::num_limbs - 1;

        /* mod is non-zero so the loop will always terminate */
        while (Fq<ppT>::mod.test_bit(bitno) == false)
        {
            const std::size_t part = bitno/GMP_NUMB_BITS;
            const std::size_t bit = bitno - (GMP_NUMB_BITS*part);

            rval.data[part] &= ~(1ul<<bit);

            bitno--;
        }

        ++iter;
    }

    /* if r.data is still >= modulus -- repeat (rejection sampling) */
    while (mpn_cmp(rval.data, Fq<ppT>::mod.data, Fq<ppT>::num_limbs) >= 0);

    return Fq<ppT>(rval);
}

#endif // MY_SHA_HPP_