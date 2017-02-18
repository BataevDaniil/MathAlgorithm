#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "ReadImage.h"
#include <math.h>

using namespace std;
//==============================================================================
int h,w;
char *R,*G,*B;
//==============================================================================
int n;
double a, b, c, d;
int *red, *green, *blue;
double *valueZ;
//==============================================================================
double f(double x, double y);
void fileRead();
void ftrash (FILE *fp, int n);
int remakeColor(int color);
//==============================================================================
int main()
{
	GetSize("input.bmp", &h, &w);
  R = new char[h*w];
  G = new char[h*w];
  B = new char[h*w];
  ReadImageFromFile("input.bmp",B,G,R);
//==============================================================================
  fileRead();
//==============================================================================
  double xStep = (b - a)/w;
	double yStep = (d - c)/h;

	printf("xStep = %lf\n", xStep);
  printf("yStep = %lf\n", yStep);

	int i = 0;
  for (double y = c; y < d; y += yStep)
  {
		for (double x = a; x < b; x += xStep)
		{
			for (int j = 0; j < n-1; j++)
      {
			  double z = f(x,y);

        if ((valueZ[j] <= z) && (z <= valueZ[j+1]))
        {
          R[i] = red[j];
          G[i] = green[j];
          B[i] = blue[j];
        }
		  }
		i++;
		}
  }

int count = 0;
	for (int y = 1; y < h; y++)
	  for (int x = 1; x < w; x++)
		  if (R[y*w+x] != R[y*w + x-1])
			  if (G[y*w+x] != G[y*w + x-1])
				  if (B[y*w+x] != B[y*w + x-1])
      if (R[y*w+x] != R[(y-1)*w + x])
			  if (G[y*w+x] != G[(y-1)*w + x])
				  if (B[y*w+x] != B[(y-1)*w + x])
					  {R[y*w+x] = G[y*w+x] = B[y*w+x] = 0;count++;}
					else {R[y*w+x] = G[y*w+x] = B[y*w+x] = 255;}
					else {R[y*w+x] = G[y*w+x] = B[y*w+x] = 255;}
					else {R[y*w+x] = G[y*w+x] = B[y*w+x] = 255;}
					else {R[y*w+x] = G[y*w+x] = B[y*w+x] = 255;}
					else {R[y*w+x] = G[y*w+x] = B[y*w+x] = 255;}
					else {R[y*w+x] = G[y*w+x] = B[y*w+x] = 255;}
						printf("%d\n",count);


	WriteImage("output.bmp",B,G,R);
};
//==============================================================================
double f(double x, double y)
{
  //return x - y;

	#define sqr(x) (x)*(x)
  return(x*x+2*sqr(3./5*pow(x*x,1./3)-y)-1);

	//return x*x+y*y;
	//return x*x+y;
	//return x*x - y*y;
};
//==============================================================================
void fileRead()
{
  FILE *fp;
  fp = fopen ("input.txt", "r");

  ftrash (fp, 3);
  fscanf(fp, "%lf", &a);

  ftrash (fp, 2);
  fscanf(fp, "%lf", &b);

  ftrash (fp, 2);
  fscanf(fp, "%lf", &c);

  ftrash (fp, 2);
  fscanf(fp, "%lf", &d);

  ftrash (fp, 2);
  fscanf(fp, "%d", &n);

  valueZ = new double[n];

	red = new int[n];
	green = new int[n];
	blue = new int [n];

  ftrash(fp, 1);
	for (int i = 0; i < n; i++)
	  {fscanf(fp, "%lf", &valueZ[i]);}

	ftrash(fp, 1);
	for (int i = 0; i < n; i++)
	{
	  fscanf(fp, "%d", &red[i]);
	  fscanf(fp, "%d", &green[i]);
	  fscanf(fp, "%d", &blue[i]);
	}

  printf("n = %d\n", n);
  printf("a = %lf\n", a);
  printf("b = %lf\n", b);
  printf("c = %lf\n", c);
  printf("d = %lf\n", d);

	for (int i = 0; i < n; i++)
	  {printf("%lf  ", valueZ[i]);}

  printf("\n");
	for (int i = 0; i < n; i++)
	{
	  printf("%d  ", red[i]);
	  printf("%d  ", green[i]);
	  printf("%d\n", blue[i]);
	}

  fclose(fp);
};
//==============================================================================
void ftrash (FILE *fp, int n)
{
  char trash[500];
  for (int i = 0; i < n; i++)
    {fscanf(fp, "%s", trash);}
};
//==============================================================================
int remakeColor(int color)
{
	return (color < 0)?(color+=256):(color);
};
//==============================================================================
