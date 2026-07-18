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

}
void wkyBrightContrast(int* histogram, double* bright, double* contrast);
//直方图均衡化
void wkyHistogramEqualize(BYTE* pGryImg, int width, int height);
//对数变换
void wkyLogTransform(BYTE* pGryImg, int width, int height);
//逐点直方图均衡化
void wkyHistogramEqualizePixel(BYTE* pGryImg, int width, int height, int N, int M, BYTE* pResImg);
//
//14Bit直方图均衡化
int wkyRead14BitImgFile(short int* p14Img, int width, int height, char* fileName);
void wkyHistogramEqualize(short int* pGry14BitImg, int width, int height, BYTE* pResImg);