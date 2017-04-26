#include <stdio.h>
#include "Graph.h"
#include <math.h>

#define sqr(x) (x)*(x)
//==============================================================================
double a, b, c, d;
int *red, *green, *blue;

int countPointInterval;
double *pointInterval;

double *nodeX;
double *nodeY;
double *nodeZ;

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

void drawfTest();
void drawf();

void coefficientMainf();
double valueFunction( int i, int j, double x, double y );

void defiColorPoint( int i, double z );
int location( double x, double y );
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

      coefficientMainf();

      int i=0;
      int j;
      int xY=0;
      for (double y = c; y < d; y+=yStep)
      {
            if (y > nodeY[i+1])
                  {i++;}

            j=0;
            for (double x = a; x < b; x+=xStep)
            {
                  if (x > nodeX[j+1])
                        {j++;}

                  defiColorPoint( xY, valueFunction( i, j, x, y ) );
                  xY++;
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

double valueFunction(int i, int j, double x, double y)
{
      double zY0;
      {
            double a = ai[i*nodeYCount + j];
            double b = bi[i*nodeYCount + j];
            double c = ci[i*nodeYCount + j];
            double d = di[i*nodeYCount + j];

            zY0 = a*pow(y - nodeY[i], 3) + b*pow(y - nodeY[i], 2) + c*(y - nodeY[i]) + d;
      }

      double zY1;
      {
            double a = ai[i*nodeYCount + j+1];
            double b = bi[i*nodeYCount + j+1];
            double c = ci[i*nodeYCount + j+1];
            double d = di[i*nodeYCount + j+1];

            zY1 = a*pow(y - nodeY[i], 3) + b*pow(y - nodeY[i], 2) + c*(y - nodeY[i]) + d;
      }

      double z;
      {

            double h = nodeX[j+1] - nodeX[j];
            double f = zY0;
            double f1 = zY1;

            double df;
            double df1;

            {
                  double a = ai[i*nodeYCount + j+2];
                  double b = bi[i*nodeYCount + j+2];
                  double c = ci[i*nodeYCount + j+2];
                  double d = di[i*nodeYCount + j+2];


                  double f2 = a*pow(y - nodeY[i], 3) + b*pow(y - nodeY[i], 2) + c*(y - nodeY[i]) + d;
                  double f1 = zY1;
                  double f0 = zY0;

                  if ((f1 > f0 && f1 > f2) || (f1 < f0 && f1 < f2))
                  {
                        df1 = 0;
                  }
                  else{
                        double x1 = nodeX[j+2];
                        double x0 = nodeX[j];

                        df1 = (f2-f0) / (x1-x0);
                        }
            }

            double a1 = pow(h,3);
            double a2 = sqr(h);
            double a3 = 3*sqr(h);
            double a4 = 2*h;
            double b1 = f1 - df*h - f;
            double b2 = df1 - df;

            b = (b2*a1 - b1*a3) / (a4*a1 - a3*a2);
            a = (b1 - a2*b) / a1;
            d = zY0;

            z = a*pow(x - nodeX[i], 3) + b*pow(x - nodeX[i], 2) + c*(x - nodeX[i]) + d;
      }

      return z;
};
//==============================================================================

void coefficientMainf()
{
      ai = new double[nodeYCount*nodeXCount];
      bi = new double[nodeYCount*nodeXCount];
      ci = new double[nodeYCount*nodeXCount];
      di = new double[nodeYCount*nodeXCount];

      for (int i = 0; i < nodeXCount; i++)
      {
                  {
                        double hZ = nodeZ[nodeXCount + i] + nodeZ[i];
                        double hY = nodeY[1] - nodeY[0];

                        ci[i*nodeYCount] = hZ/hY;
                  }

                  {
                        double hZ = nodeZ[nodeXCount*nodeYCount - 1] - nodeZ[nodeXCount*nodeYCount - 2];
                        double hY = nodeY[nodeYCount - 1] - nodeY[nodeYCount - 2];

                        ci[(i+1)*nodeYCount - 1] = hZ/hY;
                  }

            for (int j = 0; j < nodeYCount; j++)
            {
                  double h = nodeY[j+1] - nodeY[j];
                  double f = nodeZ[i + j*nodeXCount];
                  double f1 = nodeZ[i + (j+1)*nodeXCount];

                  double df = ci[i*nodeYCount + j];
                  double df1;

                  {
                        double f2 = nodeZ[(j+2)*nodeXCount];
                        double f1 = nodeZ[(j+1)*nodeXCount];
                        double f0 = nodeZ[j*nodeXCount];

                        if ((f1 > f0 && f1 > f2) || (f1 < f0 && f1 < f2))
                        {
                              df1 = 0;
                              ci[i*nodeYCount + j+1] = 0;
                        }
                        else{
                              double y1 = nodeY[j+2];
                              double y0 = nodeY[j];

                              df1 = (f2-f0) / (y1-y0);
                              ci[i*nodeYCount + j+1] = df1;
                              }
                  }

                  double a1 = pow(h,3);
                  double a2 = sqr(h);
                  double a3 = 3*sqr(h);
                  double a4 = 2*h;
                  double b1 = f1 - df*h - f;
                  double b2 = df1 - df;

                  bi[i*nodeYCount + j] = (b2*a1 - b1*a3)/(a4*a1 - a3*a2);
                  ai[i*nodeYCount + j] = (b1 - a2*bi[i*nodeYCount + j])/a1;
                  di[i*nodeYCount + j] = nodeZ[i + j*nodeXCount];
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

/*
      for (int i = 0; i < countPointInterval; i++)
      {
            printf("red[%d] = %3d  ", i, red[i]);
            printf("green[%d] = %3d  ", i, green[i]);
            printf("blue[%d] = %3d\n", i, blue[i]);

            printf("\n");
      }
*/
};
//==============================================================================

void ftrash (FILE *fp, int n)
{
      char trash[500];
      for (int i = 0; i < n; i++)
            {fscanf(fp, "%s", trash);}
};
//==============================================================================