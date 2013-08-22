#include "defs.h"
#include "data.h"
#include "funcs.h"

/* Function: read_ply_xyz_normals
	Reads ascii 1.0 stanford ply which contains only coordinates and normals. 
	Also assigns given color and applies default shading to it. */
void read_ply_xyz_normals(const char *filename, Cloud *cloud, 
							uint32_t col, uint8_t sh, float scale)
{
	FILE *f; char dummy[1024];
	uint32_t s, i; Color32 c32;
	float x,y,z,nx,ny,nz;
	f = fopen(filename, "r"); for(;;){
	fscanf(f,"ply\n");
	fscanf(f,"format ascii %f\n",&x);
	if (x!=1.0){ printf("wrong format!\n"); break; }
	fscanf(f,"%s\n",dummy);
	fscanf(f,"element vertex %d",&s);
	for(i=0;i<9;i++)fscanf(f,"%s\n",dummy);
	
	if (cloud->x != NULL) free(cloud->x);
	if (cloud->y != NULL) free(cloud->y);
	if (cloud->z != NULL) free(cloud->z);
	cloud->x = (int32_t*) malloc(s*4);
	cloud->y = (int32_t*) malloc(s*4);
	cloud->z = (int32_t*) malloc(s*4);
	cloud->c = (uint16_t*) malloc(s*2);
	cloud->nx = (int8_t*) malloc(s);
	cloud->ny = (int8_t*) malloc(s);
	cloud->nz = (int8_t*) malloc(s);
	cloud->sh = (int8_t*) malloc(s);
	cloud->s = s;
	
	for(i=0;i<s;i++) {
		fscanf(f, "%d %d %d %d %d %d\n", &x, &y, &z, &nx, &ny, &nz);
		cloud->x[i] = x*scale;
		cloud->y[i] = z*scale;
		cloud->z[i] = y*scale;
		cloud->nx[i] = nx*127.0;
		cloud->ny[i] = nz*127.0;
		cloud->nz[i] = ny*127.0;
		cloud->sh[i] = sh;
		c32.col = col;
		shade(&c32, nx, ny, nz, lightx, lighty, lightz);
		cloud->c[i] = true2high(c32.col);
	}
	
	break;}fclose(f);
}