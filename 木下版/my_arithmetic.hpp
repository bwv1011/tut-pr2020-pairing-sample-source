#ifndef MY_ARITHMETIC_HPP_
#define MY_ARITHMETIC_HPP_

#include <libff/algebra/curves/public_params.hpp>
#include "my_util.hpp"

unsigned char * A_xor_B(const unsigned char *A, const unsigned char *B, int len){
    unsigned char *C = (unsigned char *)malloc(len);
    for(int i=0; i<len; i++){
        C[i] = A[i] ^ B[i];
    }
    return C;
}

#endif