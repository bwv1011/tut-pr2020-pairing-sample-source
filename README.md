##ライブラリの準備とテストコードの実行

次のパッケージをCygwinにインストール

	g++, cmake, git, make, libssl-devel, libboost-devel, libgmp-devel, libprocps-devel, chere(任意)



Cygwin上で適当な作業フォルダに移動

https://github.com/scipr-lab/libff/archive/v1.0.0.zip からlibffをダウンロードして解凍



◯ libffのライブラリ(libff.a)の生成

ソースフォルダ直下のCMakeLists.txtを以下のように修正

	12行目 : "BN128" -> "ALT_BN128"
	63行目 : ON -> OFF (※注意: git cloneコマンドでダウンロードしたソースでは元々OFFだが、zipでダウンロードしたソースはONになっている。ちなみに、cmakeにオプションで-DWITH_PROCPS=OFFを付けることと同義)
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

下が実行結果

	(enter) Call to alt_bn128_ate_reduced_pairing   [             ] (1607332539.8598s x0.00 from start)
	  (enter) Call to alt_bn128_ate_pairing         [             ] (1607332539.8622s x0.00 from start)
	    (enter) Call to alt_bn128_ate_precompute_G1 [             ] (1607332539.8626s x0.00 from start)
	    (leave) Call to alt_bn128_ate_precompute_G1 [0.0004s x0.00] (1607332539.8630s x0.00 from start)
	    (enter) Call to alt_bn128_ate_precompute_G2 [             ] (1607332539.8634s x0.00 from start)
	    (leave) Call to alt_bn128_ate_precompute_G2 [0.0007s x0.00] (1607332539.8641s x0.00 from start)
	    (enter) Call to alt_bn128_ate_miller_loop   [             ] (1607332539.8642s x0.00 from start)
	    (leave) Call to alt_bn128_ate_miller_loop   [0.0011s x0.00] (1607332539.8653s x0.00 from start)
	  (leave) Call to alt_bn128_ate_pairing         [0.0033s x0.00] (1607332539.8654s x0.00 from start)
	  (enter) Call to alt_bn128_final_exponentiation        [             ] (1607332539.8658s x0.00 from start)
	    (enter) Call to alt_bn128_final_exponentiation_first_chunk  [             ] (1607332539.8661s x0.00 from start)
	    (leave) Call to alt_bn128_final_exponentiation_first_chunk  [0.0004s x0.00] (1607332539.8665s x0.00 from start)
	    (enter) Call to alt_bn128_final_exponentiation_last_chunk   [             ] (1607332539.8668s x0.00 from start)
	      (enter) Call to alt_bn128_exp_by_neg_z            [             ] (1607332539.8671s x0.00 from start)
	      (leave) Call to alt_bn128_exp_by_neg_z            [0.0007s x0.00] (1607332539.8679s x0.00 from start)
	      (enter) Call to alt_bn128_exp_by_neg_z            [             ] (1607332539.8680s x0.00 from start)
	      (leave) Call to alt_bn128_exp_by_neg_z            [0.0008s x0.00] (1607332539.8688s x0.00 from start)
	      (enter) Call to alt_bn128_exp_by_neg_z            [             ] (1607332539.8689s x0.00 from start)
	      (leave) Call to alt_bn128_exp_by_neg_z            [0.0007s x0.00] (1607332539.8696s x0.00 from start)
	    (leave) Call to alt_bn128_final_exponentiation_last_chunk   [0.0030s x0.00] (1607332539.8698s x0.00 from start)
	  (leave) Call to alt_bn128_final_exponentiation        [0.0052s x0.00] (1607332539.8709s x0.00 from start)
	(leave) Call to alt_bn128_ate_reduced_pairing   [0.0114s x0.00] (1607332539.8712s x0.00 from start)
	(enter) Call to alt_bn128_ate_reduced_pairing   [             ] (1607332539.8716s x0.00 from start)
	  (enter) Call to alt_bn128_ate_pairing         [             ] (1607332539.8719s x0.00 from start)
	    (enter) Call to alt_bn128_ate_precompute_G1 [             ] (1607332539.8722s x0.00 from start)
	    (leave) Call to alt_bn128_ate_precompute_G1 [0.0003s x0.00] (1607332539.8725s x0.00 from start)
	    (enter) Call to alt_bn128_ate_precompute_G2 [             ] (1607332539.8728s x0.00 from start)
	    (leave) Call to alt_bn128_ate_precompute_G2 [0.0007s x0.00] (1607332539.8735s x0.00 from start)
	    (enter) Call to alt_bn128_ate_miller_loop   [             ] (1607332539.8736s x0.00 from start)
	    (leave) Call to alt_bn128_ate_miller_loop   [0.0011s x0.00] (1607332539.8747s x0.00 from start)
	  (leave) Call to alt_bn128_ate_pairing         [0.0029s x0.00] (1607332539.8748s x0.00 from start)
	  (enter) Call to alt_bn128_final_exponentiation        [             ] (1607332539.8751s x0.00 from start)
	    (enter) Call to alt_bn128_final_exponentiation_first_chunk  [             ] (1607332539.8755s x0.00 from start)
	    (leave) Call to alt_bn128_final_exponentiation_first_chunk  [0.0003s x0.00] (1607332539.8758s x0.00 from start)
	    (enter) Call to alt_bn128_final_exponentiation_last_chunk   [             ] (1607332539.8761s x0.00 from start)
	      (enter) Call to alt_bn128_exp_by_neg_z            [             ] (1607332539.8764s x0.00 from start)
	      (leave) Call to alt_bn128_exp_by_neg_z            [0.0007s x0.00] (1607332539.8771s x0.00 from start)
	      (enter) Call to alt_bn128_exp_by_neg_z            [             ] (1607332539.8773s x0.00 from start)
	      (leave) Call to alt_bn128_exp_by_neg_z            [0.0007s x0.00] (1607332539.8779s x0.00 from start)
	      (enter) Call to alt_bn128_exp_by_neg_z            [             ] (1607332539.8783s x0.00 from start)
	      (leave) Call to alt_bn128_exp_by_neg_z            [0.0008s x0.00] (1607332539.8791s x0.00 from start)
	    (leave) Call to alt_bn128_final_exponentiation_last_chunk   [0.0031s x0.00] (1607332539.8792s x0.00 from start)
	  (leave) Call to alt_bn128_final_exponentiation        [0.0044s x0.00] (1607332539.8795s x0.00 from start)
	(leave) Call to alt_bn128_ate_reduced_pairing   [0.0093s x0.00] (1607332539.8809s x0.00 from start)
	Successful

一番下にSuccessfulが出たらOK。それより上のメッセージ(デバッガの出力)は気にしなくて良い。

## ABCDE...
