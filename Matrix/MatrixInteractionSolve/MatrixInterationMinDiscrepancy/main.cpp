/*
решение системы ленейных уравнений с помощью
интерации методом Якоби.
*/
#include <stdio.h>
#include <math.h>
#include "Graph.h"
//==============================================================================
double *matrix;
double *b;
double *x;
double eps;
int N;
double a, y, c, d;
#define maxInterac 50
//==============================================================================
void readFile();
void writeFile();
void writeMatrix(double *array, double *b);
void writeArray(double *array);
void ftrash (FILE *fp, int n);
void runInterac(double *matrix, double *b, double*x);
double normal(double *matrix, double *b, double *x);
double intercParametr(double *matrix, double *b, double *x);
//==============================================================================

int main()
{
    readFile();
//-----------------------------------------------------------------------------
    a = 0;
    y = maxInterac;
    c = 0;
    d = 100;

    SetColor(250,250,250);
    SetWindow(a,y,c,d);

    SetColor(0,0,0);
    xyLine(a,0,1,10);

//-----------------------------------------------------------------------------
    double rk = normal(matrix, b, x);
//-----------------------------------------------------------------------------
    SetPoint(a, rk);
//-----------------------------------------------------------------------------
    writeMatrix(matrix, b);
    writeArray(x);
//-----------------------------------------------------------------------------
    //проверка на решабильность методом Якоби
    runInterac(matrix, b, x);//решение
//-----------------------------------------------------------------------------
    writeFile();
//-----------------------------------------------------------------------------
    CloseWindow();
};
//==============================================================================

double normal(double *matrix, double *b, double *x)
{

    double r[N];
    //находим r
    for (int i = 0; i < N; i++)
    {
        double sum = 0;

        for (int j = 0; j < N; j++)
            {sum += matrix[i*N + j]*x[j];}

        r[i] = sum - b[i];
    }

    //подсчет нормали
    double rk = 0;
    for (int i = 0; i < N; i++)
        {rk += r[i]*r[i];}
    rk = sqrt(rk);

    return rk;
}
//==============================================================================
double intercParametr(double *matrix, double *b, double *x)
{
    double rTop=0;
    double rDown=0;
    double r[N];
    //находим r
    for (int i = 0; i < N; i++)
    {
        double sum = 0;

        for (int j = 0; j < N; j++)
            {sum += matrix[i*N + j]*x[j];}

        r[i] = b[i] - sum ;
    }

    for (int i = 0; i < N; i++)
    {
        double sum = 0;
        for (int j = 0; j < N; j++)
        {
            sum += matrix[i*N + j] * r[j];
        }
        rTop += r[i]*sum;
    }

    for (int i = 0; i < N; i++)
    {
        double sum = 0;
        for (int j = 0; j < N; j++)
        {
            sum += matrix[i*N + j] * r[j];
        }
        rDown += sum*sum;
    }
    return rTop/rDown;
}

void runInterac(double *matrix, double *b, double*x)
{
    double rk;
    double x1[N];
    int interac = 1;
    do{
        //находим x^(i+1)
        for (int i = 0; i < N; i++)
        {
            double sum = 0;

            for (int j = 0; j < N; j++)
            {
                sum += matrix[i*N + j] * x[j];
                //printf("for [%d][%d]\n", i, j);
                //printf("    matrtix = %lf\n", matrix[i*N + j]);
                //printf("    x = %lf\n", x[4]);
                //printf("    sum = %lf\n\n", sum);
            }

            x1[i] = (b[i] - sum)*intercParametr(matrix, b, x) + x[i];
        }

        for (int i = 0; i < N; i++)
            {x[i] = x1[i];}

        rk = normal(matrix, b, x);

        if (interac < maxInterac)
        {
            SetColor(199,49,19);
            Line(interac, rk);
        }
        interac++;
    }
    while (rk >= eps);
}
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
