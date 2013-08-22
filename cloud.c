#include "data.h"
#include "funcs.h"

/* Function: draw_cloud
	Draws cloud with given offset and skipping value. Use only for debug 

	Parameters:
		xo, yo, zo - coordinate offsets
		skip - from 1 (no skipping) to N
*/
void draw_cloud
	(Cloud *cloud, 
	const int32_t xo, const int32_t yo, const int32_t zo, const uint32_t skip) 
{
	uint32_t i, len = cloud->s;
	for (i=0; i<len; i+=skip) {
		project(
			cloud->x[i]+xo, cloud->y[i]+yo, cloud->z[i]+zo, 
			high2true(cloud->c[i]),
			cloud->nx[i], cloud->ny[i], cloud->nz[i], cloud->sh[i]
		);
	}
}

/* Function: render_cloud
	Draw cloud with given offset and skipping value. Use for snapshot render 

	Parameters:
		xo, yo, zo - coordinate offsets
		skip - from 1 (no skipping) to N
*/
void render_cloud
	(Cloud *cloud, 
	const int32_t xo, const int32_t yo, const int32_t zo, const uint32_t skip) 
{
	uint32_t i, len = cloud->s;
	for (i=0; i<len; i+=skip) {
		project_render(
			cloud->x[i]+xo, cloud->y[i]+yo, cloud->z[i]+zo, 
			high2true(cloud->c[i]),
			cloud->nx[i], cloud->ny[i], cloud->nz[i], cloud->sh[i]
		);
	}
}
