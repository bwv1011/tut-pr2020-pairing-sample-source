#include <libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp>
#include <iostream>

#include "my_sha512.hpp"

using namespace libff;
using namespace std;

template<typename ppT>
void test_sha512(){
    ppT::init_public_params();

    uint64_t idx = 1234;

    Fr<ppT> field_element = my_SHA512_rng<Fr<ppT>>(idx);
    field_element.print();

    return;
}

int main(void)
{
    test_sha512<alt_bn128_pp>();
    return 0;
}
