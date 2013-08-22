/* perlin */
float noise_3d(float x, float y, float z);
void  noise_init();

#include <malloc.h>
#include <math.h>
int*p_p;float p_d(float t){return t*t*t*(t*(t*6-15)+10);}float p_l(float t,
float a,float b){return a+t*(b-a);}float p_g(int p_h,float x,float y,float z)
{int h=p_h&15;float u=h<8?x:y,v=h<4?y:h==12||h==14?x:z;return ((h&1)==0?u:-u)
+((h&2)==0?v:-v);}void noise_init(){int i;p_p=calloc(512,4);for(i=0;i<256;i++)
p_p[256+i]=p_p[i]=rand()%256;}float noise_3d(float x,float y,float z){int X=
(int)floor(x)&255,Y=(int)floor(y)&255,Z=(int)floor(z)&255;float u,v,w;int A,
AA,AB,B,BA,BB;x-=floor(x);y-=floor(y);z-=floor(z);u=p_d(x);v=p_d(y);w=p_d(z);
A=p_p[X]+Y; AA=p_p[A]+Z; AB=p_p[A+1]+Z;B=p_p[X+1]+Y; BA=p_p[B]+Z; BB=p_p[B+1]
+Z;return p_l(w,p_l(v,p_l(u,p_g(p_p[AA],x ,y ,z),p_g(p_p[BA],x-1,y ,z)),p_l(u,
p_g(p_p[AB],x ,y-1,z),p_g(p_p[BB],x-1,y-1,z))),p_l(v,p_l(u,p_g(p_p[AA+1],x,y,
z-1),p_g(p_p[BA+1],x-1,y ,z-1)),p_l(u,p_g(p_p[AB+1],x ,y-1,z-1),p_g(p_p[BB+1],
x-1,y-1,z-1))));}

/* generator */
int not_empty(float x, float y, float z, float s)
{
    return noise_3d(x * s, y * s, z * s) <= -0.25;
}

int empty(float x, float y, float z, float s)
{
    return !not_empty(x, y, z, s);
}

#include <stdio.h>
int counter = 0;
void write_point(int x, int y, int z, FILE *pcloud)
{
    counter++;
    fprintf(pcloud, "%d %d %d\n", x, y, z);
}

void gen(int w, int h, int d, float s, FILE *pcloud)
{
    s = 1.0/s;
    int x, y, z;
    int i = 0, p = 0;
    int count100 = (w * h * d)/100;
    for (x = 0; x < w; x++)
    for (y = 0; y < h; y++)
    for (z = 0; z < d; z++)
    {
        i++; if (i == count100) { i = 0; printf("%d%%\n", p++); }
        if (y == 0) { write_point(x, y, z, pcloud); continue; } 
        if (not_empty(x, y, z, s))
        {
            if (y == h - 1 ||
                empty(x + 1, y, z, s) ||
                empty(x - 1, y, z, s) ||
                empty(x, y + 1, z, s) ||
                empty(x, y - 1, z, s) ||
                empty(x, y, z + 1, s) ||
                empty(x, y, z - 1, s)) write_point(x, y, z, pcloud);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 6)
    {
        printf("usage:   %s output.txt xsize ysize zsize scale\n", argv[0]);
        printf("example: %s output.txt 300 200 350 30\n", argv[0]);
        return 0;
    }
    
    FILE *pcloud = fopen(argv[1], "w");
    noise_init();
    int w, h, d, s;
    w = atoi(argv[2]);
    h = atoi(argv[3]);
    d = atoi(argv[4]);
    s = atoi(argv[5]);
    gen(w, h, d, s, pcloud);
    fclose(pcloud);
    printf("Done! %d lines written\n", counter);
}
