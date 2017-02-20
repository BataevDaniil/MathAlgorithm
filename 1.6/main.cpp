#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "Graph.h"
#include <math.h>

using namespace std;
//==============================================================================
double a, b, c, d;
double eps;
#define pi 3.141592;
//==============================================================================
double f(double x);
double df(double x);
void fileRead();
void ftrash (FILE *fp, int n);
int remakeColor(int color);
//==============================================================================
int main()
{
  SetWindow(a,b,c,d);
//==============================================================================
  fileRead();
//==============================================================================
  double Nx = 0.1, Ny = 0.1;
  int delPlot = 100;
  double xStep = (b - a)/delPlot;

  printf("xStep = %lf\n", xStep);

  SetColor(250,250,250);
	SetWindow(a,b,c,d);

	SetColor(0,0,0);
	xyLine(a,0,Nx,Ny);

  //рисует график
  SetColor(199,49,19);
  double x=a;
  SetPoint(x,f(x));
  for (int i = 0; i < delPlot; i++)
  {
    x+=xStep;
    Line(x,f(x));
  }

  //поиск решеения f(x) и отрисовка
  double xk = b;

  SetColor(0,200,0);
  SetPoint(xk,0);
  Line(xk, f(xk));

  SetColor(0,0,200);
  SetPoint(b, df(xk)*(b-xk)+f(xk));
  Line(a, df(xk)*(a-xk)+f(xk));

  while(fabs(f(xk)) > eps)
  {
    xk -= f(xk)/df(xk);
    //прямы вниз от промежуточных подсчетов
    SetColor(0,200,0);
    SetPoint(xk,0);
    Line(xk, f(xk));

    //касатеьная к промежуточныи подсчетом
    SetColor(0,0,200);
    SetPoint(b, df(xk)*(b-xk)+f(xk));
    Line(a, df(xk)*(a-xk)+f(xk));
  }

  printf("f(xk) = %lf\n", f(xk));
  printf("xk = %lf\n", xk);
  printf("eps = %lf\n", eps);

  CloseWindow();
};
//==============================================================================
double f(double x)
{
  return sin(x) + pow(x,5) - 1;
  //return x - y;

	//#define sqr(x) (x)*(x)
  //return(x*x+2*sqr(3./5*pow(x*x,1./3)-y)-1);

	//return x*x+y*y;
	//return x*x+y;
	//return x*x - y*y;
};
//==============================================================================
double df(double x)
{
  return cos(x) + 5*pow(x,4);
};
//==============================================================================
void fileRead()
{
  FILE *fp;
  fp = fopen ("input.txt", "r");

  ftrash (fp, 1);
  fscanf(fp, "%lf", &a);

  ftrash (fp, 1);
  fscanf(fp, "%lf", &b);

  ftrash (fp, 1);
  fscanf(fp, "%lf", &c);

  ftrash (fp, 1);
  fscanf(fp, "%lf", &d);

  ftrash (fp, 1);
  fscanf(fp, "%lf", &eps);

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
