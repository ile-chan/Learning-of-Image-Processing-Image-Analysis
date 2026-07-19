#include"wky_ALG_LinearStretch.h"

void wkyLinearStretch(BYTE* pGryImg, int width, int height, double k, double b, BYTE* pResImg) {
	BYTE* pCur = pGryImg, * pEnd = pGryImg + width * height;
	BYTE LUT[256];
	for (int g = 0; g < 256; g++) {
		LUT[g] = k * g + b;
	}
	for (; pCur < pEnd; pCur++, pResImg++) {
		*pResImg = LUT[*pCur];
	}
	return;
}