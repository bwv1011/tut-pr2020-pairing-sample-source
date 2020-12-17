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

/************* for sha's test *************/
#include "my_sha.hpp"

void test_sha(){
    unsigned char hash_input_0[HASH_SIZE] = "";
    unsigned char hash_value_0[HASH_SIZE] = {};
    int hash_input_len = 0;
    my_SHA(hash_value_0, hash_input_0, hash_input_len);
    printf(HASH_FUNC"(\"\"):");
    print_hex_array(hash_value_0, HASH_SIZE, 16, "");

    unsigned char hash_input_1[HASH_SIZE] = "ABC";
    unsigned char hash_input_2[HASH_SIZE] = "ABD";
    hash_input_len = 3;
    
    unsigned char hash_value_1[HASH_SIZE] = {};
    unsigned char hash_value_2[HASH_SIZE] = {};

    print_hex_array(hash_input_1, HASH_SIZE, 16, "input_1:");
    print_hex_array(hash_input_2, HASH_SIZE, 16, "input_2:");

    my_SHA(hash_value_1, hash_input_1, hash_input_len);
    my_SHA(hash_value_2, hash_input_2, hash_input_len);

    print_hex_array(hash_value_1, HASH_SIZE, 16, HASH_FUNC"(input_1):");
    print_hex_array(hash_value_2, HASH_SIZE, 16, HASH_FUNC"(input_2):");
    return;
}

/************* for element2hex's test *************/
#include "my_element2hex.hpp"

template<typename ppT>
void test_element2hex(){
    G1<ppT> P = G1<ppT>::one();
    G2<ppT> Q = G2<ppT>::one();
    GT<ppT> g = ppT::reduced_pairing(P,Q);

    unsigned char *hex_of_Fqk = get_hex_from_Fqk<ppT>(g, get_FqArray_from_Fq12<ppT>);

    int mp_limb_t_size = sizeof(mp_limb_t);
    int words_num = g.c0.c0.c0.mont_repr.N;
    int N = mp_limb_t_size*words_num;
    int k = GT<ppT>::extension_degree();
    print_hex_array(hex_of_Fqk, N*k, N, "Fq12's hex:");

    free(hex_of_Fqk);
    
    return;
}

int main(void)
{
    libff::inhibit_profiling_info = true;
    libff::inhibit_profiling_counters = true;
    alt_bn128_pp::init_public_params();

    test_pairing<alt_bn128_pp>();
    test_sha();
    test_element2hex<alt_bn128_pp>();
    
    return 0;
}
