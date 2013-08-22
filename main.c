#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <SDL/SDL.h>
#include "defs.h"
#include "data.h"
#include "funcs.h"

/* naturaldocs -i . -o HTML doc -p doc */

/*
	Function: loop
	Main program loop.
*/
void loop() { while(!exit_flag) 
{
	static int32_t delta=16, last_ticks=-1, ticks;
	static int32_t fps_upd_cnt = 0;
	static int32_t taken = 0;
	if (last_ticks == -1) last_ticks = SDL_GetTicks();
	SDL_HandleEvents();
	mouse_look();
	if (KEY[key_w]) fly_forward(delta*0.05);
	if (KEY[key_s]) fly_forward(delta*-0.05);
	if (KEY[ESCAPE]) exit_flag=1;
	clear_zbuffer();
	clear_img(CLEAR_COLOR);
	
	/* begin drawing here */
	//draw_snapshot(&snap, 1);

	if (KEY[CAPSLOCK]) fill_holes();
	/* end drawing here */
	
	SDL_FlipScreen();
	ticks = SDL_GetTicks();
	delta = ticks - last_ticks;
	last_ticks = ticks;
	if (delta<16){ SDL_Delay(16-delta); delta = 16; }
	fps_upd_cnt++;
	if (fps_upd_cnt>10) {
		fps_upd_cnt = 0;
		char buffer[256];
		sprintf(buffer,"fps: %d yaw: %.0f pit: %.0f", 1000/delta, yaw, pitch);
		SDL_WM_SetCaption(buffer, NULL);
	}
}}

int main(int argc, char **argv)
{
	//load_snapshot("snapshot.snp", &snap);
	
	SDL_Initialize();
	SDL_WM_SetCaption("test", NULL);
	zbuffer = (float*) malloc(WIDTH*HEIGHT*sizeof(float));
	Xbuf = (int32_t*) malloc(WIDTH*HEIGHT*4);
	Ybuf = (int32_t*) malloc(WIDTH*HEIGHT*4);
	Zbuf = (int32_t*) malloc(WIDTH*HEIGHT*4);
	NXbuf = (int8_t*) malloc(WIDTH*HEIGHT);
	NYbuf = (int8_t*) malloc(WIDTH*HEIGHT);
	NZbuf = (int8_t*) malloc(WIDTH*HEIGHT);
	SHbuf = (uint8_t*) malloc(WIDTH*HEIGHT);

	//load or generate cloud here. (use Cloud cloud (global from data.c)
	//set camera position camx = 1000; camy = 300; camz = 1000
	//take_snapshot(&snap, "snapshotname.snp");

	SDL_ShowCursor(0);
	SDL_WarpMouse(WIDTH/2, HEIGHT/2);
	loop();
	return 0;
}
