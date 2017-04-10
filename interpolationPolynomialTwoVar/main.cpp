﻿/*
    double xStep = (b - a)/w;
    double yStep = (d - c)/h;

    double xy = 0;
    for (int i = 0; i < nodeYCount-1; i++)
    {
        if (i != 0)
            {xy += h*(d - c)/(nodeY[i] - nodeY[i-1]);}

        for (int j = 0; j < nodeXCount-1; j++)
        {
            if (j != 0)
                {xy += w*(b - a)/(nodeX[i] - nodeX[i-1]);}

            kfPlane(i, j, 0);
            for (double y = nodeY[i]; y < nodeY[i+1]; y += yStep)
            {
                xy += w;
                for (double x = fLine(i, j, y); x > nodeX[j]; x -= xStep)
                    {defiColorPoint( xy, fPlane(x, y) ); xy--;}
            }

            if (j != 0)
                {xy += w*(b - a)/(nodeX[i+1] - nodeX[i]);}

            kfPlane(i, j, 1);
            for (double y = nodeY[i]; y < nodeY[i+1]; y += yStep)
            {
                xy += w;
                for (double x = fLine(i, j, y); x < nodeX[j+1]; x += xStep)
                    {defiColorPoint( xy, fPlane(x, y) ); xy++;}
            }
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
int nodeXCount;
int nodeYCount;
int nodeZCount;

double aPlane, bPlane, dPlane;
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
    //writeTerminal();
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
/*
    int i = 0;
    for (double y = c; y < d; y += yStep)
    {
        for (double x = a; x < b; x += xStep)
        {
            defiColorPoint(i, fPlane(x,y));
            i++;
        }
    }
*/

//------------------------------------------------------------------------------
    CloseWindow("f.bmp");
};
//==============================================================================

void kfPlane(int i, int j, bool Yn)
{
    //z = 0*x + 1*y + 1;
    double x1 = nodeX[j];
    double y1 = nodeY[i+1];
    double z1 = nodeZ[(i+1)*nodeXCount + j];

    double x2 = nodeX[j];
    double y2 = nodeY[i];
    double z2 = nodeZ[i*nodeXCount + j];

    if (Yn)
    {
        x2 = nodeX[j+1];
        y2 = nodeY[i+1];
        z2 = nodeZ[(i+1)*nodeXCount + j+1];
    }

    double x3 = nodeX[j+1];
    double y3 = nodeY[i];
    double z3 = nodeZ[i*nodeXCount + j+1];

    double a2 = x1;
    double a3 = y1;
    double a5 = x2 - x1;
    double a6 = y2 - y1;
    double a8 = x3 - x1;
    double a9 = y3 - y1;
    double b1 = z1;
    double b2 = z2 - z1;
    double b3 = z3 - z1;

/*
    //решение системы Гаусом
    bPlane = (a5*b3 - b2*a8) / (a9*a5 - a8*a6);
    aPlane = (b2 - a6*bPlane) / a5;
    dPlane = b1 - a3*bPlane - a2*aPlane;
*/
/*
    dPlane = ((x2-x1)*(z3-z1) - (z2-z1)*(x3-x1)) / ((x2-x1)*(y3-y1) - (y2-y1)*(x3-x1));
    bPlane = (z2 - z1 - (y2 - y1)*dPlane) / (x2 - x1);
    aPlane = z1 - y1*dPlane - x1*bPlane;
*/
    //решением системы Крамером
    double delta = a5*a9 - a6*a8;

    //double delta1 = b1*(a5*a9 - a6*a8) + a2*(a6*b3 - b2*a9) + a3*(b2*a8 - a5*b3);

    double delta2 = b2*a9 - a6*b3;

    double delta3 = a5*b3 - b2*a8;

    double delta1 = b1*delta - a2*delta2 - a3*delta3;

/*
    printf("delta  = %lf\n", delta);
    printf("delta1 = %lf\n", delta1);
    printf("delta2 = %lf\n", delta2);
    printf("delta3 = %lf\n", delta3);
    printf("\n");
*/

    if (delta != 0)
    {
        if (delta1 == 0)
            {dPlane = 0;}
        else dPlane = delta1 / delta;

        if (delta2 == 0)
            {aPlane = 0;}
        else aPlane = delta2 / delta;

        if (delta3 == 0)
            {bPlane = 0;}
        else bPlane = delta3 / delta;
    }
    else printf("Для плоскости решения нет.\n");

/*
    printf("aPlane = %lf\n", aPlane);
    printf("bPlane = %lf\n", bPlane);
    printf("dPlane = %lf\n", dPlane);
*/
};
//==============================================================================

double fPlane(double x, double y)
{
    return aPlane*x + bPlane*y + dPlane;
};
//==============================================================================

double fLine( int i, int j, double y )
{
    double x1 = nodeX[j+1];
    double y1 = nodeY[i];

    double x2 = nodeX[j];
    double y2 = nodeY[i+1];

    return (y - y1)*(x2 - x1)/(y2 - y1) + x1;
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
    nodeX = new double[nodeXCount];
    nodeY = new double[nodeYCount];
    nodeZ = new double[nodeZCount];

    double xStep = (b - a)/(nodeXCount-1);
    double yStep = (d - c)/(nodeYCount-1);

    double y = c;
    for (int i = 0; i < nodeYCount; i++)
    {
        nodeY[i] = y;
        y += yStep;
    }

    double x = a;
    for (int i = 0; i < nodeXCount; i++)
    {
        nodeX[i] = x;
        x += xStep;
    }

    for (int i = 0; i < nodeYCount; i++)
        for (int j = 0; j < nodeXCount; j++)
            {nodeZ[i*nodeYCount + j] = fTest( nodeX[j], nodeY[i] );}
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
    return 2*x + y + 0;

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
            printf("nodeZ[%d][%d] = %5.1lf\n", i, j, nodeZ[i*nodeYCount + j]);
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