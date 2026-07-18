# include"wky_ALG_Inverting.h"
#include <nmmintrin.h>

void wkyInvertGryImg(BYTE* pGryImg, int width, int height) {
	BYTE* pCur = pGryImg, * pEnd = pGryImg + width * height;
	for (; pCur < pEnd; pCur++) {
		*pCur = 255 - *pCur;
	}
	return;
}

void wkyInvertRgbImg(BYTE* pRgbImg, int width, int height) {
	BYTE* pCur = pRgbImg, *pEnd = pRgbImg + width * height * 3;
	for (; pCur < pEnd; pCur++) {
		*pCur = 255 - *pCur;
	}
	return;
}

void wkyInvertSSE(BYTE* pImg, int width, int height, bool isRgb) {
	__m128i C, * pSSE;
	BYTE *pCur = pImg;
	int k = (unsigned int)pImg % 16;
	BYTE *pStart = k ? (pImg + 16 - k) : pImg;
	int imsSize = isRgb ? width * height * 3 : width * height;
	BYTE* pEnd = pStart + (pImg + imsSize - pStart) / 16 * 16;
	for (; pCur < pStart; pCur++) {
		*pCur = 255 - *pCur;
	}
	for (pSSE = (__m128i*)pStart, C = _mm_set1_epi8(255); pCur < pEnd; pCur += 16, pSSE++) {
		*pSSE = _mm_sub_epi8(C, *pSSE);
	}
	for (; pCur < pImg + imsSize; pCur++) {
		*pCur = 255 - *pCur;
	}
	return;
}