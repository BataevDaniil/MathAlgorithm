#include <stdio.h>
#include "Graph.h"
#include <math.h>

//==============================================================================
double a, b, c, d;
int *red, *green, *blue;

int countPointInterval;
double *pointInterval;

double *nodeX, *nodeY, *nodeZ;
int nodeXCount;
int nodeYCount;
int nodeZCount;

double *ai, *bi, *ci, *di;

//==============================================================================
void ftrash( FILE *fp, int n );

void fileRead();
void writeTerminal();

void fillArrayXYZ();
double fTest( double x, double y );
double fCube(double x, int i);

void drawfTest();
void drawf();

void searchCoefficient();
void defiColorPoint( int i, double z );
int location(double x, double y);
//==============================================================================

int main()
{
    fileRead();
    fillArrayXYZ();
    writeTerminal();
//------------------------------------------------------------------------------
    drawfTest();

    searchCoefficient();

    drawf();
};
//==============================================================================

void drawf()
{

    ReadWindow("input.bmp", a,b,c,d);
//------------------------------------------------------------------------------
    double xStep = (b - a)/w;
    double yStep = (d - c)/h;

    int i = 0;
    for (int y = c; y < d; y += yStep)
    {
        for (int x = a; x < b; x += xStep)
        {
            defiColorPoint(0, i);
            i++;
        }
    }
/*
    //gride
    for (int i = 1; i < nodeYCount-1; i++)
    {
        for (int j = 0; j < w; j++)
        {
            R[j + location(a, nodeY[i])] = 0;
            G[j + location(a, nodeY[i])] = 0;
            B[j + location(a, nodeY[i])] = 0;
        }
    }

    for (int i = 1; i < nodeXCount-1; i++)
    {
        for (int j = 0; j < h; j++)
        {
            R[w*j + location(nodeX[i], c)] = 0;
            G[w*j + location(nodeX[i], c)] = 0;
            B[w*j + location(nodeX[i], c)] = 0;
        }
    }
*/
/*
    //line
    double xStep = (b - a)/w;
    double yStep = (d - c)/h;

    for (int i = 0; i < nodeYCount-1; i++)
    {
        for (int j = 0; j < nodeXCount-1; j++)
        {
            for (double y = nodeY[i]; y < nodeY[i+1]; y += yStep)
            {
                for (double x = nodeX[i]; x < nodeX[i+1]; x += xStep)
                {
                    if (location(fLine(i,j, y), y) == location(x,y))
                    {
                        R[location(x,y)] = 0;
                        G[location(x,y)] = 0;
                        B[location(x,y)] = 0;
                    }
                }
            }
        }
    }
*/
//------------------------------------------------------------------------------
    CloseWindow("f.bmp");
};
//==============================================================================

double fCube(double x, int i)
{
    double xi = nodeY[i];
    return ai[i]*pow(x - xi, 3) + bi[i]*pow(x - xi, 2) + ci[i]*(x - xi) + di[i];
};
//==============================================================================

int location(double x, double y)
{
    double xStep = (b - a)/w;
    double yStep = (d - c)/h;
    int i;

    i = (int)((x - a)/xStep);
    i += w*((int)((y - c)/yStep));

    //printf("xi = %d\n", (int)((x - a)/xStep));
    //printf("yi = %d\n", (int)((y - c)/yStep));
    //printf("i = %d\n", i);

    return i;
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

void searchCoefficient()
{
    di = new double[nodeXCount-1];
    for (int i = 0; i < nodeXcount; i++)
    {
        di = nodeYCount;
    }

    ci = new double[nodeXCount-1];
    ci[0] = (nodeZ[1] - nodeZ[0]) \ (nodeY[1] - nodeY[0]);
    ci[1] = (nodeZ[nodeXcount*nodeYCount-1] - nodeZ[nodeXcount*nodeYCount-2]) \ (nodeY[nodeYCount-1] - nodeY[nodeYCount-1]);
    for (int i = 1; i < nodeXCount-1; i++)
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

    ai = new double[nodeXCount-1];
    bi = new double[nodeXCount-1];
    for (int i = 0; i < nodeXCount-1; i++)
    {
        double h = nodeY[i+1] - nodeY[i];
        double f = di[i];
        double f1 = di[i+1];
        double df = ci[i];
        double df1 = ci[i+1];

        double a1 = pow(h,3);
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

void fillArrayXYZ()
{
    nodeX = new double[nodeXCount];
    nodeY = new double[nodeYCount];
    nodeZ = new double[nodeZCount];

    double xStep = (b - a)/(nodeXCount-1);
    double yStep = (d - c)/(nodeYCount-1);

    {
        double y = c;
        for (int i = 0; i < nodeYCount; i++)
        {
            nodeY[i] = y;
            y += yStep;
        }
    }

    {
        double x = a;
        for (int i = 0; i < nodeXCount; i++)
        {
            nodeX[i] = x;
            x += xStep;
        }
    }

    for (int i = 0; i < nodeYCount; i++)
        for (int j = 0; j < nodeXCount; j++)
            {nodeZ[i*nodeXCount + j] = fTest( nodeX[j], nodeY[i] );}
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
    //return x + y;

    #define sqr(x) (x)*(x)
    return(x*x+2*sqr(3./5*pow(x*x,1./3)-y)-1);

    //return x*x + y;
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
    fscanf(fp, "%d", &nodeXCount);

    ftrash (fp, 1);
    fscanf(fp, "%d", &nodeYCount);

    nodeZCount = nodeYCount * nodeXCount;

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
    printf("nodeXCount = %d\n", nodeXCount);
    printf("nodeYCount = %d\n", nodeYCount);
    printf("nodeZCount = %d\n", nodeZCount);

    printf("\n");
    for (int i = 0; i < countPointInterval; i++)
        {printf("%3.2lf  ", pointInterval[i]);}
    printf("\n");

    printf("\n");
    for (int i = 0; i < nodeYCount; i++)
    {
        for (int j = 0; j < nodeXCount; j++)
        {
            printf("nodeY[%d] = %5.1lf  ", i, nodeY[i]);
            printf("nodeX[%d] = %5.1lf  ", j, nodeX[j]);
            printf("nodeZ[%d][%d] = %5.1lf\n", i, j, nodeZ[i*nodeXCount + j]);
        }
        printf("\n");
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