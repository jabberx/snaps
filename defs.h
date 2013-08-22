#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>

//#define FULLSCREEN
#define CLEAR_COLOR 0xCEA0A0A0
#define MAX_DIST 100000
#define ABS(X) ((X)<0)?-(X):(X)
#define MAX(A,B) (((A)>(B))?((A)):((B)))
#define DEPTH 32
#define SDL_AsmRGB(R,G,B) SDL_MapRGB(screen->format, (R), (G), (B) )

typedef struct {
uint32_t s;
int32_t *x,*y,*z; uint16_t *c; 
int8_t *nx,*ny,*nz; uint8_t *sh;
} Cloud;

typedef struct {
uint32_t s; int32_t cx, cy, cz;
int16_t *x,*y,*z; uint16_t *c;
int8_t *nx,*ny,*nz; uint8_t *sh;
} Snapshot;

typedef union {
uint32_t col;
uint8_t rgba[4];
} Color32;

#endif