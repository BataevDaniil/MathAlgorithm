#include <stdio.h>
#include "Graph.h"
#include <math.h>

#define sqr(x) (x)*(x)
//==============================================================================
double a, b, c, d;

int autoSetColorIntervalYesNo;
int countPointInterval;
double *pointInterval;
int *red, *green, *blue;

double *nodeX;
double *nodeY;
double *nodeZ;

int nodeXCount;
int nodeYCount;
int nodeZCount;

double *ai, *bi, *ci, *di;
double *aiTemp, *biTemp, *ciTemp, *diTemp;

double distNodeXY;

//==============================================================================
void ftrash( FILE *fp, int n );
void grideInNodeXY();

void fileRead();
void readHeight();
void writeTerminal();
void autoSetColorInterval();

void fillNodeXYZ();

void drawMapGreenland();
void lineLevel();

void coefficientMainf();
void coefficientTempMainf( int j, double y );
double fTemp( int i, double x);

void definColorPixel( int i, double z );
int location( double x, double y );
//==============================================================================

int main()
{
      fileRead();
      readHeight();
      fillNodeXYZ();
//------------------------------------------------------------------------------
      autoSetColorInterval();

      a = 0;
      b = distNodeXY * (nodeXCount-1);
      c = 0;
      d = distNodeXY * (nodeYCount-1);

      drawMapGreenland();

      //writeTerminal();
};
//==============================================================================

void lineLevel()
{
      for (int i = 1; i < h; i++)
            for (int j = 1; j < w; j++)
                  if ((R[i*w + j-1] != R[i*w + j]) || (G[i*w + j-1] != G[i*w + j]) || (B[i*w + j-1] != B[i*w + j]) || (R[i*(w-1) + j] != R[i*w + j]) || (G[i*(w-1) + j] != G[i*w + j]) || (B[i*(w-1) + j] != B[i*w + j]))
                  {
                        R[i*w + j] = 255;
                        G[i*w + j] = 255;
                        B[i*w + j] = 255;
                  }
                  else R[i*w + j] = G[i*w + j] = B[i*w + j] = 0;
};
//==============================================================================

void drawMapGreenland()
{
      ReadWindow("input.bmp", a,b,c,d);

//------------------------------------------------------------------------------
      coefficientMainf();

      double a = 0;
      double b = distNodeXY * (nodeXCount-1);
      double c = 0;
      double d = distNodeXY * (nodeYCount-1);

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

            j = 0;
            for (double x = a; x < b; x+=xStep)
            {
                  if (x > nodeX[j+1])
                        {j++;}

                  definColorPixel( xY, fTemp( j, x ) );
                  xY++;
            }
      }

      //grideInNodeXY();
      //lineLevel();
//------------------------------------------------------------------------------

      CloseWindow("MapGreenland.bmp");
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

void definColorPixel(int i, double z)
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

void fillNodeXYZ()
{

      for (int i = 0; i < nodeXCount; i++)
      {
            nodeX[i] = distNodeXY* i;
      }

      for (int i = 0; i < nodeYCount; i++)
      {
            nodeY[i] = distNodeXY * i;
      }
};
//==============================================================================

void readHeight()
{
      FILE *fp;
      fp = fopen ("HightGreenland.dat", "r");

      for (int i = 0; i < nodeZCount; i++)
      {
            ftrash(fp, 2);
            fscanf(fp, "%lf", &nodeZ[i]);
      }

      fclose(fp);

};
//==============================================================================

void fileRead()
{
      FILE *fp;
      fp = fopen ("inputMapGreenland.txt", "r");

      ftrash (fp, 3);
      fscanf(fp, "%lf", &distNodeXY);

      ftrash (fp, 2);
      fscanf(fp, "%d", &nodeXCount);

      ftrash (fp, 1);
      fscanf(fp, "%d", &nodeYCount);

      ftrash (fp, 2);
      fscanf(fp, "%d", &autoSetColorIntervalYesNo);

      nodeZCount = nodeYCount * nodeXCount;

      nodeZ = new double[nodeZCount];
      nodeX = new double[nodeXCount];
      nodeY = new double[nodeYCount];

      if (autoSetColorIntervalYesNo == 0)
      {
            ftrash (fp, 2);
            fscanf(fp, "%d", &countPointInterval);

            pointInterval = new double[countPointInterval];

            red = new int[countPointInterval-1];
            green = new int[countPointInterval-1];
            blue = new int [countPointInterval-1];

            ftrash(fp, 1);
            for (int i = 0; i < countPointInterval; i++)
                  {fscanf(fp, "%lf", &pointInterval[i]);}

            ftrash(fp, 1);
            for (int i = 0; i < countPointInterval-1; i++)
            {
                  fscanf(fp, "%d", &red[i]);
                  fscanf(fp, "%d", &green[i]);
                  fscanf(fp, "%d", &blue[i]);
            }
      }

      fclose(fp);
};
//==============================================================================

void autoSetColorInterval()
{
      if (autoSetColorIntervalYesNo == 1)
      {
            double min = nodeZ[0];
            double max = nodeZ[0];
            for (int i = 1; i < nodeZCount; i++)
            {
                  if (min > nodeZ[i])
                        min = nodeZ[i];

                  if (max < nodeZ[i])
                        max = nodeZ[i];
            }

            //printf("min = %lf\n", min);
            //printf("max = %lf\n", max);

            countPointInterval = 256;
            double stepInterval = abs(max - min) / (countPointInterval - 1.);

            //printf("stepInterval = %lf\n", stepInterval);

            pointInterval = new double[countPointInterval];

            pointInterval[0] = min;
            for (int i = 1; i < countPointInterval; i++)
            {
                  pointInterval[i] = pointInterval[i-1] + stepInterval;
            }

            red = new int[countPointInterval-1];
            green = new int[countPointInterval-1];
            blue = new int [countPointInterval-1];

            for (int i = 0; i < countPointInterval-1; i++)
            {
                  red[i] = 0;
                  green[i] = i;
                  blue[i] = 0;
            }
      }
};
//==============================================================================

void writeTerminal()
{
      printf("\n");
      printf("countPointInterval = %d\n", countPointInterval);
      printf("nodeXCount = %d\n", nodeXCount);
      printf("nodeYCount = %d\n", nodeYCount);
      printf("nodeZCount = %d\n", nodeZCount);

      printf("\n");
      for (int i = 0; i < countPointInterval; i++)
            {printf("%3.2lf  ", pointInterval[i]);}
      printf("\n");

/*
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
*/

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

void ftrash (FILE *fp, int n)
{
      char trash[500];
      for (int i = 0; i < n; i++)
            {fscanf(fp, "%s", trash);}
};
//==============================================================================