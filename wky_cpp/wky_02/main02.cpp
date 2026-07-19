#include"../wky_w&r/bmpFile.h"
#include"wky_ALG_Histogram.h"
#include<windows.h>
#include<stdio.h>

void homework0202() {
	int width, height;
	BYTE* pRgbImg = Rmw_Read24BitBmpFile2Img("../wky_cpp/wky_02/H0201Rgb.bmp", &width, &height);
	if (pRgbImg == NULL) {
		printf("H0201Rgb.bmp文件打开失败\n");
		getchar();
		return;
	}
	BYTE* pResImg = new BYTE[width * height];
	static BYTE LUT[256][256][256];
	BYTE* pCur = pRgbImg;
	BYTE* pDst = pResImg;
	for (int r = 0; r < 256; r++) {
		for (int g = 0; g < 256; g++) {
			for (int b = 0; b < 256; b++) {
				LUT[r][g][b] = (BYTE)(r * 0.299 + g * 0.587 + b * 0.114);
			}
		}
	}
	for (int i = 0; i < width * height; i++) {
		BYTE b = *pCur++;
		BYTE g = *pCur++;
		BYTE r = *pCur++;
		*pDst++ = LUT[r][g][b];
	}
	Rmw_Write8BitImg2BmpFile(pResImg, width, height, "../wky_cpp/wky_02/H0201Gry.bmp");
	delete[] pRgbImg;
	delete[] pResImg;
}

void homework0204() {
	int width1, height1, width2, height2;
	BYTE* pGryImg1 = Rmw_Read8BitBmpFile2Img("../wky_cpp/wky_02/H0202Plane.bmp", &width1, &height1);
	if (pGryImg1 == NULL) {
		printf("文件H0202Plane.bmp打开失败\n");
		getchar();
		return;
	}
	BYTE* pGryImg2 = Rmw_Read8BitBmpFile2Img("../wky_cpp/wky_02/H0203Girl.bmp", &width2, &height2);
	if (pGryImg2 == NULL) {
		printf("文件H0203Girl.bmp打开失败\n");
		getchar();
		delete[] pGryImg1;
		return;
	}
	wkyHistogramEqualize(pGryImg1, width1, height1);
	wkyHistogramEqualize(pGryImg2, width2, height2);
	Rmw_Write8BitImg2BmpFile(pGryImg1, width1, height1, "../wky_cpp/wky_02/H0202Plane_eq.bmp");
	Rmw_Write8BitImg2BmpFile(pGryImg2, width2, height2, "../wky_cpp/wky_02/H0203Girl_eq.bmp");
	delete[] pGryImg1;
	delete[] pGryImg2;
}

void homework0207() {
	int width = 640, height = 480;
	short* p14Img = new short[width * height];
	if (RmwRead14BitImgFile(p14Img, width, height, "../wky_cpp/wky_02/H0204IR14bit.raw") != 0) {
		printf("文件打开失败\n");
		getchar();
		delete[] p14Img;
		return;
	}
	BYTE* pGryImg = new BYTE[width * height];
	wkyHistogramEqualize(p14Img, width, height, pGryImg);
	Rmw_Write8BitImg2BmpFile(pGryImg, width, height, "../wky_cpp/wky_02/H0204Ir8bit.bmp");
	delete[] p14Img;
	delete[] pGryImg;
}

//int main() {
//	homework0202();
//	homework0204();
//	homework0207();
//	return 0;
//}