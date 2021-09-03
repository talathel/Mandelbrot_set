#include <stdio.h>
#include <stdlib.h>
#include <eggx.h>
#include <math.h>
#define l 1000
#define h 1000
#define epsilon 0.001
#define length 50
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
float complex_abs(struct complex x)
{
	return sqrt(x.real*x.real+x.imag*x.imag);
}
int check_sequence(struct complex* sequence, int len)
{
	return ((complex_abs(sequence[len-1]) > epsilon) && ((complex_abs(sequence[len-1]) < 2.0)));
}
int main()
{
	struct complex c;
	int win, current_length;
	win = gopen(l,h);
	winname(win,"Mandelbrot set");
	gsetbgcolor(win,"white");
	gclr(win);
	coordinate(win, 0,0, -2.0,-2.0, 250.0,250.0);
	for (c.real = -2.0; c.real <= 2.0; c.real+=0.001)
		for (c.imag = -2.0; c.imag <= 2.0; c.imag+=0.001)
		{
			struct complex* arr = (struct complex*) malloc(length*sizeof(struct complex));
			arr[0].real = 0.0;
			arr[0].imag = 0.0;
			current_length = 1;
			do
			{
				arr[current_length] = calculate(arr[current_length - 1], c);
				current_length++;
			} while((check_sequence(arr,current_length)) && (current_length < length));
			if (check_sequence(arr,current_length))
			{
				newcolor(win,"Black");
				pset(win,c.real,c.imag);
			}
			free(arr);

		}
	gsaveimage(win,0,-2.0,-2.0,2.0,2.0,"pnmtopng",16,"Mandelbrot_set.png");
	ggetch();
	gclose(win);
	return 0;
}
