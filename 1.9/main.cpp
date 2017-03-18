/*
решение системы ленейных уравнений с помощью
интерации методом Якоби.
*/
#include <stdio.h>
#include <math.h>
//==============================================================================
double *matrix;
double *b;
double *x;
double eps;
int N;
//==============================================================================
void readFile();
void writeFile();
void writeMatrix(double *array, double *b);
void writeArray(double *array);
void ftrash (FILE *fp, int n);
//==============================================================================

int main()
{
  readFile();
//-----------------------------------------------------------------------------
  writeMatrix(matrix, b);
  writeArray(x);
//-----------------------------------------------------------------------------
    //проверка на решабильность методом Якоби
  for (int i = 0; i < N; i++)
  {
    double sum = 0;

    for (int j = 0; j < N; j++)
    {
      if (i == j){continue;}
      sum +=matrix[i*N + j];
    }

    if (sum > matrix[i*N + i])
      {printf("С помощью метода Якоби решения нет.\n");}
  }

//решение
  double rk;
  double r[N];
  double x1[N];
  do{
    //находим x^(i+1)
    for (int i = 0; i < N; i++)
    {
      double sum = 0;

      for (int j = 0; j < N; j++)
      {
        if (j == i){continue;}
        sum += matrix[i*N * j] * x[j];
        printf("for [%d][%d]\n", i, j);
        printf("    matrtix = %lf\n", matrix[i*N * j]);
        printf("    x = %lf\n", x[4]);
        printf("    sum = %lf\n\n", sum);
      }

      x1[i] = (b[i] - sum)/matrix[i*N + i];
    }

    for (int i = 0; i < N; i++)
      {x[i] = x1[i];}

    //находим r^i
    for (int i = 0; i < N; i++)
    {
      double sum = 0;

      for (int j = 0; j < N; j++)
        {sum += matrix[i*N + j]*x1[j];}

      r[i] = sum - b[i];
    }

    //подсчет нормали
    rk = 0;
    for (int i = 0; i < N; i++)
      {rk += r[i]*r[i];}

    printf("rk = %lf\n", rk);
  }while (sqrt(rk) >= eps);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
  writeFile();
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
  b = new double[N];
  x = new double[N];
  ftrash(fp, 1);
  for (int i = 0; i < N*N; i++)
    {fscanf(fp, "%lf", &matrix[i]);}

  ftrash(fp, 1);
  for (int i = 0; i < N; i++)
    {fscanf(fp, "%lf", &b[i]);}

  ftrash(fp, 1);
  for (int i = 0; i < N; i++)
    {fscanf(fp, "%lf", &x[i]);}

  ftrash(fp, 1);
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

    fprintf(fp, "%4.2lf \n", b[i]);
  }
  fprintf(fp, "\n");

  for (int i = 0; i < N; i++)
    {fprintf(fp, "x[%d] = %20.20lf \n", i, x[i]);}
//-----------------------------------------------------------------------------
  fclose(fp);
};
//==============================================================================

void writeMatrix(double *array, double *b)
{
  printf("\n");
  printf("N = %d \n", N);

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
      {printf("%4.2lf  ", array[i*N+j]);}

    printf("   %lf \n", b[i]);
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