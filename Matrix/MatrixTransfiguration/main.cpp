#include <stdio.h>
#include <math.h>
//=============================================================================
void kfMultiOnStrSumStrMatrix(double *matrix, int N, int M, int i, int j, double multi);
void kfMultiStrMatrix(double *matrix, int N, int M, int i, double multi);
void swapStrMatrix(double *matrix, int N, int M, int i, int j);
void swapColumnMatrix(double *matrix, int N, int M, int i, int j);
void operationBack();

void ftrash (FILE *fp, int n);
void fileRead();
void fileWrite();
void writeMatrix(double *x);
void writefileMemoryStep();
//=============================================================================

int N; //размерность матрицы.
int M; //размерность матрицы.
double *matrix; //одномерный массив для матрицы.
double *b;

double memoryOperation[1000];
int countOperation;
int countAction;
//=============================================================================

int main()
{
      fileRead();
//-----------------------------------------------------------------------------
      double multi;
      int numberTask;
      int i, j;

      countOperation = 1;
      countAction = 0;

      while(true)
      {
            writeMatrix(matrix);

            printf(" 1. Multi\n");
            printf(" 2. Multi string on number\n");
            printf(" 3. Swap string\n");
            printf(" 4. Swap column\n");
            printf(" 5. Operation back\n");
            printf(" 6. Exit and save : ");

            scanf("%d", &numberTask);
            printf("\n");

            memoryOperation[countOperation] = numberTask;
            countOperation++;
            countAction++;

            if (numberTask == 1)
            {

                  printf("multi = ");
                  scanf("%lf", &multi);

                  memoryOperation[countOperation] = multi;
                  countOperation++;

                  printf("iStr = ");
                  scanf("%d", &i);

                  memoryOperation[countOperation] = i;
                  countOperation++;

                  printf("jStr = ");
                  scanf("%d", &j);

                  memoryOperation[countOperation] = j;
                  countOperation++;

                  kfMultiOnStrSumStrMatrix(matrix, N, M, i, j, multi);
                  continue;
            }

            if (numberTask == 2)
            {

                  printf("multi = ");
                  scanf("%lf", &multi);

                  memoryOperation[countOperation] = multi;
                  countOperation++;

                  printf("str = ");
                  scanf("%d", &i);

                  memoryOperation[countOperation] = i;
                  countOperation++;

                  kfMultiStrMatrix(matrix, N, M, i, multi);
                  continue;
            }

            if (numberTask == 3)
            {

                  printf("iStr = ");
                  scanf("%d", &i);

                  memoryOperation[countOperation] = i;
                  countOperation++;

                  printf("jStr = ");
                  scanf("%d", &j);

                  memoryOperation[countOperation] = j;
                  countOperation++;

                  swapStrMatrix(matrix, N, M, i, j);
                  continue;
            }

            if (numberTask == 4)
            {
                  printf("iStr = ");
                  scanf("%d", &i);

                  memoryOperation[countOperation] = i;
                  countOperation++;

                  printf("jStr = ");
                  scanf("%d", &j);

                  memoryOperation[countOperation] = j;
                  countOperation++;

                  swapColumnMatrix(matrix, N, M, i, j);
                  continue;
            }

            if (numberTask == 5)
            {
                  operationBack();
            }

            if (numberTask == 6)
                  {break;}
      }
//-----------------------------------------------------------------------------
      memoryOperation[0] = countAction;
      writefileMemoryStep();
      fileWrite();
};
//=============================================================================

void operationBack()
{
      FILE *fp;
      fp = fopen ("matrix.txt", "r");
//-----------------------------------------------------------------------------
      ftrash (fp, 6);
      for (int i = 0; i < N*M; i++)
            {fscanf(fp, "%lf", &matrix[i]);}

      ftrash (fp, 1);
      for (int i = 0; i < N; i++)
            {fscanf(fp, "%lf", &b[i]);}
//-----------------------------------------------------------------------------
      fclose(fp);

      int count = 1;
      for (int k = 0; k < countAction-1; k++)
      {
            getchar();
            switch((int)memoryOperation[count])
            {
                  case 1:
                  {

                        int multi = memoryOperation[count+1];
                        int i = (int)memoryOperation[count+2];
                        int j = (int)memoryOperation[count+3];
                        kfMultiOnStrSumStrMatrix(matrix, N, M, i, j, multi);
                        count += 4;
                  }
                  break;
                  case 2:
                  {
                        int multi = memoryOperation[count+1];
                        int i = (int)memoryOperation[count+2];
                        kfMultiStrMatrix(matrix, N, M, i, multi);
                        count += 3;
                  }
                  break;
                  case 3:
                  {
                        int i = (int)memoryOperation[count+1];
                        int j = (int)memoryOperation[count+2];
                        swapStrMatrix(matrix, N, M, i, j);
                        count += 3;
                  }
                  break;
                  case 4:
                  {
                        int i = (int)memoryOperation[count+1];
                        int j = (int)memoryOperation[count+2];
                        swapColumnMatrix(matrix, N, M, i, j);
                        count += 3;
                  }
                  break;
            }
      }
      writeMatrix(matrix);
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

void writefileMemoryStep()
{
      FILE *fp;
      fp = fopen ("memoryOperation.txt", "w");
//-----------------------------------------------------------------------------
      for (int i = 0; i < countOperation; i++)
      {
            fprintf(fp, "%lf\n", memoryOperation[i]);
      }
//-----------------------------------------------------------------------------
      fclose(fp);

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
