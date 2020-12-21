#ifndef MY_UTIL_HPP_
#define MY_UTIL_HPP_

#include <libff/algebra/curves/public_params.hpp>

using namespace libff;
using namespace std;

#define SWAP(x, y) do{ typeof(y) t = x; x = y; y = t; }while (0)

// 16進数の配列を表示
void print_hex_array(unsigned char *buf, int buf_len, int line_wrap_len, const char *print_prefix=NULL){
    printf("%s", print_prefix);
    for(int i=0; i<buf_len; i++){
        if(i%line_wrap_len == 0)
            printf("\n\t");
        printf("%02x ",buf[i]);
    }
    printf("\n\n");
}

// 16進数の配列が同じであるか比較
bool hexcmp(unsigned char *buf1, unsigned char *buf2, int buf_len){
    int i;
    for(i=0; i<buf_len; i++)
        if(buf1[i] != buf2[i])
            break;

    if(i == buf_len)
        return true;
    else
        return false;
}

//  高速化のためにモンゴメリ表現に変換
template<typename ppT>
Fq<ppT> Montgomery_reduction(Fq<ppT> &t){
    Fq<ppT> tmp;
    tmp.mont_repr.data[0] = 1;
    tmp.mul_reduce(t.mont_repr);
    return tmp;
}

// 素体Fqを16進数にした時のサイズを得る
template<typename ppT>
int get_Fq_hex_len(){
    Fq<ppT> g;
    const int mp_limb_t_size = sizeof(mp_limb_t);
    const int words_num = g.mont_repr.N;
    return mp_limb_t_size * words_num;
}

// 拡大体Fqkを16進数にした時のサイズを得る
template<typename ppT>
int get_Fqk_hex_len(){
    return get_Fq_hex_len<ppT>() * Fqk<ppT>::extension_degree();
}

#endif // MY_UTIL_HPP_