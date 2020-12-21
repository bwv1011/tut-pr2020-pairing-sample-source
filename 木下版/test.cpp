#include <libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp>
#include <libff/common/profiling.hpp>
#include <iostream>
#include <cassert>

#include "my_util.hpp"

using namespace libff;
using namespace std;

/************* for pairing's test *************/
template<typename ppT>
void test_pairing(){
    // G1 x G2 -> GT

    G1<ppT> P;
    G2<ppT> Q;

    P = (Fr<ppT>::random_element()) * G1<ppT>::one();
    Q = (Fr<ppT>::random_element()) * G2<ppT>::one();

    Fr<ppT> s = Fr<ppT>::random_element();
    
    G1<ppT> sP = s*P;
    G2<ppT> sQ = s*Q;

    GT<ppT> ans1,ans2,ans3;
    ans1 = ppT::reduced_pairing(sP,Q);
    ans2 = ppT::reduced_pairing(P,sQ);
    ans3 = ppT::reduced_pairing(P,Q)^s;

    assert(ans1 == ans2);
    assert(ans1 == ans3);

    printf("Pairing's successful\n\n");
}

/************* for hash's test *************/
#include "my_hash.hpp"

template<typename ppT>
void test_hash(){

    /******* Sha's test *******/

    unsigned char hash_input_0[HASH_SIZE] = "";
    int hash_input_len = 0;

    unsigned char *hash_value_0 = my_SHA(hash_input_0, hash_input_len);
    print_hex_array(hash_value_0, HASH_SIZE, 16, HASH_FUNC"(\"\"):");

    unsigned char hash_input_1[HASH_SIZE] = "ABC";
    unsigned char hash_input_2[HASH_SIZE] = "ABD";
    hash_input_len = 3;
    
    unsigned char *hash_value_1 = my_SHA(hash_input_1, hash_input_len);
    unsigned char *hash_value_2 = my_SHA(hash_input_2, hash_input_len);

    print_hex_array(hash_input_1, HASH_SIZE, 16, "input_1:");
    print_hex_array(hash_input_2, HASH_SIZE, 16, "input_2:");

    print_hex_array(hash_value_1, HASH_SIZE, 16, HASH_FUNC"(input_1):");
    print_hex_array(hash_value_2, HASH_SIZE, 16, HASH_FUNC"(input_2):");

    free(hash_value_0);
    free(hash_value_1);
    free(hash_value_2);


    /******* Hash(ID) to element *******/
    unsigned char hash_input_A[HASH_SIZE] = "ID_A";
    unsigned char hash_input_B[HASH_SIZE] = "ID_B";
    hash_input_len = 4;
    Fq<ppT> a = get_element_from_id<ppT>(hash_input_A, hash_input_len);
    Fq<ppT> b = get_element_from_id<ppT>(hash_input_B, hash_input_len);
    
    printf(HASH_FUNC"(\"%s\") to Fq element = ", hash_input_A);
    a.print();
    printf(HASH_FUNC"(\"%s\") to Fq element = ", hash_input_B);
    b.print();
    printf("\n");

    return;
}

/************* for element2hex's test *************/
#include "my_element2hex.hpp"

template<typename ppT>
void test_element2hex(){
    G1<ppT> P = G1<ppT>::one();
    G2<ppT> Q = G2<ppT>::one();
    GT<ppT> g = ppT::reduced_pairing(P,Q);

    unsigned char *hex_of_Fqk = get_hex_from_pairing_value(g);

    int N = get_Fq_hex_len<ppT>();
    int k = GT<ppT>::extension_degree();
    print_hex_array(hex_of_Fqk, N*k, N, "Fq12's hex:");

    free(hex_of_Fqk);
    
    return;
}

/************* for my_arithmetic's test *************/
#include "my_arithmetic.hpp"

void test_arithmetic(){
    unsigned char A[64] = {1, 2, 3};
    unsigned char B[64] = {2, 3, 1};

    unsigned char *C = A_xor_B(A, B, 3);

    print_hex_array(C, 3, 4, "C:");

    free(C);
    return;
}

int main(void)
{
    libff::inhibit_profiling_info = true;
    libff::inhibit_profiling_counters = true;
    
    alt_bn128_pp::init_public_params();
    test_element2hex<alt_bn128_pp>();
    test_hash<alt_bn128_pp>();
    test_pairing<alt_bn128_pp>();

    test_arithmetic();

    
    return 0;
}
