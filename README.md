# 周知

Cygwin上での実装で致命的なエラーが発生するので、今からでも仮想マシンを使ったUbuntu上での実装に移行した方が良いです。「ubuntu16.04_on_VirtualBox」を参考にして下さい。

VirtualBoxをインストールして配布している仮想マシンをダウンロードしてインポートするだけで、すぐに実装を開始できます。libffを改めてダウンロード、インストールする必要はないです。
詳細は後日まとめます。

また、「統括版」にこれまでの統括と一部修正、Jouxのプロトコルの実装例をまとめてます。
詳細は後日まとめます。

# 実装するプロトコル

Boneh-Boyen署名：https://crypto.stanford.edu/~dabo/pubs/papers/bbsigs.pdf

境-笠原IDベース暗号：https://eprint.iacr.org/2005/226.pdf    (光成滋生著「クラウドを支えるこれからの暗号技術」の15.5章)

McCullagh-Barreto IDベース認証鍵交換：https://eprint.iacr.org/2004/122.pdf
