# 「sh compile.sh A.cpp」 で A.cppのコンパイル
INPUT=$1
g++ -std=gnu++11 ${INPUT} -I../install/include -L../install/lib -lgmp -lcrypto -lff