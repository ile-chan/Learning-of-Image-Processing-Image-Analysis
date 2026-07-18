# ifndef WKYBMPFILE_H
# define WKYBMPFILE_H

# include<windows.h>

BYTE* Wky_Read8BitBMPFile2Img(const char* fileName, int* width, int* height) {
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	int w, h;
	BYTE *pCur,
}

# endif