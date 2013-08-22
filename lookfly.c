#include "data.h"
#include <math.h>

/* Function: mouse_look
	Altering yaw and pitch basing on mouse movement. */
void mouse_look()
{
	float dx = MOUSEX-WIDTH/2, dy = MOUSEY-HEIGHT/2;
	yaw -= dx*0.15;
	pitch -= dy*0.15;
	while (yaw>360) yaw-=360;
	while (yaw<0) yaw+=360;
	if (pitch>90) pitch=89;
	if (pitch<-90) pitch=-89;
	cosyaw = cos(yaw*DTR);
	cospitch = cos(pitch*DTR);
	sinyaw = sin(yaw*DTR);
	sinpitch = sin(pitch*DTR);
	SDL_WarpMouse(WIDTH/2, HEIGHT/2);
}

/* Function: fly_forward
	Changes camera pos depending on it's angles (yaw, pitch) and given speed. */
void fly_forward(float speed)
{
	speed *= 35;
	camx += speed*cos((yaw+90)*DTR) * cos(pitch*DTR);
	camy += speed*sin(pitch*DTR);
	camz += speed*sin((yaw+90)*DTR) * cos(pitch*DTR);
}
