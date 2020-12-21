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

template<typename FieldT>
FieldT my_SHA_rng(const unsigned char *idx, int idx_len);

template<typename FieldT>
FieldT my_SHA_rng(const unsigned char *idx, int idx_len)
{
    assert(GMP_NUMB_BITS == 64); // current Python code cannot handle larger values, so testing here for some assumptions.
    assert(is_little_endian());

    assert(FieldT::size_in_bits() <= SHA512_DIGEST_LENGTH * 8);

    bigint<FieldT::num_limbs> rval;
    uint64_t iter = 0;
    do
    {
        mp_limb_t hash[((SHA512_DIGEST_LENGTH*8) + GMP_NUMB_BITS - 1)/GMP_NUMB_BITS];

        SHA512_CTX sha512;
        SHA512_Init(&sha512);
        SHA512_Update(&sha512, idx, idx_len);
        SHA512_Update(&sha512, &iter, sizeof(iter));
        SHA512_Final((unsigned char*)hash, &sha512);

        for (mp_size_t i = 0; i < FieldT::num_limbs; ++i)
        {
            rval.data[i] = hash[i];
        }

        /* clear all bits higher than MSB of modulus */
        size_t bitno = GMP_NUMB_BITS * FieldT::num_limbs - 1;

        /* mod is non-zero so the loop will always terminate */
        while (FieldT::mod.test_bit(bitno) == false)
        {
            const std::size_t part = bitno/GMP_NUMB_BITS;
            const std::size_t bit = bitno - (GMP_NUMB_BITS*part);

            rval.data[part] &= ~(1ul<<bit);

            bitno--;
        }

        ++iter;
    }

    /* if r.data is still >= modulus -- repeat (rejection sampling) */
    while (mpn_cmp(rval.data, FieldT::mod.data, FieldT::num_limbs) >= 0);

    return FieldT(rval);
}

#endif // MY_SHA_HPP_
