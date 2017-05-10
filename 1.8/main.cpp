/*
 Решает систему линейных уравнений с помощью
 алгоритма гауса-жардана с выбором глааного элемента.
*/
#include <stdio.h>
#include <math.h>
//-----------------------------------------------------------------------------
#define swap(a,b) a-=b; b+=a; a=b-a;
//=============================================================================
void ftrash (FILE *fp, int n);
void fileRead();
void writeMatrix(double *x);
void writeAnswer();
void writeFile();
void answerCalculation();
void faultCalculation();

//=============================================================================
int N; //размерность матрицы.
double *matrix; //одномерный массив для матрицы.
double *b;
double *x;
double *fault;
bool answer = true;// имеет ли решения СЛAУ

//=============================================================================
int main()
{
      fileRead();
//-----------------------------------------------------------------------------
      x = new double[N];
//-----------------------------------------------------------------------------
      writeMatrix(matrix);
//-----------------------------------------------------------------------------
      //Первый проход с верху в низ
      for (int i = 0; i < N-1; i++)
      {
            int indexMaxLine = i;

            //нахождение max a_ii
            for (int j = i+1; j < N; j++)
                        if (fabs(matrix[j*N + i]) > fabs(matrix[indexMaxLine * N + i]))
                              {indexMaxLine = j;}

            if (indexMaxLine != i)
            {
                  for (int j = i; j < N; j++)
                        {swap(matrix[i*N + j],   matrix[indexMaxLine * N  +  j]);}
                  swap(b[i],  b[indexMaxLine]);
            }
            else if (matrix[i*indexMaxLine + i] == 0) {continue;}
//--------------------------------------------
            //складывает i строку с последующими за ней умножив i строку на cof
            for (int j = i+1; j < N; j++)
            {
                  double cof = -matrix[j*N + i]/matrix[i*N + i];

                  for (int k = i; k < N; k++)
                        {matrix[j*N + k] += cof*matrix[i*N + k];}

                  b[j] += cof*b[i];
            }
      }
//--------------------------------------------
      writeMatrix(matrix);
//--------------------------------------------
      //второй проход с низу в верх
      for (int i = N-1; i >= 0; i--)
      {
            if (matrix[i*N + i] == 0)
                  {answer = false; break;}

            for (int j = i-1; j >= 0; j--)//for (int j = i; j--;)
            {
                  double cof = -matrix[j*N + i]/matrix[i*N + i];

                  for (int k = i; k < N; k++)
                        {matrix[j*N + k] += cof*matrix[i*N + k];}

                  b[j] += cof*b[i];
            }
      }
//-----------------------------------------------------------------------------
      writeMatrix(matrix);
//-----------------------------------------------------------------------------
      if (answer)
      {
            answerCalculation();
//-----------------------------------------------------------------------------
            faultCalculation();
//-----------------------------------------------------------------------------
            writeAnswer();
      }
      else printf("Вырожденная матрица\n");
//-----------------------------------------------------------------------------
      writeFile();
};
//=============================================================================

void answerCalculation()
{
      for (int i = 0; i < N; i++)
            {x[i] = b[i]/matrix[i*N + i];}
};
//=============================================================================

void faultCalculation()
{
      FILE *fp;
      fp = fopen ("matrix.txt", "r");
//--------------------------------------------
      ftrash (fp, 5);
      for (int i = 0; i < N*N; i++)
            {fscanf(fp, "%lf", &matrix[i]);}
//--------------------------------------------
      ftrash (fp, 1);
      for (int i = 0; i < N; i++)
            {fscanf(fp, "%lf", &b[i]);}
//--------------------------------------------
      fclose(fp);
//-----------------------------------------------------------------------------
      fault = new double[N];

      for (int i = 0; i < N; i++)
      {
            double sum = 0;

            for (int j = 0; j < N; j++)
                  {sum += x[j]*matrix[i*N + j];}

            fault[i] = sum - b[i];
      }
};
//=============================================================================

void writeFile()
{
      FILE *fp;
      fp = fopen ("answer.txt", "w");
//-----------------------------------------------------------------------------
      fprintf(fp, "N = %d \n", N);
//--------------------------------------------
      for (int i = 0; i < N; i++)
      {
            for (int j = 0; j < N; j++)
                  {fprintf(fp, "%4.2lf  ", matrix[i*N+j]);}

            fprintf(fp, "%4.2lf \n", b[i]);
      }
      fprintf(fp, "\n");
//--------------------------------------------
      if (answer)
      {
            for (int i = 0; i < N; i++)
                  {fprintf(fp, "x[%d] = %.45lf \n", i, x[i]);}
//--------------------------------------------
             for (int i = 0; i < N; i++)
                   {fprintf(fp, "fault[%d] = %.45lf \n", i, fault[i]);}
      }
      else fprintf(fp, "Вырожденная матрица.\n");
//-----------------------------------------------------------------------------
      fclose(fp);
};
//=============================================================================

void writeMatrix(double *array)
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
//=============================================================================

void writeAnswer()
{
      for (int i = 0; i < N; i++)
            {printf("x[%d] = %.40lf \n", i, x[i]);}
//--------------------------------------------
      for (int i = 0; i < N; i++)
            {printf("fault[%d] = %.40lf \n", i, fault[i]);}
};
//=============================================================================

void fileRead()
{
      FILE *fp;
      fp = fopen ("matrix.txt", "r");
//-----------------------------------------------------------------------------
      ftrash (fp, 3);
      fscanf(fp, "%d", &N);
//--------------------------------------------
      matrix = new double[N*N];
      b = new double[N];
//--------------------------------------------
      ftrash (fp, 1);
      for (int i = 0; i < N*N; i++)
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