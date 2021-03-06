#ifndef MY_ELEMENT2HEX_HPP_
#define MY_ELEMENT2HEX_HPP_

#include <libff/algebra/curves/public_params.hpp>

#include "my_util.hpp"

using namespace libff;
using namespace std;


// 素体Fqの配列をまとめた16進数の配列を得る
template<typename ppT>
void get_hex_from_FqArray(unsigned char *out, Fq<ppT> in[], int in_len){
    int mp_limb_t_size = sizeof(mp_limb_t);
    int words_num = in[0].mont_repr.N;
    int hex_byte_num = mp_limb_t_size*words_num;

    unsigned char **hexArray = (unsigned char **)malloc( sizeof(void*)*(Fqk<ppT>::extension_degree()) );
    for(int i=0; i<in_len; i++){
        hexArray[i] = out + i*hex_byte_num;
    }

    for(int i=0; i<in_len; i++){
        Fq<ppT> tmp = Montgomery_reduction<ppT>(in[i]);

        if(is_little_endian()){
            for(int j=0; j<words_num; j++)
                *(mp_limb_t*)(hexArray[i]+j*mp_limb_t_size) = tmp.mont_repr.data[j];
            int middle = hex_byte_num/2;
            for(int j=0; j<middle; j++)
                SWAP(hexArray[i][j], hexArray[i][hex_byte_num-1-j]);
        }
        else{
            for(int j=0; j<words_num; j++)
                *(mp_limb_t*)(hexArray[i]+j*mp_limb_t_size) = tmp.mont_repr.data[words_num-1-j];
        }
    }
    free(hexArray);
    return;
}

// 拡大体Fqkを16進数にした値を得る
template<typename ppT>
unsigned char* get_hex_from_Fqk(Fqk<ppT> &g, Fq<ppT>* (*get_FqArray_from_Fqk)(Fqk<ppT>&)){
    Fq<ppT> *FqArray =  get_FqArray_from_Fqk(g); 

    int N = get_Fq_hex_len<ppT>();
    int k = g.extension_degree();
    unsigned char *hex_of_Fqk = (unsigned char *)malloc( N * k );
    get_hex_from_FqArray<ppT>(hex_of_Fqk, FqArray, k);
    delete[] FqArray;

    return hex_of_Fqk;
}


/******************** get_hex_from_Fqk for alt_bn128_pp ********************/
template<typename ppT>
Fq<ppT>* get_FqArray_from_Fq12(Fqk<ppT>& g){
    int k = g.extension_degree();
    Fq<ppT> *FqArray = new Fq<ppT>[k];

    FqArray[0] = g.c0.c0.c0;
    FqArray[1] = g.c0.c0.c1;
    FqArray[2] = g.c0.c1.c0;
    FqArray[3] = g.c0.c1.c1;
    FqArray[4] = g.c0.c2.c0;
    FqArray[5] = g.c0.c2.c1;
    FqArray[6] = g.c1.c0.c0;
    FqArray[7] = g.c1.c0.c1;
    FqArray[8] = g.c1.c1.c0;
    FqArray[9] = g.c1.c1.c1;
    FqArray[10] = g.c1.c2.c0;
    FqArray[11] = g.c1.c2.c1;

    return FqArray;
}

#define get_hex_from_pairing_value(x) get_hex_from_Fqk<ppT>(x, get_FqArray_from_Fq12<ppT>)

#endif