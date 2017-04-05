/*
Рисует линии уравня.
Тость рисует график функции в 3D где есть ширинa, длина, высота выраженная
цветом.
*/
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
int N;
double a, b, c, d;
int *red, *green, *blue;
double *valueZ;
//==============================================================================
double f(double x, double y);
void fileRead();
void ftrash (FILE *fp, int n);

//==============================================================================
int main()
{
  GetSize("input.bmp", &h, &w);
  R = new char[h*w];
  G = new char[h*w];
  B = new char[h*w];
  ReadImageFromFile("input.bmp",B,G,R);
//------------------------------------------------------------------------------
  fileRead();
//------------------------------------------------------------------------------
  double xStep = (b - a)/w;
  double yStep = (d - c)/h;

  int i = 0;
  for (double y = c; y < d; y += yStep)
  {
    for (double x = a; x < b; x += xStep)
    {
      double z = f(x,y);
      double zx = f(x-xStep, y);
      double zy = f(x, y-yStep);

      for (int j = 0; j < N-1; j++)
      {
        double a0 = valueZ[j];
        double a1 = valueZ[j+1];
        if (((a0 < zx && zx < a1) != (a0 < z && z < a1)) || ((a0 < zy && zy < a1) != (a0 < z && z < a1)))
          {R[i] = G[i] = B[i] = 0;}
      }
    i++;
    }
  }
//------------------------------------------------------------------------------
  WriteImage("output.bmp",B,G,R);
};
//==============================================================================
double f(double x, double y)
{
  //return x - y;

 // #define sqr(x) (x)*(x)
  //return(x*x+2*sqr(3./5*pow(x*x,1./3)-y)-1);

  return x*x+y*y;
  //return x*x+y;
  //return x*x - y*y;
};
//==============================================================================

void fileRead()
{
  FILE *fp;
  fp = fopen ("input.txt", "r");
//------------------------------------------------------------------------------
  ftrash (fp, 3);
  fscanf(fp, "%lf", &a);

  ftrash (fp, 2);
  fscanf(fp, "%lf", &b);

  ftrash (fp, 2);
  fscanf(fp, "%lf", &c);

  ftrash (fp, 2);
  fscanf(fp, "%lf", &d);

  ftrash (fp, 2);
  fscanf(fp, "%d", &N);

  valueZ = new double[N];

  red = new int[N];
  green = new int[N];
  blue = new int [N];

  ftrash(fp, 1);
  for (int i = 0; i < N; i++)
    {fscanf(fp, "%lf", &valueZ[i]);}

  ftrash(fp, 1);
  for (int i = 0; i < N; i++)
  {
    fscanf(fp, "%d", &red[i]);
    fscanf(fp, "%d", &green[i]);
    fscanf(fp, "%d", &blue[i]);
  }
//------------------------------------------------------------------------------
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