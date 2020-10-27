#pragma once
#include "stdint.h"

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

#pragma pack(push, 1)
typedef struct {
	uint16_t bfType;
	int bfSize;
	int bfReserved;
	int bfOffbits;

	int biSize;
	int biWidth;
	int biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	int biCompression;
	int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	int biClrUsed;
	int biClrImportant;
} bit_map_header;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	bit_map_header header;
	uint8_t **data;
	uint32_t width;
	uint32_t height;
	uint32_t square;
} bmp_structure;
#pragma pack(pop)

int load_bmp(const char *name_of_file, unsigned char* header, bmp_structure *bmp);

int save_bmp(const char *name_of_file, unsigned char* header, bmp_structure *bmp);

int crop(bmp_structure *bmp, int x, int y, int w, int h);

int rotate(bmp_structure *bmp);
