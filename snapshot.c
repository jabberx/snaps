#include "data.h"
#include "funcs.h"

/* Function: render_scene
	Scene should be assembled here. TODO: rework

	Parameters:
		counter - pointer to snapshot's point counter
*/
void render_scene(float y, float p, Snapshot *snap, uint32_t *counter) 
{
	uint32_t i;
	uint32_t cnt = *counter;
	clear_zbuffer(); 
	clear_img(CLEAR_COLOR); 
	yaw = y; 
	pitch = p;
	compute_yp(); 
	
	/* render here */
	render_cloud(&cloud,0,0,0,1); 
	
	/* end */
		
	for (i=0; i<WIDTH*HEIGHT; i++) { 
		if (img[i] != CLEAR_COLOR) {
		snap->x[cnt] = shrink(Xbuf[i], shrink_val); 
		snap->y[cnt] = shrink(Ybuf[i], shrink_val); 
		snap->z[cnt] = shrink(Zbuf[i], shrink_val); 
		snap->nx[cnt] = NXbuf[i];
		snap->ny[cnt] = NYbuf[i]; 
		snap->nz[cnt] = NZbuf[i];
		snap->sh[cnt] = SHbuf[i];
		snap->c[cnt] = true2high(img[i]); 
		cnt++; }
	}
	*counter = cnt;
}

/* Function: take_snapshot
	Renders given snapshot and writes it to the file. TODO: rework */
void take_snapshot(Snapshot *snap, const char *filename)
{
	Uint32 i, len = cloud.s;
	Uint32 cnt = 0; FILE *f; Uint32 header[4];
	if (snap->x == NULL) snap->x = (int16_t*) malloc(WIDTH*HEIGHT*12);
	if (snap->y == NULL) snap->y = (int16_t*) malloc(WIDTH*HEIGHT*12);
	if (snap->z == NULL) snap->z = (int16_t*) malloc(WIDTH*HEIGHT*12);
	if (snap->c == NULL) snap->c = (uint16_t*) malloc(WIDTH*HEIGHT*12);
	if (snap->nx == NULL) snap->nx = (int8_t*) malloc(WIDTH*HEIGHT*6);
	if (snap->ny == NULL) snap->ny = (int8_t*) malloc(WIDTH*HEIGHT*6);
	if (snap->nz == NULL) snap->nz = (int8_t*) malloc(WIDTH*HEIGHT*6);
	if (snap->sh == NULL) snap->sh = (uint8_t*) malloc(WIDTH*HEIGHT*6);

	render_scene(0,-90,snap,&cnt);
	render_scene(0,90,snap,&cnt);
	render_scene(0,0,snap,&cnt);
	render_scene(90,0,snap,&cnt);
	render_scene(180,0,snap,&cnt);
	render_scene(270,0,snap,&cnt);
	
	snap->s = cnt; snap->cx = camx;
	snap->cy = camy; snap->cz = camz;

	f = fopen(filename, "wb");
	header[0] = cnt;
	header[1] = camx;
	header[2] = camy;
	header[3] = camz;
	fwrite(header, 1, 16, f);
	fwrite(snap->x, 2, cnt, f);
	fwrite(snap->y, 2, cnt, f);
	fwrite(snap->z, 2, cnt, f);
	fwrite(snap->c, 2, cnt, f);
	fwrite(snap->nx, 1, cnt, f);
	fwrite(snap->ny, 1, cnt, f);
	fwrite(snap->nz, 1, cnt, f);
	fwrite(snap->sh, 1, cnt, f);
	fclose(f);
}

/* Function: load_snapshot
	Loads a file to the snapshot. */
void load_snapshot(const char *filename, Snapshot *snap)
{
	FILE *f;
	uint32_t header[4]; uint32_t cnt=0;
	f = fopen(filename, "rb");
	if (f == NULL) { printf("file not found: %s", filename); return; }
	/*  maximum memory should be allocated only once for a snapshot
		to allow later refill with new data
	 */
	if (snap->x == NULL) snap->x = (int16_t*) malloc(WIDTH*HEIGHT*12);
	if (snap->y == NULL) snap->y = (int16_t*) malloc(WIDTH*HEIGHT*12);
	if (snap->z == NULL) snap->z = (int16_t*) malloc(WIDTH*HEIGHT*12);
	if (snap->c == NULL) snap->c = (uint16_t*) malloc(WIDTH*HEIGHT*12);
	if (snap->nx == NULL) snap->nx = (int8_t*) malloc(WIDTH*HEIGHT*6);
	if (snap->ny == NULL) snap->ny = (int8_t*) malloc(WIDTH*HEIGHT*6);
	if (snap->nz == NULL) snap->nz = (int8_t*) malloc(WIDTH*HEIGHT*6);
	if (snap->sh == NULL) snap->sh = (uint8_t*) malloc(WIDTH*HEIGHT*6);
	fread(header, 1, 16, f);
	snap->s = 	header[0];
	snap->cx = 	header[1];
	snap->cy = 	header[2];
	snap->cz = 	header[3];
	cnt = snap->s;
	printf("size %d\n",cnt);
	fread(snap->x, 2, cnt, f);
	fread(snap->y, 2, cnt, f);
	fread(snap->z, 2, cnt, f);
	fread(snap->c, 2, cnt, f);
	fread(snap->nx, 1, cnt, f);
	fread(snap->ny, 1, cnt, f);
	fread(snap->nz, 1, cnt, f);
	fread(snap->sh, 1, cnt, f);
	fclose(f);
}

/* Function: draw_snapshot
	Draws snapshot. 
	
	Parameters:
		skip - 1 gives no skipping
*/
void draw_snapshot(Snapshot *snap, const uint32_t skip)
{
	uint32_t i, len = snap->s, color; Color32 c32;
	for (i=0; i<len; i+=skip) {
		c32.col = high2true(snap->c[i]);
		shade_spec(&c32, snap->nx[i]/128.0,
						 snap->ny[i]/128.0,
						 snap->nz[i]/128.0,
						 lightx, lighty, lightz,
						 snap->sh[i]);
		project(expand(snap->x[i], shrink_val)+snap->cx, 
				expand(snap->y[i], shrink_val)+snap->cy, 
				expand(snap->z[i], shrink_val)+snap->cz, 
				snap->nx[i], snap->ny[i], snap->nz[i], snap->sh[i],
				c32.col);
	}
}
