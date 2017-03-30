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
double ai, bi;
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
double fCube(double x, double f, double df, double node, double a, double b);
void searchCoefficient(int i);
void drawfCube();
//==============================================================================

int main()
{
    readScaleFile();

    drawCoordinat();

    //рисует главный график с которым будем сравнивать другие графики
    //drawfMain();

    fillArrayXY();

    drawfCube();

    //drawfLograng();

//---------------------------------------------------
    CloseWindow();
};
//==============================================================================
void drawfCube()
{
    SetColor(0,255,0);

    int delPlot = 100;
    double xStep = (b - a)/delPlot;

    for (int i = 0; i < 3 - 1; i++)
    {
        double x = node[i];
        searchCoefficient(i);

        SetPoint(x, fCube(x, nodeValue[i], dNodeValue[i], node[i], ai, bi));
        for (int j = 0; j < delPlot; j++)
        {
            x+=xStep;
            Line(x, fCube(x, nodeValue[i], dNodeValue[i], node[i], ai, bi));
        }
    }
};
//==============================================================================

void searchCoefficient(int i)
{
    double h = node[i+1] - node[i];
    double f = nodeValue[i];
    double f1 = nodeValue[i+1];
    double df = dNodeValue[i];
    double df1 = dNodeValue[i+1];
    ai = (df - df1)/h;
    bi = (f1 - df*h - f)*pow(h, 4) + (df1 - df)*pow(h, 2);
};
//==============================================================================

double fCube(double x, double f, double df, double node, double a, double b)
{
    return pow(a*(x - node), 3) + pow(b*(x - node), 2) + df*(x - node) + f;
};
//==============================================================================

double fMain(double x)
{
  //return exp(-50*x*x);
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

void fillArrayXY()
{
    // забиваю массивы значениями узлов и значениями фукции в
    // этих точках значения беруться для определенной функции
    // чтобы проверить работу программы

    #define Count 3
    node = new double[Count];
    nodeValue = new double[Count];

    node[0] = 1;
    node[1] = 3;
    node[2] = 6;
    nodeValue[0] = 2;
    nodeValue[1] = 3;
    nodeValue[2] = 1;
/*
    node = new double[nodeCount];
    nodeValue = new double[nodeCount];

    double xStep = (b - a)/(nodeCount-1);
    double x = a;
//------------------------------------------------------------------------------
    for (int i = 0; i < nodeCount; i++)
    {
        node[i] = x;
        nodeValue[i] = fMain(node[i]);
        x+=xStep;
    }
*/
    dNodeValue = new double[Count];
    dNodeValue[0] = 0;
    dNodeValue[2] = 0;
    for (int i = 1; i < Count-1; i++)
    {
        dNodeValue[i] = (nodeValue[i+1] - nodeValue[i-1])/(node[i+1]-node[i-1]);
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