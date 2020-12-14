#include <libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp>
#include <iostream>

#include "my_sha512.hpp"

using namespace libff;
using namespace std;

#define HASH_SIZE SHA512_DIGEST_LENGTH

void print_hex_array(unsigned char *buf, int buf_len, const char *print_prefix=NULL){
    printf(print_prefix);
    for(int i=0; i<buf_len; i++){
        if(i%16 == 0)
            printf("\n\t");
        printf("%02x ",buf[i]);
    }
    printf("\n\n");
}

template<typename ppT>
void test_sha512(){
    ppT::init_public_params();

    unsigned char hash_input_1[HASH_SIZE] = "ABC";
    unsigned char hash_input_2[HASH_SIZE] = "ABD";
    int hash_input_len = 3;
    
    unsigned char hash_value_1[HASH_SIZE] = {};
    unsigned char hash_value_2[HASH_SIZE] = {};

    print_hex_array(hash_input_1, HASH_SIZE, "input_1: \n");
    print_hex_array(hash_input_2, HASH_SIZE, "input_2: \n");


    my_SHA512(hash_value_1, hash_input_1, hash_input_len);
    my_SHA512(hash_value_2, hash_input_2, hash_input_len);

    print_hex_array(hash_value_1, HASH_SIZE, "out_1: \n");
    print_hex_array(hash_value_2, HASH_SIZE, "out_2: \n");
    return;
}

int main(void)
{
    test_sha512<alt_bn128_pp>();
    return 0;
}
