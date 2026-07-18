#include"wky_ALG_Histogram.h"
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
	wkyGetHistogram(pGryImg, width, height, histogram);
	for (; g < 256; g++) {
		
	}

}
//对数变换
void wkyLogTransform(BYTE* pGryImg, int width, int height);
//逐点直方图均衡化
void wkyHistogramEqualizePixel(BYTE* pGryImg, int width, int height, int N, int M, BYTE* pResImg);
//
//14Bit直方图均衡化
int wkyRead14BitImgFile(short int* p14Img, int width, int height, char* fileName);
void wkyHistogramEqualize(short int* pGry14BitImg, int width, int height, BYTE* pResImg);