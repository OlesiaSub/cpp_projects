#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "bmp.h"

#define BYTES_PER_HEADER 54

int main(int argc, char **argv){
	assert(argc == 8);
	if (strcmp(argv[1], "crop-rotate") == 0) {
		bmp_structure *bmp = malloc(sizeof(bmp_structure));
		unsigned char *header = (unsigned char*)malloc(BYTES_PER_HEADER);
		load_bmp(argv[2], header, bmp);
		int x = atoi(argv[4]);
		int y = atoi(argv[5]);
		int w = atoi(argv[6]);
		int h = atoi(argv[7]); 
		assert(x >= 0 && y >= 0 && h >= 0 && w >= 0);
		crop(bmp, x, y, w, h);
		rotate(bmp);
		save_bmp(argv[3], header, bmp);
		free(bmp->data[0]);
	        free(bmp->data);
		free(bmp);
		free(header);
	} else {
		printf("%s", "EXIT_FAILURE");
		return 1;
	}
	return 0;
}
