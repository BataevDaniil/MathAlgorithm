/*
Решение системы ленейных уравнений с помощью
интерационного метода наискорейшего спуска.
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
double Normal(double*rk);
void vectorFault(double *matrix, double *f,double *x, double *rk);
void multiMatrixVector(double *matrix, double *rk, double vec);
double multiScalyrVector(double *vec1, double *vec2);
void multiVecOnNumber(double *vec1, double number);

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

      int numInterac;
      if (countInterac > maxInterac)
            numInterac = maxInterac;
      else numInterac = countInterac;

      for (int i = 1; i <= numInterac; i++)
      {
            Line(i, valuePlot[i]);
      }
//------------------------------------------------------------------------------
      CloseWindow();
};
//==============================================================================

double multiScalyrVector(double *vec1, double *vec2)
{
      double sum = 0;
      for (int i = 0; i < N; i++)
      {
            sum += vec1[i] * vec2[i];
      }

      return sum;
};
//==============================================================================
void multiVecOnNumber(double *vec, double number)
{
      for (int i = 0; i < N; i++)
      {
            vec[i] *= number;
      }
};
//==============================================================================

void multiMatrixVector(double *matrix, double *rk, double *vec)
{
      for (int i = 0; i < N; i++)
      {
            double sum = 0;
            for (int j = 0; j < N; j++)
            {
                  sum += matrix[i*N + j] * rk[j];
            }
            vec[i] = sum;
      }
};
//==============================================================================

double Normal(double*rk)
{
      double sum = 0;
      for (int i = 0; i < N; i++)
      {
            sum += sqr(rk[i]);
      }
      return sqrt(sum);
};
//==============================================================================

void vectorFault(double *matrix, double *f,double *x, double *rk)
{
      for (int i = 0; i < N; i++)
      {
            double sum = 0;
            for (int j = 0; j < N; j++)
            {
                  sum += matrix[i*N + j] * x[j];
            }

            rk[i] = sum - f[i];
      }
};
//==============================================================================

void zeydily(double *matrix, double *f, double*x)
{
      double normal;
      double x1[N];
      double rk[N];

      countInterac = 0;
      valuePlot = new double[maxInterac+1];

      {
            vectorFault(matrix, f, x, rk);
            valuePlot[0] = Normal(rk);
      }

      do
      {

            double Ax[N];
            double Ark[N];
            multiMatrixVector(matrix, x, Ax);
            multiMatrixVector(matrix, rk, Ark);

            //writeArray(Ark);

            double scalyr1 = multiScalyrVector(rk, rk);
            double scalyr2 = multiScalyrVector(rk, Ark);

            //printf("scalyr1 = %lf \n", scalyr1);
            //printf("scalyr2 = %lf \n", scalyr2);

            for (int i = 0; i < N; i++)
            {
                  x1[i] = (f[i] - Ax[i]) * scalyr1 / scalyr2 + x[i];
            }

            for (int i = 0; i < N; i++)
            {
                  x[i] = x1[i];
            }

            vectorFault(matrix, f, x, rk);
            normal = Normal(rk);

            //printf("vec rk \n");
            //writeArray(rk);

            if (countInterac < maxInterac)
            {
                  valuePlot[countInterac+1] = normal;
            }
            countInterac++;
            //getchar();
      }
      while(normal > eps);
};
//==============================================================================

void writeTermimal()
{
      writeMatrix(matrix, f);

      printf("vec x\n");
      writeArray(x);

      printf("eps = %lf\n", eps);

      printf("countInterac = %d \n", countInterac);
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

      fprintf(fp, "countInterac = %d\n", countInterac);
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
