#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

#include "bmp.h"

#define BYTES_PER_PIXEL 3
#define BYTES_PER_HEADER 54
#define BYTES_PER_BMP_STRUCTURE sizeof(bmp_structure)

int line_width(int w) {
	int wid = w;
	while (wid % 4 > 0)
		wid++;
	return wid;
}


int load_bmp(const char *name_of_file, unsigned char *header, bmp_structure *bmp) {
    FILE *in = fopen(name_of_file, "rb");
    assert(in);
	fread(header, 1, BYTES_PER_HEADER, in);
	uint32_t w = header[18] | (header[19] << 8) | (header[20] << 16) | (header[21] << 24);
	uint32_t h = header[22] | (header[23] << 8) | (header[24] << 16) | (header[25] << 24);
	bmp->height = h;
	bmp->width = w;
	bmp->square = bmp->width * bmp->height * BYTES_PER_PIXEL;
	bmp->data = (uint8_t **) malloc(sizeof(uint8_t *) * h);
	uint8_t *pix_data = (uint8_t *) malloc(sizeof(uint8_t) * h * w * BYTES_PER_PIXEL);
	for (uint32_t i = 0; i < h; i++) {
		*(bmp->data + i) = pix_data + i * w * BYTES_PER_PIXEL;
	}
	for (uint32_t i = 0; i < h; i++) {
		fread(bmp->data[i], 1, w * BYTES_PER_PIXEL, in);
	}
	fclose(in);
	return 0;
}


int save_bmp(const char *name_of_file, unsigned char* header, bmp_structure *bmp) {
	FILE *out = fopen(name_of_file, "wb");
    assert(out);
	header[18] = bmp->width;
	header[19] = (bmp->width >> 8);
	header[20] = (bmp->width >> 16);
	header[21] = (bmp->width >> 24);
	header[22] = (bmp->height);
	header[23] = (bmp->height >> 8);
	header[24] = (bmp->height >> 16);
	header[25] = (bmp->height >> 24);
	fwrite(header, 1, BYTES_PER_HEADER, out);
	for (uint32_t i = 0; i < bmp->height; i++) {
		fwrite(bmp->data[i], 1, bmp->width * BYTES_PER_PIXEL, out);
	}
	fclose(out);
	return 0;
}


void init_bmp(bmp_structure *buffer, int w, int h) {
	buffer->height = h;
	buffer->width = line_width(w);
	buffer->square = buffer->height * buffer->width * BYTES_PER_PIXEL;
	buffer->header.bfSize = buffer->square + BYTES_PER_HEADER;
	buffer->header.biHeight = h;
	buffer->header.biWidth = w;
	buffer->header.biSizeImage = buffer->square;
    buffer->data = (uint8_t **) malloc(sizeof(uint8_t *) * h);
	uint8_t * pix_data = (uint8_t *) malloc(sizeof(uint8_t) * buffer->square);
	for (int i = 0; i < h; i++) {
		*(buffer->data + i) = pix_data + i * w * BYTES_PER_PIXEL;
	}
}

void free_bmp(bmp_structure *bmp, bmp_structure *buffer) {
	free(bmp->data[0]);
	free(bmp->data);
	memcpy(bmp, buffer, BYTES_PER_BMP_STRUCTURE);
	free(buffer);
}

int crop(bmp_structure *bmp, int x, int y, int w, int h) {
	bmp_structure *buffer = malloc(sizeof(*buffer));
	memcpy(buffer, bmp, BYTES_PER_PIXEL);
	assert(x >= 0 && y >=0 && w >= 0 && h >= 0);
	init_bmp(buffer, w, h);
	int32_t i = 0;
	while (i < h) {
		memcpy(buffer->data[i], bmp->data[y + i] + x * BYTES_PER_PIXEL, BYTES_PER_PIXEL * w);
		i++;
	}
	free_bmp(bmp, buffer);
	return 0; 
}

int rotate(bmp_structure *bmp) {
	int h = bmp->header.biWidth;
	int w = bmp->header.biHeight;
	bmp_structure *buffer = malloc(BYTES_PER_BMP_STRUCTURE);
	memcpy(buffer, bmp, sizeof(bit_map_header));
	init_bmp(buffer, w, h);
	for (int height = 0; height < h; height++) {
		for (int width = 0; width < w; width++) {
			memcpy(buffer->data[h - height - 1] + BYTES_PER_PIXEL * width,
			bmp->data[width] + height * BYTES_PER_PIXEL, BYTES_PER_PIXEL);
		}
	}
	free_bmp(bmp, buffer);
	return 0;
}
