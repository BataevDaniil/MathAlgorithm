/*
    double xStep = (b - a)/w;
    double yStep = (d - c)/h;

    for (int i = 0; i < nodeCount-1; i++)
    {
        for (int j = 0; j < nodeCount-1; j++)
        {
            kfLine(i, j);

            kfPlane(i, j, 0);
            for (double y = nodeY[i]; y < nodeY[i+1]; y += yStep;)
                for (double x = fLine(y); x > nodeX[j]; x -= xStep)
                    {defiColorPoint( fPlane(x, y) );}

            kfPlane(i, j, 1);
            for (double y = nodeY[i]; y < nodeY[i+1]; y += yStep;)
                for (double x = fLine(y); x < nodeX[j+1]; x += xStep)
                    {defiColorPoint( fPlane(x, y) );}
        }
    }
*/
#include <stdio.h>
#include "Graph.h"
#include <math.h>

//==============================================================================
double a, b, c, d;
int *red, *green, *blue;

int countPointInterval;
double *pointInterval;

double *nodeX, *nodeY, *nodeZ;
int nodeCount;

double aPlane, bPlane, dPlane;

double k;
//==============================================================================
void ftrash( FILE *fp, int n );

void fileRead();
void writeTerminal();

void fillArrayXYZ();
double fTest( double x, double y );

void drawfTest();
void drawf();

void kfPlane( int i, int j, bool Yn );
double fPlane( double x, double y );
double fLine( int i, int j, double y );
void defiColorPoint( int i, double z );
//==============================================================================

int main()
{
    fileRead();
    fillArrayXYZ();
    writeTerminal();
//------------------------------------------------------------------------------
    drawfTest();

    drawf();
};
//==============================================================================

void drawf()
{

    ReadWindow("input.bmp", a,b,c,d);
//------------------------------------------------------------------------------
    double xStep = (b - a)/w;
    double yStep = (d - c)/h;

    //printf("xStep = %lf\n", xStep);
    //printf("yStep = %lf\n", yStep);


//------------------------------------------------------------------------------
    CloseWindow("f.bmp");
};
//==============================================================================

void kfPlane(int i, int j, bool Yn)
{

};
//==============================================================================

double fPlane(double x, double y)
{
    return aPlane*x + bPlane*y + dPlane;
};
//==============================================================================

double fLine( int i, int j, double y )
{
    double x1 = nodeX[i+1];
    double y1 = nodeY[j-1];
    double x2 = nodeX[i];
    double y2 = nodeY[j];

    return (y - y1)*(x2 - x1)\(y2 - y1) + x1;
};
//==============================================================================

void defiColorPoint(int i, double z)
{
    for (int j = 0; j < countPointInterval-1; j++)
    {
        if ((pointInterval[j] <= z) && (z <= pointInterval[j+1]))
        {
            R[i] = red[j];
            G[i] = green[j];
            B[i] = blue[j];
        }
    }

};
//==============================================================================

void fillArrayXYZ()
{
    nodeX = new double[nodeCount];
    nodeY = new double[nodeCount];
    nodeZ = new double[nodeCount];

    double xStep = (b - a)/(nodeCount-1);
    double yStep = (d - c)/(nodeCount-1);

    //printf("xStep = %lf\n", xStep);
    //printf("yStep = %lf\n", yStep);

    double x = a;
    double y = c;

    for (int i = 0; i < nodeCount; i++)
    {
        nodeX[i] = x;
        nodeY[i] = y;
        nodeZ[i] = fTest(x, y);
        x += xStep;
        y += yStep;
    }
};
//==============================================================================

void drawfTest()
{
    ReadWindow("input.bmp", a,b,c,d);
//------------------------------------------------------------------------------
    double xStep = (b - a)/w;
    double yStep = (d - c)/h;

    int i = 0;
    for (double y = c; y < d; y += yStep)
    {
        for (double x = a; x < b; x += xStep)
        {
            defiColorPoint(i, fTest(x,y));
            i++;
        }
    }
//------------------------------------------------------------------------------
    CloseWindow("fTest.bmp");

};
//==============================================================================

double fTest(double x, double y)
{
    return x + y;

    //#define sqr(x) (x)*(x)
    //return(x*x+2*sqr(3./5*pow(x*x,1./3)-y)-1);

    //return x*x + y*y;
    //return x*x + y;
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
    fscanf(fp, "%d", &countPointInterval);

    ftrash (fp, 2);
    fscanf(fp, "%d", &nodeCount);

    pointInterval = new double[countPointInterval];

    red = new int[countPointInterval];
    green = new int[countPointInterval];
    blue = new int [countPointInterval];

    ftrash(fp, 1);
    for (int i = 0; i < countPointInterval; i++)
        {fscanf(fp, "%lf", &pointInterval[i]);}

    ftrash(fp, 1);
    for (int i = 0; i < countPointInterval; i++)
    {
        fscanf(fp, "%d", &red[i]);
        fscanf(fp, "%d", &green[i]);
        fscanf(fp, "%d", &blue[i]);
    }

    fclose(fp);
};
//==============================================================================

void writeTerminal()
{
    printf("a = %5.2lf\n", a);
    printf("b = %5.2lf\n", b);
    printf("c = %5.2lf\n", c);
    printf("d = %5.2lf\n", d);

    printf("\n");
    printf("countPointInterval = %d\n", countPointInterval);
    printf("nodeCount = %d\n", nodeCount);

    printf("\n");
    for (int i = 0; i < countPointInterval; i++)
        {printf("%3.2lf  ", pointInterval[i]);}
    printf("\n");

    printf("\n");
    for (int i = 0; i < nodeCount; i++)
    {
        printf("nodeX[%d] = %5.1lf  ", i, nodeX[i]);
        printf("nodeY[%d] = %5.1lf  ", i, nodeY[i]);
        printf("nodeZ[%d] = %5.1lf\n", i, nodeZ[i]);
    }
};
//==============================================================================

void ftrash (FILE *fp, int n)
{
    char trash[500];
    for (int i = 0; i < n; i++)
        {fscanf(fp, "%s", trash);}
};
//==============================================================================