#include <malloc.h>
#include <math.h>
// KEN PERLIN'S 3D NOISE. NOTHING TO ALTER HERE ANYMORE
#define NEW(Type,Size) (Type*)malloc(Size*sizeof(Type))
static int seed=1; __inline void randomize(int s) {seed=s;}
__inline int randm() {seed=(214013*seed+2531011); return((seed>>16)&0x7FFF);}
int*p_p;float p_d(float t){return t*t*t*(t*(t*6-15)+10);}float p_l(float t,
float a,float b){return a+t*(b-a);}float p_g(int p_h,float x,float y,float z)
{int h=p_h&15;float u=h<8?x:y,v=h<4?y:h==12||h==14?x:z;return ((h&1)==0?u:-u)
+((h&2)==0?v:-v);}void noise_init(){int i;p_p=NEW(int,512);for (i=0;i<256;i++)
p_p[256+i]=p_p[i]=randm()%256;}float noise_3d(float x,float y,float z){int X=
(int)floor(x)&255,Y=(int)floor(y)&255,Z=(int)floor(z)&255;float u,v,w;int A,
AA,AB,B,BA,BB;x-=floor(x);y-=floor(y);z-=floor(z);u=p_d(x);v=p_d(y);w=p_d(z);
A=p_p[X]+Y; AA=p_p[A]+Z; AB=p_p[A+1]+Z;B=p_p[X+1]+Y; BA=p_p[B]+Z; BB=p_p[B+1]
+Z;return p_l(w,p_l(v,p_l(u,p_g(p_p[AA],x ,y ,z),p_g(p_p[BA],x-1,y ,z)),p_l(u,
p_g(p_p[AB],x ,y-1,z),p_g(p_p[BB],x-1,y-1,z))),p_l(v,p_l(u,p_g(p_p[AA+1],x,y,
z-1),p_g(p_p[BA+1],x-1,y ,z-1)),p_l(u,p_g(p_p[AB+1],x ,y-1,z-1),p_g(p_p[BB+1],
x-1,y-1,z-1))));}
