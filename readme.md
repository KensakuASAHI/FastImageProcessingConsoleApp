FastImageProcessingConsoleApp
==========

## 概要

巨大な画像を最近傍のリサンプリングにより縮小する速度をCとPythonで比較する．

以下の入力画像を1/10に縮小する速度を計測する．

### 入力画像

`pexels-asad-photo-maldives-1591373.jpg`
7360 x 4912 px


### 出力画像：

* `output.jpg` C による出力
* `py_output.jpg` Python による出力


## 必要なもの

### C code

Visual Studio 2010 or later.


### Python code

Python 3.x and PIL


## 使い方

### C code

`FastImageProcessingConsoleApp.sln` を開いてビルドして実行する．


### Python code

`resize.py` を実行する．


## 実行時間例

### 測定結果

* C : 0.00145 [s]
* Python :  0.656 [s]

### 測定環境

* Intel Core i7-9700 @ 3.00GHz
* 16GB
* Windows 10 21H1 (BUild 19043.1237)


## License

MIT License
Copyright (c) 2021 Kensaku ASAHI



