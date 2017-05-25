/*
Вычисление интеграла с помощью метода трапеций с его илюстрацией
*/
#include <stdio.h>
#include "Graph.h"
#include <math.h>
//==============================================================================
double a, b, c, d;
double aInt, bInt;
int powerR;
double *r;
double valueIntegral;
//==============================================================================
void ftrash (FILE *fp, int n);
void fileRead();
void writeTerminal();
double f(double x);
void drawf();
void calculationIntegralf();
//==============================================================================

int main()
{
    fileRead();

    drawf();

    writeTerminal();
};
//==============================================================================

void calculationIntegralf()
{
    //Заполняет разбиение его элементами
    double xStep = (bInt-aInt)/(powerR-1);
    double xi = aInt;
    for (int i = 0; i < powerR; i++)
    {
        r[i] = xi;
        xi += xStep;
    }

    //рисует трапеции возле графика функции
    SetColor(100,100,100);
    for (int i = 0; i < powerR-1; i++)
    {
        SetPoint(r[i], 0);
        Line(r[i], f(r[i]));
        Line(r[i+1], f(r[i+1]));
    }
    Line(r[powerR-1], 0);

    //вычисление интеграла
    valueIntegral = 0;
    for (int i = 0; i < powerR-1; i++)
    {
        valueIntegral += (r[i+1] - r[i]) * (f(r[i]) + f(r[i+1])) * 0.5;
    }
};
//==============================================================================

void drawf()
{
    ReadWindow("input.bmp", a,b,c,d);
//------------------------------------------------------------------------------
    SetColor(0,0,0);
    xyLine(0,0,1,1);

    int delPlot = 100;
    double xStep = (b - a)/delPlot;

    SetColor(199,49,19);
    double x = a;

    SetPoint(x,f(x));
    for (int i = 0; i < delPlot; i++)
    {
        x+=xStep;
        Line(x,f(x));
    }
//------------------------------------------------------------------------------
    calculationIntegralf();
//------------------------------------------------------------------------------
    CloseWindow();
};
//==============================================================================

void writeTerminal()
{
    printf("a = %5.2lf\n", a);
    printf("b = %5.2lf\n", b);
    printf("c = %5.2lf\n", c);
    printf("d = %5.2lf\n", d);

    printf("\n");
    printf("powerR = %d\n", powerR);

    printf("\n");
    printf("aInt = %5.2lf\n", aInt);
    printf("bInt = %5.2lf\n", bInt);

    printf("\n");
    for (int i = 0; i < powerR; i++)
        {printf("r[%d] = %5.2lf\n", i, r[i]);}

    printf("\n");
    printf("valueIntegral = %5.2lf\n", valueIntegral);
};
//==============================================================================

double f(double x)
{
    return x*x*x;
    //return x - y;

    //#define sqr(x) (x)*(x)
    //return(x*x+2*sqr(3./5*pow(x*x,1./3)-y)-1);

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
    fscanf(fp, "%d", &powerR);

    r = new double[powerR];

    ftrash (fp, 2);
    fscanf(fp, "%lf", &aInt);

    ftrash (fp, 1);
    fscanf(fp, "%lf", &bInt);

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