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
double *aiTemp, *biTemp, *ciTemp, *diTemp;

//==============================================================================
void ftrash( FILE *fp, int n );
void grideInNodeXY();

void fileRead();
void writeTerminal();

void fillArrayXYZ();
double fTest( double x, double y );

void drawfTest();
void drawf();

void coefficientMainf();
void coefficientTempMainf(int j, double y);
double fTemp( int i, double x);

void fTestOneVar();
void fTempOneVar();

void defiColorPoint( int i, double z );
int location( double x, double y );
//==============================================================================

int main()
{
      fileRead();
      fillArrayXYZ();
//------------------------------------------------------------------------------
      drawfTest();

      coefficientMainf();

      fTestOneVar();

      drawf();

      //writeTerminal();
};
//==============================================================================
void fTempOneVar()
{
      SetColor(0,255,0);

      int delPlot = 100;

      for (int i = 0; i < nodeXCount-1; i++)
      {
            double xStep = (nodeX[i+1] - nodeX[i]) / delPlot;

            double x = nodeX[i];

            SetPoint(x, diTemp[i]);
            for (int j = 0; j < delPlot; j++)
            {
                  x += xStep;

                  double a1 = aiTemp[i]*pow(x - nodeX[i], 3);
                  double b1 = biTemp[i]*pow(x - nodeX[i], 2);
                  double c1 = ciTemp[i]*(x - nodeX[i]);
                  double d1 = diTemp[i];

                  double z = a1 + b1 + c1 + d1;

                  Line(x, z);
            }
      }
//------------------------------------------------------------------------------
      CloseWindow("fTempOneVar.bmp");
};

void fTestOneVar()
{
      SetColor(0,255,0);

      int delPlot = 10;

      #define numberPlot 1

      for (int i = 0; i < 0;i++)//nodeYCount-1; i++)
      {
            double yStep = (nodeY[i+1] - nodeY[i]) / delPlot;

            double y = nodeY[i];

            SetPoint(y, di[i]);
            for (int j = 0; j < delPlot; j++)
            {
                  y += yStep;

                  double a1 = ai[i]*pow(y - nodeY[i], 3);
                  double b1 = bi[i]*pow(y - nodeY[i], 2);
                  double c1 = ci[i]*(y - nodeY[i]);
                  double d1 = di[i];

                  double z = a1 + b1 + c1 + d1;

                  Line(y, z);
            }
      }
//------------------------------------------------------------------------------
      CloseWindow("fTestOneVar.bmp");
};
//==============================================================================

void drawf()
{

      ReadWindow("input.bmp", a,b,c,d);
//------------------------------------------------------------------------------
      double xStep = (b - a)/w;
      double yStep = (d - c)/h;

      aiTemp = new double[nodeXCount-1];
      biTemp = new double[nodeXCount-1];
      ciTemp = new double[nodeXCount-1];
      diTemp = new double[nodeXCount-1];

      int xY = 0;
      int i=0;
      int j;
      for (double y = c; y < d; y+=yStep)
      {
            if (y > nodeY[i+1])
                  {i++;}

            coefficientTempMainf(i, y);

            if (y == nodeY[1]-yStep*10)
                  {fTempOneVar();}

            j = 0;
            for (double x = a; x < b; x+=xStep)
            {
                  if (x > nodeX[j+1])
                        {j++;}

                  defiColorPoint( xY, fTemp( j, x ) );
                  xY++;
            }
      }

      grideInNodeXY();
//------------------------------------------------------------------------------
      CloseWindow("f.bmp");
};
//==============================================================================

void coefficientTempMainf(int j, double y)
{
      double nodeZTemp[nodeXCount];
      double df[nodeXCount];

      for (int i = 0; i < nodeXCount; i++)
      {
            double a = ai[i*(nodeYCount-1) + j];
            double b = bi[i*(nodeYCount-1) + j];
            double c = ci[i*(nodeYCount-1) + j];
            double d = di[i*(nodeYCount-1) + j];

            nodeZTemp[i] = a*pow(y - nodeY[j], 3) + b*sqr(y - nodeY[j]) + c*(y - nodeY[j]) + d;
      }

      {
            double deltaZ = nodeZTemp[1] - nodeZTemp[0];
            double deltaX = nodeX[1] - nodeX[0];

            df[0] = deltaZ / deltaX;
      }

      {
            double deltaZ = nodeZTemp[nodeXCount-1] - nodeZTemp[nodeXCount-2];
            double deltaX = nodeX[nodeXCount - 1] - nodeX[nodeXCount - 2];

            df[nodeXCount-1] = deltaZ / deltaX;
      }

      for (int i = 1; i < nodeXCount-1; i++)
      {
            double f2 = nodeZTemp[i+1];
            double f1 = nodeZTemp[i];
            double f0 = nodeZTemp[i-1];

            if ((f1 > f0 && f1 > f2) || (f1 < f0 && f1 < f2))
            {
                  df[i] = 0;
            }
            else
            {
                  double y1 = nodeX[i+1];
                  double y0 = nodeX[i-1];

                  df[i] = (f2-f0) / (y1-y0);
            }
      }

      for (int i = 0; i < nodeXCount-1; i++)
      {
            double h = nodeX[i+1] - nodeX[i];

            double f = nodeZTemp[i];
            double f1 = nodeZTemp[i+1];

            double df0 = df[i];
            double df1 = df[i+1];

            double a1 = pow(h,3);
            double a2 = sqr(h);
            double a3 = 3*sqr(h);
            double a4 = 2*h;
            double b1 = f1 - df0*h - f;
            double b2 = df1 - df0;

            biTemp[i] = (b2*a1 - b1*a3) / (a4*a1 - a3*a2);
            aiTemp[i] = (b1 - a2*biTemp[i]) / a1;
            ciTemp[i] = df0;
            diTemp[i] = f;
      }
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

double fTemp( int i, double x )
{
      double a = aiTemp[i]*pow(x - nodeX[i], 3);
      double b = biTemp[i]*sqr(x - nodeX[i]);
      double c = ciTemp[i]*(x - nodeX[i]);
      double d = diTemp[i];

      double z =  a + b + c + d;

      return z;
};
//==============================================================================

void coefficientMainf()
{
      ai = new double[(nodeYCount-1)*nodeXCount];
      bi = new double[(nodeYCount-1)*nodeXCount];
      ci = new double[(nodeYCount-1)*nodeXCount];
      di = new double[(nodeYCount-1)*nodeXCount];

      double df[nodeYCount*nodeXCount];

      for (int i = 0; i < nodeXCount; i++)
      {
            {
                  double deltaZ = nodeZ[i + nodeXCount] - nodeZ[i];
                  double deltaY = nodeY[1] - nodeY[0];

                  df[i*nodeYCount] = deltaZ / deltaY;
            }

            {
                  double deltaZ = nodeZ[i + nodeXCount*(nodeYCount - 1)] - nodeZ[i + nodeXCount*(nodeYCount - 2)];
                  double deltaY = nodeY[nodeYCount - 1] - nodeY[nodeYCount - 2];

                  df[(i+1)*nodeYCount-1] = deltaZ / deltaY;
            }

            for (int j = 1; j < nodeYCount-1; j++)
            {
                  double f2 = nodeZ[i + (j+1)*nodeXCount];
                  double f1 = nodeZ[i + j*nodeXCount];
                  double f0 = nodeZ[i + (j-1)*nodeXCount];

                  if ((f1 > f0 && f1 > f2) || (f1 < f0 && f1 < f2))
                  {
                        df[i*nodeYCount + j] = 0;
                  }
                  else
                  {
                        double y1 = nodeY[j+1];
                        double y0 = nodeY[j-1];

                        df[i*nodeYCount + j] = (f2-f0) / (y1-y0);
                  }
            }
      }

      for (int i = 0; i < nodeXCount; i++)
      {
            for (int j = 0; j < nodeYCount-1; j++)
            {
                  double h = nodeY[j+1] - nodeY[j];

                  double f = nodeZ[i + j*nodeXCount];
                  double f1 = nodeZ[i + (j+1)*nodeXCount];

                  double df0 = df[i*nodeYCount + j];
                  double df1 = df[i*nodeYCount + j+1];

                  double a1 = pow(h,3);
                  double a2 = sqr(h);
                  double a3 = 3*sqr(h);
                  double a4 = 2*h;
                  double b1 = f1 - df0*h - f;
                  double b2 = df1 - df0;

                  bi[i*(nodeYCount-1) + j] = (b2*a1 - b1*a3) / (a4*a1 - a3*a2);
                  ai[i*(nodeYCount-1) + j] = (b1 - a2*bi[i*(nodeYCount-1) + j]) / a1;
                  ci[i*(nodeYCount-1) + j] = df0;
                  di[i*(nodeYCount-1) + j] = f;
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

      //grideInNodeXY();
//------------------------------------------------------------------------------
      CloseWindow("fTest.bmp");

};
//==============================================================================

double fTest(double x, double y)
{
      //return x + y;

      #define sqr(x) (x)*(x)
      return (x*x+2*sqr(3./5*pow(x*x,1./3)-y)-1);

      //return x + y*y;
      //return y*y;
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
      for (int i = 0; i < nodeXCount; i++)
      {
            for (int j = 0; j < nodeYCount; j++)
            {
                  printf("ai = %5.2lf  ", ai[i*nodeYCount + j]);
                  printf("bi = %5.2lf  ", bi[i*nodeYCount + j]);
                  printf("ci = %5.2lf  ", ci[i*nodeYCount + j]);
                  printf("di = %5.2lf  ", di[i*nodeYCount + j]);

                  printf("\n");
            }
      }
*/

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

void grideInNodeXY()
{
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
};
//==============================================================================

void ftrash (FILE *fp, int n)
{
      char trash[500];
      for (int i = 0; i < n; i++)
            {fscanf(fp, "%s", trash);}
};
//==============================================================================