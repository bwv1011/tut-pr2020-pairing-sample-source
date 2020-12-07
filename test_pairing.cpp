#include <libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp>
#include <iostream>

using namespace libff;
using namespace std;

template<typename ppT>
void test_pairing(){
    ppT::init_public_params();

    // G1 x G2 -> GT

    G1<ppT> P;
    G2<ppT> Q;


    P = (Fr<ppT>::random_element()) * G1<ppT>::one();
    Q = (Fr<ppT>::random_element()) * G2<ppT>::one();

    Fr<ppT> s = Fr<ppT>::random_element();
    
    G1<ppT> sP = s*P;
    G2<ppT> sQ = s*Q;

    GT<ppT> ans1,ans2;
    ans1 = ppT::reduced_pairing(sP,Q);
    ans2 = ppT::reduced_pairing(P,sQ);

    if(ans1 == ans2)
        cout << "Successful" << endl;
    else
        cout << "Failed" << endl;
}

int main(void)
{
    test_pairing<alt_bn128_pp>();
    return 0;
}
