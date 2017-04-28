/*
Построение графика функции от одной переменной по точкам с помощью
интрополяционого полинома Логранжа.
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "Graph.h"
#include <math.h>

using namespace std;
//==============================================================================
double a, b, c, d;
double *ai, *bi;
int nodeXCount;
double *nodeX;
double *nodeY;
double *dNodeY;
double Nx = 1, Ny = 1;
//==============================================================================
void wirteTerminal();
void fillArrayXY();

double fMain(double x);
double fLograng(double x);
double fCube(double x, int i);

void readScaleFile();
void drawCoordinat();
void searchCoefficient();

void drawfMain();
void drawfLograng();
void drawfCube();

void ftrash (FILE *fp, int n);
//==============================================================================

int main()
{
      readScaleFile();

      drawCoordinat();

      fillArrayXY();


      //рисует главный график с которым будем сравнивать другие графики
      drawfMain();

      searchCoefficient();
      drawfCube();

      //wirteTerminal();

      //drawfLograng();

//---------------------------------------------------
      CloseWindow();
};
//==============================================================================
void drawfCube()
{
      SetColor(0,255,0);

      int delPlot = 100;

      for (int i = 0; i < nodeXCount-1; i++)
      {
            double xStep = (nodeX[i+1] - nodeX[i])/delPlot;

            double x = nodeX[i];

            SetPoint(x, fCube(x, i));
            for (int j = 0; j < delPlot; j++)
            {
                  x+=xStep;
                  Line(x, fCube(x, i));
            }
      }
};
//==============================================================================

void searchCoefficient()
{
      ai = new double[nodeXCount-1];
      bi = new double[nodeXCount-1];

      for (int i = 0; i < nodeXCount-1; i++)
      {
            double h = nodeX[i+1] - nodeX[i];

            double f = nodeY[i];
            double f1 = nodeY[i+1];

            double df = dNodeY[i];
            double df1 = dNodeY[i+1];

            double a1 = h*h*h;
            double a2 = h*h;
            double a3 = 3*h*h;
            double a4 = 2*h;
            double b1 = f1 - df*h - f;
            double b2 = df1 - df;

            bi[i] = (b2*a1 - b1*a3)/(a4*a1 - a3*a2);
            ai[i] = (b1 - a2*bi[i])/a1;
      }
};
//==============================================================================

double fCube(double x, int i)
{
      double f = nodeY[i];
      double df = dNodeY[i];
      double xi = nodeX[i];

      return ai[i]*pow(x - xi, 3) + bi[i]*pow(x - xi, 2) + df*(x - xi) + f;
};
//==============================================================================
void wirteTerminal()
{
      printf("a = %3.2lf b = %3.2lf c = %3.2lf d = %3.2lf\n", a, b, c, d);
      printf("nodeXCount = %d\n", nodeXCount);

      for (int i = 0; i < nodeXCount; i++)
            {printf("x[%d]     = %6.2lf  ", i, nodeX[i]);}
      printf("\n");

      for (int i = 0; i < nodeXCount; i++)
            {printf("f(x[%d])  = %6.2lf  ", i, nodeY[i]);}
      printf("\n");

      for (int i = 0; i < nodeXCount; i++)
            {printf("df(x[%d]) = %6.2lf  ", i, dNodeY[i]);}
      printf("\n");

      for (int i = 0; i < nodeXCount-1; i++)
            {printf("ai[%d])   = %6.2lf  ", i, ai[i]);}
      printf("\n");

      for (int i = 0; i < nodeXCount-1; i++)
            {printf("bi[%d])   = %6.2lf  ", i, bi[i]);}
      printf("\n");
}

double fMain(double x)
{
  return exp(-50*x*x);
//---------------------------------------------------
  //return sin(x);
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

void drawfMain()
{
      //рисует главный график с которым будем сравнивать другие графики
      SetColor(255,0,0);

      int delPlot = 100;
      double xStep = (b - a)/delPlot;
      double x=a;

      SetPoint(x,fMain(x));
      for (int i = 0; i < delPlot; i++)
      {
            x+=xStep;
            Line(x,fMain(x));
      }

};
//==============================================================================

double fLograng(double x)
{
      double multi;
      double sum = 0;
      for (int i = 0; i < nodeXCount; i++)
      {
            multi = 1;
            for (int j = 0; j < nodeXCount; j++)
            {
                  if (j==i)
                        {continue;}
                  multi *= (x-nodeX[j]) / (nodeX[i]-nodeX[j]);
            }
            sum += nodeY[i]*multi;
      }
      return sum;
};
//==============================================================================

void drawfLograng()
{

      SetColor(0,0,255);

      int delPlot = 100;
      double xStep = (b - a)/delPlot;
      double x=a;

      SetPoint(x,fLograng(x));
      for (int i = 0; i < delPlot; i++)
      {
            x+=xStep;
            Line(x,fLograng(x));
      }
};
//==============================================================================

void fillArrayXY()
{
      // забиваю массивы значениями узлов и значениями фукции в
      // этих точках значения беруться для определенной функции
      // чтобы проверить работу программы

      nodeX = new double[nodeXCount];
      nodeY = new double[nodeXCount];
      dNodeY = new double[nodeXCount];

      double xStep = (b - a)/(nodeXCount-1);
      double x = a;

      for (int i = 0; i < nodeXCount; i++)
      {
            nodeX[i] = x;
            nodeY[i] = fMain(nodeX[i]);
            x+=xStep;
      }

      {
            double deltaY = nodeY[1] - nodeY[0];
            double deltaX = nodeX[1] - nodeX[0];

            dNodeY[0] = deltaY / deltaX;
      }

      {
            double deltaY = nodeY[nodeXCount-1] - nodeY[nodeXCount-2];
            double deltaX = nodeX[nodeXCount-1] - nodeX[nodeXCount-2];

            dNodeY[nodeXCount-1] = deltaY / deltaX;
      }

      for (int i = 1; i < nodeXCount-1; i++)
      {
            double f2 = nodeY[i+1];
            double f1 = nodeY[i];
            double f0 = nodeY[i-1];

            if ((f1 > f0 && f1 > f2) || (f1 < f0 && f1 < f2))
            {
                  dNodeY[i] = 0;
            }
            else{
                  double x1 = nodeX[i+1];
                  double x0 = nodeX[i-1];

                  dNodeY[i] = (f2-f0)/(x1-x0);
                  }
      }

};
//==============================================================================

void readScaleFile()
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
      fscanf(fp, "%d", &nodeXCount);
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

void drawCoordinat()
{
      SetColor(250,250,250);
      SetWindow(a,b,c,d);

      SetColor(0,0,0);
      xyLine(0,0,Nx,Ny);
};
//==============================================================================