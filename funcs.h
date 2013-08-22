#include "defs.h"

/* SDL_plus.c */
void SDL_Initialize();
void SDL_FlipScreen();
__inline void SDL_DrawPixel(int32_t x, int32_t y, uint32_t col);
void SDL_HandleEvents();

/* color.c */
uint16_t true2high(uint32_t tru);
uint32_t high2true(uint16_t high);

/* lookfly.c */
void mouse_look();
void fly_forward(float speed);

/* fillholes.c */
void fill_holes();

/* plyreader.c */
void read_ply_xyz_normals(const char *filename, Cloud *cloud, 
							uint32_t col, uint8_t sh, float scale);

/* cloud.c */
/*void gen_sand_2x2m(Cloud *cloud);
void load_cloud(const char *filename, const uint32_t len, Cloud *cloud); */
void draw_cloud
	(Cloud *cloud, const int32_t xo, const int32_t yo, 
	const int32_t zo, const uint32_t skip);
void render_cloud
	(Cloud *cloud, const int32_t xo, const int32_t yo, 
	const int32_t zo, const uint32_t skip);

/* snapshot.c */
void take_snapshot(Snapshot *, const char *filename);
void load_snapshot(const char *filename, Snapshot *);
void draw_snapshot(Snapshot *snap, const uint32_t skip);
void render_scene(float y, float p, Snapshot *, uint32_t *counter);

/* project.c */
__inline void shade(Color32 *c, 
					float nx, float ny, float nz,
					float lx, float ly, float lz);
__inline void shade_spec(Color32 *c, 
					float nx, float ny, float nz,
					float lx, float ly, float lz, uint8_t sh);
__inline int32_t expand(int16_t x, float y);
__inline int16_t shrink(int32_t z, float y);
__inline uint8_t is_back_culled(int32_t px, int32_t py, int32_t pz,
								float nx, float ny, float nz);
void clear_zbuffer();
void clear_img(const uint32_t color);
void compute_yp();
void compute_viewdir();
void project(int32_t x, int32_t y, int32_t z, uint32_t col,
			 int8_t nx, int8_t ny, int8_t nz, uint8_t sh);
void project_render
	(const int32_t x, const int32_t y, const int32_t z, uint32_t  col,
	 int8_t nx, int8_t ny, int8_t nz, uint8_t sh);
void add_fog_to_img();
void add_spec_to_img();

/* perlin.c */
__inline void randomize(int32_t s);
__inline int32_t randm();
void noise_init();
float noise_3d(float x, float y, float z);
