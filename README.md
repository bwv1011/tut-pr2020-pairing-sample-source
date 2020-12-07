次のパッケージをCygwinにインストール
g++, cmake, git, make
libssl-devel, libboost-devel, libgmp-devel, libprocps-devel



Cygwin上で適当な作業フォルダに移動

https://github.com/scipr-lab/libff/archive/v1.0.0.zip からlibffをダウンロードして解凍



◯ libffのライブラリ(libff.a)の生成

ソースフォルダ直下のCMakeLists.txtを以下のように修正

	12行目 : "BN128" -> "ALT_BN128"
	
	230行目 : add_subdirectory(depends) -> # add_subdirectory(depends)
	

ソースフォルダ直下で、次のコマンドを実行

mkdir build && cd build && cmake .. -DCMAKE_INSTALL_PREFIX=../install

make

make install

cd ../

◯ libff.aを用いたサンプルソースの実行

ソースフォルダ直下で、次のコマンドを実行

mkdir test && cd test

curl -O https://raw.githubusercontent.com/bwv1011/tut-pr2020-pairing-sample-source/main/test_pairing.cpp

g++ test_pairing.cpp -L../install/lib -lff -lgmp -I../install/include

./a.exe

Successfulが出たらOK.
