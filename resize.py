#!python3
# -*- coding: utf-8 -*-

from PIL import Image
# 実行時間計測用
import time

import math

def h(t):
    x=math.fabs(t)
    if (x < 1.0):
        return (16.0 + x*x*(21.0 * x - 36.0))/18.0
    elif (x < 2.0):
        return (32.0 + x*(-60.0 + x*(36.0 - 7.0*x)))/18.0
    return 0

def main():
    IMG_FNAME_IN = "pexels-asad-photo-maldives-1591373.jpg"
    IMG_FNAME_OUT = "py_output.jpg"
    divisor = 10

    # 画像ファイルの読み込み
    img = Image.open(IMG_FNAME_IN)
    (width, hight) = img.size
    # 出力画像サイズ
    out_width = width // divisor
    out_hight = hight // divisor
    img = img.convert("RGB")

    # 実行時間の計測開始
    start = time.time()

    # リサイズ
    # Call PIL function
    #out_img = img.resize((out_width, out_hight),resample=Image.BICUBIC)
    # Python native
    
    out_img = Image.new("RGB", (out_width, out_hight), color=0)
    for y in range(out_hight):
        for x in range(out_width):
            out_img.putpixel((x, y), img.getpixel((x * divisor, y * divisor)))
    

    # 実行時間の計測終了
    elapsed_time = time.time() - start
    print ("実行時間 {0}".format(elapsed_time) + "[秒]")

    # 画像の保存
    out_img.save(IMG_FNAME_OUT, 'jpeg', quality=100)

if __name__ == '__main__':
    main()

    """
    out_img = Image.new("RGB", (out_width, out_hight), color=0)
    for y in range(out_hight):
        for x in range(out_width):
            tmp2 = [0, 0, 0]
            for j in range(0, 4):
                tmp = [0, 0, 0]
                for i in range(0, 4):
                    pix_tmp = list(map(lambda x: x*h(i - 1), list(img.getpixel((x * 10 + i, y * 10 + j))))
                    for k in range(3):
                        tmp[k] += pix_tmp[k]
                
                tmp2 += tmp[j] * h(j - 1)
            out_img.putpixel((x, y), tmp2)
    """