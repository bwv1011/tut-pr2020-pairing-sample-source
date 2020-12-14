#include <cstdint>

template<typename FieldT>
FieldT my_SHA512_rng(const uint64_t idx);

void my_SHA512(unsigned char *out, const unsigned char *in, int _len);


#include "my_sha512.cpp"
