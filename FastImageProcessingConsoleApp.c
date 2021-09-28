#include <stdio.h>
// 実行時間計測用
#include <time.h>

// 画像入出力・リサイズ
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

// 入出力ファイル名
#define IMG_FNAME_IN "pexels-asad-photo-maldives-1591373.jpg"
#define IMG_FNAME_OUT "output.jpg"

// 実行時間計測用 for WIN32
// BEGIN
// From https://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows
#ifdef WIN32
#include <windows.h>
#define CLOCK_REALTIME 0

LARGE_INTEGER
getFILETIMEoffset()
{
	SYSTEMTIME s;
	FILETIME f;
	LARGE_INTEGER t;

	s.wYear = 1970;
	s.wMonth = 1;
	s.wDay = 1;
	s.wHour = 0;
	s.wMinute = 0;
	s.wSecond = 0;
	s.wMilliseconds = 0;
	SystemTimeToFileTime(&s, &f);
	t.QuadPart = f.dwHighDateTime;
	t.QuadPart <<= 32;
	t.QuadPart |= f.dwLowDateTime;
	return (t);
}

int
clock_gettime(int X, struct timeval* tv)
{
	LARGE_INTEGER           t;
	FILETIME            f;
	double                  microseconds;
	static LARGE_INTEGER    offset;
	static double           frequencyToMicroseconds;
	static int              initialized = 0;
	static BOOL             usePerformanceCounter = 0;

	if (!initialized) {
		LARGE_INTEGER performanceFrequency;
		initialized = 1;
		usePerformanceCounter = QueryPerformanceFrequency(&performanceFrequency);
		if (usePerformanceCounter) {
			QueryPerformanceCounter(&offset);
			frequencyToMicroseconds = (double)performanceFrequency.QuadPart / 1000000.;
		}
		else {
			offset = getFILETIMEoffset();
			frequencyToMicroseconds = 10.;
		}
	}
	if (usePerformanceCounter) QueryPerformanceCounter(&t);
	else {
		GetSystemTimeAsFileTime(&f);
		t.QuadPart = f.dwHighDateTime;
		t.QuadPart <<= 32;
		t.QuadPart |= f.dwLowDateTime;
	}

	t.QuadPart -= offset.QuadPart;
	microseconds = (double)t.QuadPart / frequencyToMicroseconds;
	t.QuadPart = microseconds;
	tv->tv_sec = t.QuadPart / 1000000;
	tv->tv_usec = t.QuadPart % 1000000;
	return (0);
}
#endif
// END

// 実行時間計測用
#define USECTOSEC 1000000L;
struct timeval start_time;
struct timeval stop_time;

double calculateExecutionTime()
{

	clock_gettime(CLOCK_REALTIME, &stop_time);

	double dSeconds = (stop_time.tv_sec - start_time.tv_sec);

	double dMicroSeconds = (double)(stop_time.tv_usec - start_time.tv_usec) / USECTOSEC;

	return dSeconds + dMicroSeconds;
}

int main()
{
	unsigned char* pixels = NULL; // 画素の格納先
	unsigned char* out_pixels = NULL; // 画素の格納先
	int width, hight;
	int out_width, out_hight;
	int bpp; // 1画素のバイト数
	int x, y, k;
	int divisor = 10;


	// ----------------------------------------
	// 画像ファイルの読み込み
	pixels = stbi_load(IMG_FNAME_IN, &width, &hight, &bpp, 0);
	// 出力画像サイズ
	out_width = width / divisor;
	out_hight = hight / divisor;
	out_pixels = (unsigned char*)stbi__malloc(out_width * out_hight * bpp);


	// 開始時刻の記録
	clock_gettime(CLOCK_REALTIME, &start_time);
	
	// リサイズ
	/*
	stbir_resize_uint8(pixels, width, hight, 0,
					out_pixels, out_width, out_hight, 0,
					3);
	*/
	// C native resize implementation (nearest neighborhood)
	
	for (y = 0; y < out_hight; y++) {
		int ybpp = y * bpp;
		for (x = 0; x < out_width; x++) {
			int xbpp = bpp * x;
			for (k = 0; k < bpp; k++) {
				out_pixels[ybpp * out_width + xbpp + k] = pixels[(ybpp * divisor) * width  + (xbpp * divisor) + k];
			}
		}
	}
	

	// 終了時刻の取得と実行時間の算出
	printf("実行時間 %f 秒\n", calculateExecutionTime());

	stbi_write_jpg(IMG_FNAME_OUT, out_width, out_hight, bpp, out_pixels, 100);

	// メモリ上の画像データを破棄
	stbi_image_free(pixels);
	// ----------------------------------------


	

	return 0;
}