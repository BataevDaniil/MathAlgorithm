/*
решение системы ленейных уравнений с помощью
интерации методом Якоби.
*/
#include <stdio.h>
#include <math.h>
#include "Graph.h"
//==============================================================================

double a, b, c, d;

int N;
double *matrix;
double *f;
double *x;

double eps;

#define maxInterac 50

double *valuePlot;
int countInterac;

//==============================================================================
#define sqr(x) (x)*(x)

void ftrash (FILE *fp, int n);

void readFile();
void writeFile();

void writeMatrix(double *array, double *f);
void writeArray(double *array);
void writeTermimal();

void drawPlot();
void zeydily(double *matrix, double *f, double *x);

//==============================================================================

int main()
{
      readFile();
//-----------------------------------------------------------------------------
      zeydily(matrix, f, x);

      drawPlot();

      writeTermimal();
//-----------------------------------------------------------------------------
      writeFile();
};
//==============================================================================
void drawPlot()
{
      a = 0;
      b = maxInterac;
      c = 0;
      d = 100;
//------------------------------------------------------------------------------
      SetColor(250,250,250);
      SetWindow(a,b,c,d);

      SetColor(0,0,0);
      xyLine(0,0,1,10);

      SetColor(0,255,0);
      SetPoint(0, valuePlot[0]);
      for (int i = 1; i < countInterac; i++)
      {
            Line(i, valuePlot[i]);
      }
//------------------------------------------------------------------------------
      CloseWindow();
};
//==============================================================================

void zeydily(double *matrix, double *f, double*x)
{
      double normal;
      countInterac = 0;
      valuePlot = new double[maxInterac];

      {
            double rk[N];
            for (int i = 0; i < N; i++)
            {
                  double sum = 0;
                  for (int j = 0; j < N; j++)
                  {
                        sum += matrix[i*N + j] * x[j];
                  }

                  rk[i] = sum - f[i];
            }

            {
                  double sum = 0;
                  for (int i = 0; i < N; i++)
                  {
                        sum += sqr(rk[i]);
                  }
                  normal = sqrt(sum);
            }
            valuePlot[0] = normal;
            countInterac++;
      }

      do
      {
            double x1[N];
            double rk[N];

            for (int i = 0; i < N; i++)
            {
                  double sum1 = 0;
                  for (int j = 0; j < i; j++)
                  {
                        sum1 += matrix[i*N + j] * x1[j];
                  }

                  double sum2 = 0;
                  for (int j = i+1; j < N; j++)
                  {
                        sum2 += matrix[i*N + j] * x[j];
                  }

                  x1[i] = (f[i] - sum1 - sum2) / matrix[i*N + i];
            }

            for (int i = 0; i < N; i++)
            {
                  double sum = 0;
                  for (int j = 0; j < N; j++)
                  {
                        sum += matrix[i*N + j] * x1[j];
                  }

                  rk[i] = sum - f[i];
            }

            {
                  double sum = 0;
                  for (int i = 0; i < N; i++)
                  {
                        sum += sqr(rk[i]);
                  }
                  normal = sqrt(sum);
            }

            for (int i = 0; i < N; i++)
            {
                  x[i] = x1[i];
            }

            if (countInterac < maxInterac)
            {
                  valuePlot[countInterac] = normal;
            }
            countInterac++;
      }
      while(normal > eps);
      printf("countInterac = %d \n", countInterac);
};
//==============================================================================

void writeTermimal()
{
      writeMatrix(matrix, f);
      printf("vec x\n");
      writeArray(x);
      printf("eps = %lf\n", eps);
};
//==============================================================================

void writeArray(double *array)
{
      for (int i = 0; i < N; i++)
            printf("arr[%d] = %lf\n", i, array[i]);

      printf("\n");
};
//==============================================================================

void readFile()
{
      FILE *fp;
      fp = fopen ("matrix.txt", "r");
//-----------------------------------------------------------------------------
      ftrash(fp, 2);
      fscanf(fp, "%d", &N);

      matrix = new double[N*N];
      f = new double[N];
      x = new double[N];

      ftrash(fp, 1);
      for (int i = 0; i < N*N; i++)
            {fscanf(fp, "%lf", &matrix[i]);}

      ftrash(fp, 1);
      for (int i = 0; i < N; i++)
            {fscanf(fp, "%lf", &f[i]);}

      ftrash(fp, 1);
      for (int i = 0; i < N; i++)
            {fscanf(fp, "%lf", &x[i]);}

      ftrash(fp, 2);
      fscanf(fp, "%lf", &eps);
//-----------------------------------------------------------------------------
      fclose(fp);
};
//==============================================================================

void writeFile()
{
      FILE *fp;
      fp = fopen ("output.txt", "w");
//-----------------------------------------------------------------------------
      for (int i = 0; i < N; i++)
      {
            for (int j = 0; j < N; j++)
                  {fprintf(fp, "%4.2lf  ", matrix[i*N+j]);}

            fprintf(fp, "%4.2lf \n", f[i]);
      }
      fprintf(fp, "\n");

      for (int i = 0; i < N; i++)
            {fprintf(fp, "x[%d] = %20.20lf \n", i, x[i]);}
//-----------------------------------------------------------------------------
      fclose(fp);
};
//==============================================================================

void writeMatrix(double *array, double *f)
{
      printf("\n");
      printf("N = %d \n", N);

      for (int i = 0; i < N; i++)
      {
            for (int j = 0; j < N; j++)
                  {printf("%4.2lf  ", array[i*N+j]);}

            printf("   %lf \n", f[i]);
      }
      printf("\n");
};
//==============================================================================

void ftrash (FILE *fp, int n)
{
      char trash[500];
      for (int i = n; i--;)
            {fscanf(fp, "%s", trash);}
};
