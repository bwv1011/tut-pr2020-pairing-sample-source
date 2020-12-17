#ifndef MY_UTIL_HPP_
#define MY_UTIL_HPP_


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

#endif // MY_UTIL_HPP_