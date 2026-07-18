#include"wky_ALG_Histogram.h"
#include<math.h>
//直方图及其计算
void wkyGetHistogram(BYTE* pGryImg, int width, int height, int* histogram) {
	BYTE* pCur = pGryImg, * pEnd = pGryImg + width * height;
	memset(histogram, 0, sizeof(int) * 256);
	for (; pCur < pEnd; pCur++) {
		histogram[*pCur]++;
	}
	return;
}
void wkyMinMaxGry(int* histogram, int* minGry, int* maxGry) {
	int g = 0;
	for (; histogram[g] == 0; g++);
	*minGry = g;
	for (g = 255; histogram[g] == 0; g--);
	*maxGry = g;
	return;
}
void wkyBrightContrast(int* histogram, double* bright, double* contrast) {
	int g = 0, count = 0;
	double sum = 0, fsum = 0;
	for (; g < 256; g++) {
		sum += g * histogram[g];
		count += histogram[g];
	}
	*bright = sum / count;
	for (g = 0; g < 256; g++) {
		fsum = histogram[g] * (histogram[g] - *bright) * (histogram[g] - *bright);
	}
	*contrast = fsum / (count - 1);
	return;
}
//直方图均衡化
void wkyHistogramEqualize(BYTE* pGryImg, int width, int height) {
	int histogram[256], LUT[256];
	int g = 0;
	int A = 0;
	BYTE* pCur = pGryImg, * pEnd = pGryImg + width * height;
	wkyGetHistogram(pGryImg, width, height, histogram);
	for (; g < 256; g++) {
		A += histogram[g];
		LUT[g] = 255 * A / (width * height);
	}
	for (; pCur < pEnd; pCur++) {
		*pCur = LUT[*pCur];
	}
	return;
}
//对数变换
void wkyLogTransform(BYTE* pGryImg, int width, int height) {
	BYTE* pCur, * pEnd = pGryImg + width * height;
	int histogram[256], LUT[256], gmax = 255, g = 0;
	double c;
	wkyGetHistogram(pGryImg, width, height, histogram);
	for (; histogram[gmax] == 0; gmax++);
	c = 255.0 / log(1 + gmax);
	for (; g < 256; g++)
	{
		LUT[g] = (int)(c * log(1 + g));
	}
	for (pCur = pGryImg; pCur < pEnd;) *(pCur++) = LUT[*pCur];
	return;
}
//逐点直方图均衡化
void wkyHistogramEqualizePixel(BYTE* pGryImg, int width, int height, int N, int M, BYTE* pResImg);
//
//14Bit直方图均衡化
void wkyHistogramEqualize(short int* pGry14BitImg, int width, int height, BYTE* pResImg) {
	int histogram[1 << 14], LUT[1 << 14];
	int A = 0, i = 0, g = 0;
	memset(histogram, 0, sizeof(int) * (1 << 14));
	for (i = 0; i < width * height; i++) histogram[*(pGry14BitImg + i)]++;
	for (g = 0; g < (1 << 14); g++){
		A += histogram[g];
		LUT[g] = 255 * A / (width * height);
	}
	for (i = 0; i < width * height; i++){
		pResImg[i] = LUT[*(pGry14BitImg + i)];
	}
	return;
}