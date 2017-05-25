#include <stdio.h>
#include <math.h>
//=============================================================================
void kfMultiOnStrSumStrMatrix(double *matrix, int N, int M, int i, int j, double multi);
void kfMultiStrMatrix(double *matrix, int N, int M, int i, double multi);
void swapStrMatrix(double *matrix, int N, int M, int i, int j);
void swapColumnMatrix(double *matrix, int N, int M, int i, int j);

void ftrash (FILE *fp, int n);
void fileRead();
void fileWrite();
void writeMatrix(double *x);
//=============================================================================

int N; //размерность матрицы.
int M; //размерность матрицы.
double *matrix; //одномерный массив для матрицы.
double *b;
//=============================================================================

int main()
{
      fileRead();
//-----------------------------------------------------------------------------
      double multi;
      int numberTast;
      int i, j;

      while(true)
      {
            writeMatrix(matrix);

            printf(" 1. Multi\n");
            printf(" 2. Multi string on number\n");
            printf(" 3. Swap string\n");
            printf(" 4. Swap column\n");
            printf(" 5. Exit and save : ");

            scanf("%d", &numberTast);
            printf("\n");

            if (numberTast == 1)
            {

                  printf("multi = ");
                  scanf("%lf", &multi);

                  printf("iStr = ");
                  scanf("%d", &i);

                  printf("jStr = ");
                  scanf("%d", &j);

                  kfMultiOnStrSumStrMatrix(matrix, N, M, i, j, multi);
                  continue;
            }

            if (numberTast == 2)
            {

                  printf("multi = ");
                  scanf("%lf", &multi);

                  printf("str = ");
                  scanf("%d", &i);

                  kfMultiStrMatrix(matrix, N, M, i, multi);
                  continue;
            }

            if (numberTast == 3)
            {

                  printf("iStr = ");
                  scanf("%d", &i);

                  printf("jStr = ");
                  scanf("%d", &j);

                  swapStrMatrix(matrix, N, M, i, j);
                  continue;
            }

            if (numberTast == 4)
            {
                  printf("iStr = ");
                  scanf("%d", &i);

                  printf("jStr = ");
                  scanf("%d", &j);

                  swapColumnMatrix(matrix, N, M, i, j);
                  continue;
            }

            if (numberTast == 5)
                  {break;}
      }
//-----------------------------------------------------------------------------
      fileWrite();
};
//=============================================================================

void swapColumnMatrix(double *matrix, int N, int M, int i, int j)
{
      for (int k = 0; k < M; k++)
      {
            double tmp;
            tmp = matrix[k*M + i-1];
            matrix[k*M + i-1] = matrix[k*M + j-1];
            matrix[k*M + j-1] = tmp;
      }
};
//=============================================================================

void swapStrMatrix(double *matrix, int N, int M, int i, int j)
{
      for (int k = 0; k < M; k++)
      {
            double tmp;
            tmp = matrix[(i-1)*M + k];
            matrix[(i-1)*M + k] = matrix[(j-1)*M + k];
            matrix[(j-1)*M + k] = tmp;
      }

      double tmp;
      tmp = b[i-1];
      b[i-1] = b[j-1];
      b[j-1] = tmp;
};
//=============================================================================

void kfMultiStrMatrix(double *matrix, int N, int M, int i, double multi)
{
      for (int k = 0; k < M; k++)
      {
            matrix[(i-1)*M + k] *= multi;
      }
      b[(i-1)] *= multi;
};
//=============================================================================

void kfMultiOnStrSumStrMatrix(double *matrix, int N, int M, int i, int j, double multi)
{
      for (int k = 0; k < M; k++)
      {
            matrix[(j-1)*M + k] = matrix[(i-1)*M + k]*multi + matrix[(j-1)*M + k];
      }
      b[j-1] += b[i-1]*multi;
};
//=============================================================================

void fileWrite()
{
      FILE *fp;
      fp = fopen ("answer.txt", "w");
//-----------------------------------------------------------------------------
      fprintf(fp, "Размерность_СЛАУ_(<=10)\n");
      fprintf(fp, "N= %d\n", N);
      fprintf(fp, "M= %d\n", M);
//--------------------------------------------
      fprintf(fp, "\n");
      fprintf(fp, "Значение_матрицы_СЛАУ(double):\n");
//--------------------------------------------
      for (int i = 0; i < N; i++)
      {
            for (int j = 0; j < M; j++)
                  {fprintf(fp, "%6.2lf  ", matrix[i*M+j]);}

            fprintf(fp, "\n");
      }
//--------------------------------------------
      fprintf(fp, "\n");
      fprintf(fp, "Значениее_правой_части_(double):\n");
//--------------------------------------------
      for (int i = 0; i < N; i++)
            {fprintf(fp, "%6.2lf ", b[i]);}
//-----------------------------------------------------------------------------
      fclose(fp);
};
//=============================================================================

void fileRead()
{
      FILE *fp;
      fp = fopen ("matrix.txt", "r");
//-----------------------------------------------------------------------------
      ftrash (fp, 2);
      fscanf(fp, "%d", &N);
//--------------------------------------------
      ftrash (fp, 1);
      fscanf(fp, "%d", &M);
//--------------------------------------------
      matrix = new double[N*M];
      b = new double[N];
//--------------------------------------------
      ftrash (fp, 1);
      for (int i = 0; i < N*M; i++)
            {fscanf(fp, "%lf", &matrix[i]);}
//--------------------------------------------
      ftrash (fp, 1);
      for (int i = 0; i < N; i++)
            {fscanf(fp, "%lf", &b[i]);}
//-----------------------------------------------------------------------------
      fclose(fp);
};
//=============================================================================

void ftrash (FILE *fp, int n)
{
      char trash[500];
      for (int i = n; i--;)
            {fscanf(fp, "%s", trash);}
};
//=============================================================================

void writeMatrix(double *array)
{
      printf("\n");
      printf("N = %d M = %d\n", N, M);

      for (int i = 0; i < N; i++)
      {
            for (int j = 0; j < M; j++)
                  {printf("%6.2lf ", array[i*M+j]);}

            printf(" | %6.2lf\n", b[i]);
      }
      printf("\n");
};
//=============================================================================
