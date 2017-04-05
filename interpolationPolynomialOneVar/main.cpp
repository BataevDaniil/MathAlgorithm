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
int nodeCount;
double *node;
double *nodeValue;
double *dNodeValue;
double Nx = 1, Ny = 1;
//==============================================================================
double fMain(double x);
double fLograng(double x);
void readScaleFile();
void fillArrayXY();
void ftrash (FILE *fp, int n);
void drawCoordinat();
void drawfMain();
void drawfLograng();
double fCube(double x, int i);
void searchCoefficient();
void drawfCube();
void wirteTerminal();
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

    wirteTerminal();

    drawfLograng();

//---------------------------------------------------
    CloseWindow();
};
//==============================================================================
void drawfCube()
{
    SetColor(0,255,0);

    int delPlot = 100;

    for (int i = 0; i < nodeCount-1; i++)
    {
        double xStep = (node[i+1] - node[i])/delPlot;

        double x = node[i];

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
    ai = new double[nodeCount-1];
    bi = new double[nodeCount-1];

    for (int i = 0; i < nodeCount-1; i++)
    {
        double h = node[i+1] - node[i];
        double f = nodeValue[i];
        double f1 = nodeValue[i+1];
        double df = dNodeValue[i];
        double df1 = dNodeValue[i+1];

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
    double f = nodeValue[i];
    double df = dNodeValue[i];
    double xi = node[i];

    return ai[i]*pow(x - xi, 3) + bi[i]*pow(x - xi, 2) + df*(x - xi) + f;
};
//==============================================================================
void wirteTerminal()
{
    printf("a = %3.2lf b = %3.2lf c = %3.2lf d = %3.2lf\n", a, b, c, d);
    printf("nodeCount = %d\n", nodeCount);

    for (int i = 0; i < nodeCount; i++)
        {printf("x[%d]     = %6.2lf  ", i, node[i]);}
    printf("\n");

    for (int i = 0; i < nodeCount; i++)
        {printf("f(x[%d])  = %6.2lf  ", i, nodeValue[i]);}
    printf("\n");

    for (int i = 0; i < nodeCount; i++)
        {printf("df(x[%d]) = %6.2lf  ", i, dNodeValue[i]);}
    printf("\n");

    for (int i = 0; i < nodeCount-1; i++)
        {printf("ai[%d])   = %6.2lf  ", i, ai[i]);}
    printf("\n");

    for (int i = 0; i < nodeCount-1; i++)
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

    node = new double[nodeCount];
    nodeValue = new double[nodeCount];
    dNodeValue = new double[nodeCount];

    double xStep = (b - a)/(nodeCount-1);
    double x = a;
//------------------------------------------------------------------------------
    for (int i = 0; i < nodeCount; i++)
    {
        node[i] = x;
        nodeValue[i] = fMain(node[i]);
        x+=xStep;
    }

    dNodeValue[0] = (nodeValue[1] - nodeValue[0])/(node[1] - node[0]);
    dNodeValue[nodeCount-1] = (nodeValue[nodeCount-2] - nodeValue[nodeCount-1])/(node[nodeCount-2] - node[nodeCount-1]);

    for (int i = 1; i < nodeCount-1; i++)
    {
        double f2 = nodeValue[i+1];
        double f1 = nodeValue[i];
        double f0 = nodeValue[i-1];

        if ((f1 > f0 && f1 > f2) || (f1 < f0 && f1 < f2))
        {
            dNodeValue[i] = 0;
        }
        else{
            double x1 = node[i+1];
            double x0 = node[i-1];

            dNodeValue[i] = (f2-f0)/(x1-x0);
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
    fscanf(fp, "%d", &nodeCount);
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