/*
Находит корень уравнения с помощью метода деления отрезка пополам и
метода Ньютона. Число интераций обоих алгоритмов записывается в файл.
Метод Ньютона проилюстрированн графически.
*/
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "Graph.h"
#include <math.h>

using namespace std;
//==============================================================================
double a, b, c, d;
double eps;
int countInterac;
//==============================================================================
double f(double x);
double df(double x);
void fileRead();
void ftrash (FILE *fp, int n);
//==============================================================================

int main()
{

  FILE *fp;
  fp = fopen("output.txt", "w");
//------------------------------------------------------------------------------
  fileRead();
//------------------------------------------------------------------------------
  SetWindow(a,b,c,d);
//------------------------------------------------------------------------------
  double Nx = 0.1, Ny = 0.1;
  int delPlot = 100;
  double xStep = (b - a)/delPlot;

  SetColor(250,250,250);
  SetWindow(a,b,c,d);

  SetColor(0,0,0);
  xyLine(a,0,Nx,Ny);

//------------------------------------------------------------------------------
  //Рисует график
  SetColor(199,49,19);
  double x=a;
  SetPoint(x,f(x));
  for (int i = 0; i < delPlot; i++)
  {
    x+=xStep;
    Line(x,f(x));
  }

//------------------------------------------------------------------------------
  //Поиск решения уравенения с помощью метода Ньютона и отрисовка.
  double xk = b;

  SetColor(0,200,0);
  SetPoint(xk,0);
  Line(xk, f(xk));

  SetColor(0,0,200);
  SetPoint(b, df(xk)*(b-xk)+f(xk));
  Line(a, df(xk)*(a-xk)+f(xk));

  countInterac = 0;
  while(fabs(f(xk)) > eps)
  {
    xk -= f(xk)/df(xk);
    //Прямые вниз от промежуточных подсчетов до Ox.
    SetColor(0,200,0);
    SetPoint(xk,0);
    Line(xk, f(xk));

    //Касатеьная к промежуточныи подсчетом.
    SetColor(0,0,200);
    SetPoint(b, df(xk)*(b-xk)+f(xk));
    Line(a, df(xk)*(a-xk)+f(xk));
    countInterac++;
  }
  fprintf(fp, "1 = %d \n", countInterac);
  fprintf(fp, "Метод Ньютона = %lf \n", f(xk));

//------------------------------------------------------------------------------
  //Метод деления отрезка пополам.
  countInterac = 0;
  double decision;

  do
  {
    decision = (b+a)/2;

    if (f(decision)*f(b) > 0)
      {b = decision;}
    else {a = decision;}

  countInterac++;
  }
  while(fabs(f(decision)) > eps);

  fprintf(fp, "2 = %d \n", countInterac);
  fprintf(fp, "половины= %lf \n", f(decision));
//------------------------------------------------------------------------------
  CloseWindow();
  fclose(fp);
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
