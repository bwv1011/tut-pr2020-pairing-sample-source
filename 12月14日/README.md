## 関数の追加

/libff-1.0.0/testの下に、my_sha512.cpp, my_sha512.hpp, test_sha512.cppを置く。

次のコマンドでtest_sha512.cppをコンパイルして関数が呼べるか確認

> g++ test_sha512.cpp -L../install/lib -lff -lgmp -I../install/include -I/cygdrive/c/openssl/install/include

