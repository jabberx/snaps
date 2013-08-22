#include "data.h"
#include "funcs.h"
#include <math.h>

/* Function: shade
	Applies shading to the point, basing on lights position.
	No specularity will be added. 
	
	Use only in baking purposes. (When loading point cloud).
*/
__inline void shade(Color32 *c, 
					float nx, float ny, float nz,
					float lx, float ly, float lz)
{
	float lum = nx*lx + ny*ly + nz*lz;
	lum = (lum+1)/2.0f;
	c->rgba[0] *= lum;
	c->rgba[1] *= lum;
	c->rgba[2] *= lum;
}

/* Function: shade_spec
	Applies specular shading to the point, basing on lights position.
	
	Parameters:
		sh - packed specular power and hardness: 0..15 and 0...15 = 
			 0.0...3.0 and 0...150
*/
__inline void shade_spec(Color32 *c, 
					float nx, float ny, float nz,
					float lx, float ly, float lz, uint8_t sh)
{
    float len, hi, spec, hard;
	int32_t r,g,b;
	if (!sh) return;
	spec = (sh>>4);
	hard = sh - (sh>>4)<<4;
	spec /= 5.0;
	hard *= 10;
	lx += viewx; ly += viewy; lz += viewz;
	len = 1.0/sqrtf(lx*lx+ly*ly+lz*lz);
    lx *= len; ly *= len; lz *= len;
	hi = (nx*lx + ny*ly + nz*lz)*spec;
	if (hi<0) hi=0; else if(hi>1) hi=1;
	hi = powf(hi, hard);
	hi = (hi+2)/2.0;
	if (hi<0) hi=0; else if(hi>1) hi=1;
	r = c->rgba[0] * hi;
	g = c->rgba[1] * hi;
	b = c->rgba[2] * hi;
	if (r>255 || g>255 || b>255) {
		int32_t m = MAX(r,MAX(g,b));
		float div = m/256.0;
		r *= div; g *= div; b *= div;
	}
	c->rgba[0] = r;
	c->rgba[1] = g;
	c->rgba[2] = b;
}

/* Function: expand
	Restores full 32-bit value from 16-bit lossy packed snapshot coordinate.
	
	Parameters:
		y - shrinking factor, must be the same as used in <shrink>
*/
__inline int32_t expand(int16_t x, float y) 
{
	int8_t sign = 1;
	if (x<0) { sign = -1; x = -x; }
	return (x+x*(x*y))*sign;
}

/* Function: shrink
	Packs 32-bit snapshot coordinate to 16-bit with lossy compression.
	(Close points more precise).
	
	Parameters:
		y - shrinking factor, the same must be used in <expand>
*/
__inline int16_t shrink(int32_t z, float y)
{
	int8_t sign = 1;
	if (z<0) { sign = -1; z = -z; }
	return ((sqrtf(4*y*z+1)-1)/(2*y))*sign;
}

/* Function: clear_zbuffer
	Clears zbuffer. zbuffer is float*, 
	value: the lower - the closer to camera */
void clear_zbuffer()
{
	int x, len = WIDTH*HEIGHT;
	for (x=0;x<len;x++) {
		zbuffer[x] = MAX_DIST;
	}
}

/* Function: clear_img
	clears img. img is uint32_t* array representing screen pixels */
void clear_img(const Uint32 color)
{
	int x, len = WIDTH*HEIGHT;
	for (x=0;x<len;x++) {
		img[x] = color;
	}
}

/* Function: compute_yp
	Caches cos/sins of camera angles. 

	Do once at frame when yaw/pitch changed and <project> will work properly */
void compute_yp() 
{
	cosyaw = cos(yaw*DTR);
	cospitch = cos(pitch*DTR);
	sinyaw = sin(yaw*DTR);
	sinpitch = sin(pitch*DTR);
}

/* Function: compute_viewdir
	Computes viewdir (viewx, viewy, viewz);

	Do once at frame when yaw/pitch changed so <shade_spec> can work properly*/
void compute_viewdir()
{
	viewx = cos((yaw+90)*DTR) * cos(pitch*DTR);
	viewy = sin(pitch*DTR);
	viewz = sin((yaw+90)*DTR) * cos(pitch*DTR);
}

/* Function: project
	Simple project to screen. Use to project ready snapshots or debug points.
	Writes normals and spec_hard values to be used later in pixel shaders.
	
	See Also: 
		<project_render> */
void project(int32_t x, int32_t y, int32_t z, uint32_t col,
			 int8_t nx, int8_t ny, int8_t nz, uint8_t sh) 
{
  float newx,newz0,newy,newz; int sx,sy; 
  static const int marg=0; double nfov;
  const int32_t tx=x-camx, ty=y-camy, tz=z-camz;
  if (!is_back_culled(x,y,z,nx/127.0,ny/127.0,nz/127.0)) return;
  newx = tx * cosyaw   + tz * sinyaw;
  newz0=-tx * sinyaw   + tz * cosyaw;
  newy = ty * cospitch - newz0 * sinpitch;
  newz = ty * sinpitch + newz0 * cospitch;
  if (newz<0.05f || newz>MAX_DIST) return;
  if (newz<0.05f) return; nfov = fov/newz;
  sx = WIDTH/2  + newx * nfov;
  sy = HEIGHT/2 + newy * nfov;
  if(sx<marg ||
      sx>WIDTH-marg-1 ||
      sy<marg ||
      sy>HEIGHT-marg-1) return;
  if(newz<zbuffer[sx+sy*WIDTH]) {
    zbuffer[sx+sy*WIDTH] = newz;
    NXbuf[sx+sy*WIDTH] = nx;
    NYbuf[sx+sy*WIDTH] = ny;
    NZbuf[sx+sy*WIDTH] = nz;
    SHbuf[sx+sy*WIDTH] = sh;
    SDL_DrawPixel(sx,sy,col); }
}

/* Function: project_render
	Project and fill coordinate buffer with shrinked relative to cx/y/z values. 
	Use to render points to snapshot */
void project_render
	(const int32_t x, const int32_t y, const int32_t z, uint32_t  col,
	 int8_t nx, int8_t ny, int8_t nz, uint8_t sh) 
{
  float newx,newz0,newy,newz; int sx,sy; 
  static const int marg=0;
  const int32_t tx=x-camx, ty=y-camy, tz=z-camz;
  if (!is_back_culled(x,y,z,nx/127.0,ny/127.0,nz/127.0)) return;
  newx = tx * cosyaw   + tz * sinyaw;
  newz0=-tx * sinyaw   + tz * cosyaw;
  newy = ty * cospitch - newz0 * sinpitch;
  newz = ty * sinpitch + newz0 * cospitch;
  if (newz<0.05f || newz>MAX_DIST) return;
  if (newz<0.05f) return;
  sx = WIDTH/2  + newx * fov/newz;
  sy = HEIGHT/2 + newy * fov/newz;
  if(sx<marg ||
      sx>WIDTH-marg-1 ||
      sy<marg ||
      sy>HEIGHT-marg-1) return;
  if(newz<zbuffer[sx+sy*WIDTH]) {
    zbuffer[sx+sy*WIDTH] = newz;
    Xbuf[sx+sy*WIDTH] = tx;
    Ybuf[sx+sy*WIDTH] = ty;
    Zbuf[sx+sy*WIDTH] = tz;
    NXbuf[sx+sy*WIDTH] = nx;
    NYbuf[sx+sy*WIDTH] = ny;
    NZbuf[sx+sy*WIDTH] = nz;
    SHbuf[sx+sy*WIDTH] = sh;
    img[sx+sy*WIDTH] = col;    
	}
}

/* Function: add_spec_to_img
	Use to add specularity to image recevied from drawing snapshot[s] 
	
	Should be called before <fill_holes> or any similar function.
*/
void add_spec_to_img()
{
	uint32_t i, len = WIDTH*HEIGHT;
	Color32 c32;
	for (i=0;i<len;i++) {
		if (img[i]!=CLEAR_COLOR) {
			c32.col = img[i];
			shade_spec(&c32, NXbuf[i]/127.0, NYbuf[i]/127.0, NZbuf[i]/127.0,
							 lightx, lighty, lightz, SHbuf[i]);
			img[i] = c32.col;
		}
	}
}

/* Function: is_back_culled
	Use to throw away some points that should be invisible.

	Parameters:
		px,py,pz - global point position
		nx,ny,nz - point's normal

	Returns:
		1 if culled, 0 if not */
__inline uint8_t is_back_culled(int32_t px, int32_t py, int32_t pz,
								float nx, float ny, float nz)
{
	float dx = camx - px;
	float dy = camy - py;
	float dz = camz - pz;
	float len = 1.0f/sqrtf(dx*dx + dy*dy + dz*dz);
	dx *= len;
	dy *= len;
	dz *= len;
	return (dx*nx + dy*ny + dz*nz)<0;
}


/* Function: add_fog_to_img
	Use to add fog to image recevied from drawing snapshot[s]
	
	Should be called before <fill_holes> or any similar function.
*/
void add_fog_to_img()
{
	uint32_t i, len = WIDTH*HEIGHT;
	Color32 c32; float z;
	for (i=0;i<len;i++) {
		if (img[i]!=CLEAR_COLOR) {
			z = zbuffer[i];
			if (z>0.02f) continue;
			z *= z * MAX_DIST * 4;
			z > 1 ? z=1:0;
			z < 0.25f ? z=0.25f:0;
			c32.col = img[i];
			c32.rgba[0] *= z;
			c32.rgba[1] *= z;
			c32.rgba[2] *= z;
			c32.rgba[0] += 0x88 * (1-z);
			c32.rgba[1] += 0xDD * (1-z);
			c32.rgba[2] += 0xEE * (1-z);
			img[i] = c32.col;
		}
	}
}
