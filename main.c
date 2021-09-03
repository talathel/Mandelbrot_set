#include <stdio.h>
#include <eggx.h>
#include <math.h>
#define l 1000
#define h 1000
struct complex
{
	float real;
	float imag;
};
struct complex calculate(struct complex z, struct complex c)
{
	struct complex t;
	t.real = z.real*z.real-z.imag*z.imag+c.real;
	t.imag = 2*z.real*z.imag+c.imag;
	return t;	
}
int main()
{
	struct complex c;
	struct complex z;
	int win;
	win = gopen(l,h);
	winname(win,"Mandelbrot set");
	gsetbgcolor(win,"white");
	gclr(win);
	coordinate(win, 0,0, -2.0,-2.0, 250.0,250.0) ;
	for (c.real = -2.0; c.real <= 2.0; c.real+=0.01)
		for (c.imag = -2.0; c.imag <= 2.0; c.imag+=0.01)
		{
			z.real = 0.0;
			z.imag = 0.0;
			for (int i=0; i< 100; i++)
        		{
               			z = calculate(z,c);
				if (fabs(sqrt(z.real*z.real+z.imag*z.imag)) < 2.001)
                		{
					newcolor(win,"Black");
                                	pset(win,z.real,z.imag);
				}
        		}
		}
	ggetch();
	gclose(win);
	return 0;
}
