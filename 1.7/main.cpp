#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "Graph.h"
#include <math.h>

using namespace std;
//==============================================================================
double a, b, c, d;
int nodeCount;
double *node;
double *nodeValue;
//==============================================================================
double f(double x);
double fLograng(double x);
void fileRead();
void fillArrayXY();
void ftrash (FILE *fp, int n);
int remakeColor(int color);
//==============================================================================
int main()
{
  SetWindow(a,b,c,d);
//------------------------------------------------------------------------------
  fileRead();
//------------------------------------------------------------------------------
  double Nx = 1., Ny = 0.1;
  int delPlot = 100;
  double xStep = (b - a)/delPlot;

  printf("xStep = %lf\n", xStep);

  SetColor(250,250,250);
	SetWindow(a,b,c,d);

	SetColor(0,0,0);
	xyLine(0,0,Nx,Ny);
//==============================================================================
  //рисует график с которым будем сравнивать график нарисованный полиномом
  SetColor(255,0,0);
  double x=a;
  SetPoint(x,f(x));
  for (int i = 0; i < delPlot; i++)
  {
    x+=xStep;
    Line(x,f(x));
  }
//==============================================================================
  //построение графика по точкам с помощью интрополяционого
  //многочлена Логранжа
  fillArrayXY();
//------------------------------------------------------------------------------
  SetColor(0,0,255);
  xStep = (b - a)/delPlot;
  x=a;
  SetPoint(x,fLograng(x));
  for (int i = 0; i < delPlot; i++)
  {
    x+=xStep;
    Line(x,fLograng(x));
  }
//------------------------------------------------------------------------------
  CloseWindow();
};
//==============================================================================
double f(double x)
{
//---------------------------------------------------
  return sin(x);
//---------------------------------------------------
  //return sin(x) + pow(x,5) - 1;
//---------------------------------------------------
  //return x - y;
//---------------------------------------------------
	//#define sqr(x) (x)*(x)
  //return(x*x+2*sqr(3./5*pow(x*x,1./3)-y)-1);
//---------------------------------------------------
	//return x*x+y*y;
//---------------------------------------------------
	//return x*x - y*y;
//---------------------------------------------------
};
//==============================================================================
double fLograng(double x)
{
  double multi;
  double sum = 0;
  for (int i = 0; i < nodeCount; i++)
  {
    multi = 1;
    for (int j = 0; j < nodeCount; j++)
    {
      if (j==i)
        {continue;}
      multi *= (x-node[j]) / (node[i]-node[j]);
    }
    sum += nodeValue[i]*multi;
  }
  return sum;
};
//==============================================================================
void fillArrayXY()
{
  // забиваю массивы значениями узлов и значениями фукции в
  // этих точках значения берутбся для определенной функции
  // чтобы проверить работу программы
  node = new double[nodeCount];
  nodeValue = new double[nodeCount];
  double xStep = (b - a)/(nodeCount-1);
  node[0] = a;
  node[nodeCount-1] = b;
  nodeValue[0] = f(a);
  nodeValue[nodeCount-1] = f(b);
//------------------------------------------------------------------------------
  for (int i = 1; i < nodeCount-1; i++)
  {
    node[i] = a + xStep*i;
    nodeValue[i] = f(node[i]);
  }
//------------------------------------------------------------------------------
  for (int i = 0; i < nodeCount; i++)
  {
    printf("node[%d] = %lf\n", i, node[i]);
    printf("nodeValue[%d] = %lf\n\n", i, nodeValue[i]);
  }
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
  fscanf(fp, "%d", &nodeCount);
//------------------------------------------------------------------------------
  printf("a = %lf\n", a);
  printf("b = %lf\n", b);
  printf("c = %lf\n", c);
  printf("d = %lf\n", d);
  printf("node = %d\n", nodeCount);
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
