#include <SDL/SDL.h>
#include <stdint.h>
#include "defs.h"

Cloud cloud;
Snapshot snap;

float *zbuffer;
int32_t *Xbuf, *Ybuf, *Zbuf;
int8_t *NXbuf, *NYbuf, *NZbuf;
uint8_t *SHbuf;
float yaw, pitch, cosyaw, sinyaw, cospitch, sinpitch;
float camx=0, camy=0, camz=0;
float viewx=0, viewy=0, viewz=0;
float lightx=-0.28, lighty=-0.942, lightz=-0.18;
const float fov = 128;
const double DTR = 0.01745329238; const double RTD = 57.29578;
const double PI = 3.1415926535897932384626433832795;

const int WIDTH = 256, HEIGHT = 256;

const float shrink_val = 0.001;

SDL_Event event;
int32_t MOUSEX, MOUSEY;
int32_t KEY[128];
int32_t BUTTON[5];
int32_t exit_flag = 0;

SDL_Surface *screen;
uint32_t *img;