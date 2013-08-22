#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include "data.h"
#include "funcs.h"

/* just fills the gaps between pixels. doesn't touches zbuffer */
void fill_holes()
{
	uint32_t x, y;
	static uint32_t *img2 = NULL;
	if (img2 == NULL) {
		img2 = (uint32_t*) malloc (WIDTH*HEIGHT*sizeof(uint32_t));
	}
	memcpy(img2, img, WIDTH*HEIGHT*sizeof(Uint32));
	for (x=0;x<WIDTH-1;x++) {
		for (y=0;y<HEIGHT;y++) {
			const uint32_t addr = x + y*WIDTH;
			if (img2[addr] == CLEAR_COLOR) {
				img2[addr] = img[addr+1]; 
			}
		}
	}
	for (x=1;x<WIDTH;x++) {
		for (y=0;y<HEIGHT;y++) {
			const uint32_t addr = x + y*WIDTH;
			if (img2[addr] == CLEAR_COLOR) {
				img2[addr] = img[addr-1]; 
			}
		}
	}
	memcpy(img, img2, WIDTH*HEIGHT*sizeof(uint32_t));
	
	for (x=0;x<WIDTH;x++) {
		for (y=0;y<HEIGHT-1;y++) {
			const uint32_t addr = x + y*WIDTH;
			if (img2[addr] == CLEAR_COLOR) {
				img2[addr] = img[addr+WIDTH]; 
			}
		}
	}
	for (x=0;x<WIDTH;x++) {
		for (y=1;y<HEIGHT;y++) {
			const uint32_t addr = x + y*WIDTH;
			if (img2[addr] == CLEAR_COLOR) {
				img2[addr] = img[addr-WIDTH]; 
			}
		}
	}
	memcpy(img, img2, WIDTH*HEIGHT*sizeof(uint32_t));
}
