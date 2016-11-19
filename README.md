## How about this ??
  
全世界のプログラミングが好きな桃華Pならば、思うはずである。  
「あ～あ、桃華でプログラミング出来たら、好きな事が一緒に出来て幸せなのになぁ～」  
  
そんな欲望を叶えるのが、「ちゃま言語」である。  
愛があれば、桃華Pは「ちゃま」だけでプログラミングが出来る。  
いつだって桃華への愛で、無限の可能性が開かれるのだ。  
  
## How to programming by Chama-Language ??
  
ちゃま言語はOok!を基に設計されている。  
8つのトークンの組み合わせでポインタ操作を行い、プログラミングを実現できる。  
トークンルールは以下のとおりである。  
  
>ちゃま。　ちゃま？	・ポインタを1つ進める  
>ちゃま？　ちゃま。	・ポインタを1つ戻す  
>ちゃま。　ちゃま。	・ポインタをincrementする  
>ちゃま！　ちゃま！	・ポインタをdecrementする  
>ちゃま。　ちゃま！	・標準入力から値を読み取る  
>ちゃま！　ちゃま。	・現在のメモリポインタを標準出力する  
>ちゃま！　ちゃま？	・現在のメモリ値が0なら対応するちゃま？　ちゃま！までポインタを進める  
>ちゃま？　ちゃま！	・対応するちゃま！　ちゃま？までポインタを戻す  
  
## How to install
  
exeのページでDownloadを押すか  
https://github.com/kaibasira/ChamaLanguage/raw/master/ChamaLanguage.exe  
ここから現状のモノをダウンロードできる。  
  
開発環境はVS2015なので正常に実行できない場合は以下の再頒布パッケージが必要になるかもしれない。  
https://www.microsoft.com/ja-JP/download/details.aspx?id=48145  
  
C++コンパイラを持っている人は、Source.cppをcloneまたはdownloadしてビルドするだけである。  
一応Clang、gccでも動くと思う。  
  
## How to use
  
CUIツールになる。以下のように使用する。  
`ChamaLanguage.exe [filename]`  
  
test.chamaはHello worldを出力するちゃまグラムなので、  
`ChamaLanguage.exe test.chama`  
などしてみるといいかもしれない  
  
## TODO
・力技をunordered_mapで代替する  
・GUI(できればIDE)化する  
・1トークンのちゃま間に半角スペースを許容するか考える  
・改行したらダメかもしれない　対応する  
・もっと良いりーどみーを書く  

