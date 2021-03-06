#include <libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp>
#include <libff/common/profiling.hpp>
#include <iostream>
#include <cassert>
#include <chrono>

#include "my_util.hpp"
#include "my_sha.hpp"
#include "my_element2hex.hpp"

using namespace libff;
using namespace std;

// e(R,S)^x を計算
template<typename ppT>
GT<ppT> Fw(Fr<ppT> x, G1<ppT> R, G2<ppT> S){
    return ppT::reduced_pairing(R,S)^x;
}

template<typename ppT>
void Joux_protocol(){

    G1<ppT> P = G1<ppT>::one();
    G2<ppT> Q = G2<ppT>::one();

    /********* 3人のユーザー A, B, C は、ぞれぞれ自分の秘密鍵と公開鍵を生成 *********/
    Fr<ppT> a = Fr<ppT>::random_element(); // A's secret key
    G1<ppT> PA = a * P;                    // A's public key 1
    G2<ppT> QA = a * Q;                    // A's public key 2

    Fr<ppT> b = Fr<ppT>::random_element(); // B's secret key
    G1<ppT> PB = b * P;                    // B's public key 1 
    G2<ppT> QB = b * Q;                    // B's public key 2

    Fr<ppT> c = Fr<ppT>::random_element(); // C's secret key
    G1<ppT> PC = c * P;                    // C's public key 1 
    G2<ppT> QC = c * Q;                    // C's public key 2
    /********* A,B,Cはお互いの公開鍵を交換する *********/



    /********* 交換で受け取った相手の公開鍵と自分の秘密鍵から共通の値を計算 *********/
    GT<ppT> A_SharedValue =  Fw<ppT>(a,PB,QC);
    GT<ppT> B_SharedValue =  Fw<ppT>(b,PA,QC);
    GT<ppT> C_SharedValue =  Fw<ppT>(c,PA,QB);

    unsigned char *A_SharedValue_hex = get_hex_from_pairing_value(A_SharedValue);
    unsigned char *B_SharedValue_hex = get_hex_from_pairing_value(B_SharedValue);
    unsigned char *C_SharedValue_hex = get_hex_from_pairing_value(C_SharedValue);
    int K_len = get_Fqk_hex_len<ppT>();

    /******* ペアリング値をハッシュに入力して共有秘密鍵を得る *******/
    unsigned char *A_SharedSecret = my_SHA(A_SharedValue_hex, K_len);
    unsigned char *B_SharedSecret = my_SHA(B_SharedValue_hex, K_len);
    unsigned char *C_SharedSecret = my_SHA(C_SharedValue_hex, K_len);

    /******* 共有秘密鍵が一致しているか確認　*******/
    assert(hexcmp(A_SharedSecret, B_SharedSecret, HASH_SIZE));
    assert(hexcmp(B_SharedSecret, C_SharedSecret, HASH_SIZE));

    print_hex_array(A_SharedSecret, HASH_SIZE, HASH_SIZE/2, "A_SharedSecret");
    print_hex_array(B_SharedSecret, HASH_SIZE, HASH_SIZE/2, "B_SharedSecret:");
    print_hex_array(C_SharedSecret, HASH_SIZE, HASH_SIZE/2, "C_SharedSecret:");

    free(A_SharedValue_hex);
    free(B_SharedValue_hex);
    free(C_SharedValue_hex);
    free(A_SharedSecret);
    free(B_SharedSecret);
    free(C_SharedSecret);
    
    return;
}

int main(void){
    libff::inhibit_profiling_info = true;
    libff::inhibit_profiling_counters = true;
    alt_bn128_pp::init_public_params();
                       
    auto start = std::chrono::high_resolution_clock::now();
        Joux_protocol<alt_bn128_pp>();
    auto end = std::chrono::high_resolution_clock::now();

    double Time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

    printf("Time = %lf [ms]\n", Time);
}