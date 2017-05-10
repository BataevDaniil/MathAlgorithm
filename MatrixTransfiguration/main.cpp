#include <stdio.h>
#include <math.h>
//=============================================================================

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
    double multi = 1;
    int str;
    int i, j;

    while(true)
    {
        writeMatrix(matrix);

        printf(" 1. Swap string\n");
        printf(" 2. Swap column\n");
        printf(" 3. Multi\n");
        printf(" 4. Exit and save\n");
        printf(" 5. Multi string on number : ");

        scanf("%d", &str);
        printf("\n");

        if (str == 5)
        {

            printf("multi = ");
            scanf("%lf", &multi);

            printf("Str = ");
            scanf("%d", &i);

            for (int k = 0; k < N; k++)
            {
                matrix[(i-1)*N + k] *= multi;
            }

            continue;
        }

        if (str == 4)
            {break;}

        if (str == 2)
        {
            printf("iStr = ");
            scanf("%d", &i);

            printf("jStr = ");
            scanf("%d", &j);

            for (int k = 0; k < N; k++)
            {
                double tmp;
                tmp = matrix[k*N + i-1];
                matrix[k*N + i-1] = matrix[k*N + j-1];
                matrix[k*N + j-1] = tmp;
            }

            continue;
        }

        if (str == 1)
        {

            printf("iStr = ");
            scanf("%d", &i);

            printf("jStr = ");
            scanf("%d", &j);

            for (int k = 0; k < N; k++)
            {
                double tmp;
                tmp = matrix[(i-1)*N + k];
                matrix[(i-1)*N + k] = matrix[(j-1)*N + k];
                matrix[(j-1)*N + k] = tmp;
            }

            double tmp;
            tmp = b[i-1];
            b[i-1] = b[j-1];
            b[j-1] = tmp;

            continue;
        }

        if (str == 3)
        {
            printf("multi = ");
            scanf("%lf", &multi);

            printf("iStr = ");
            scanf("%d", &i);

            printf("jStr = ");
            scanf("%d", &j);

            for (int k = 0; k < N; k++)
            {
                matrix[(j-1)*N + k] = matrix[(i-1)*N + k]*multi + matrix[(j-1)*N + k];
            }
            b[j-1] += b[i-1]*multi;

            continue;
        }
    }
//-----------------------------------------------------------------------------
    fileWrite();
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
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            {fprintf(fp, "%6.2lf  ", matrix[i*N+j]);}

        fprintf(fp, "\n");
    }
//--------------------------------------------
    fprintf(fp, "\n");
    fprintf(fp, "Значениее_правой_части_(double):\n");
//--------------------------------------------
    for (int i = 0; i < M; i++)
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
    b = new double[M];
//--------------------------------------------
    ftrash (fp, 1);
    for (int i = 0; i < N*M; i++)
        {fscanf(fp, "%lf", &matrix[i]);}
//--------------------------------------------
    ftrash (fp, 1);
    for (int i = 0; i < M; i++)
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

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            {printf("%6.2lf ", array[i*N+j]);}

        printf(" | %6.2lf\n", b[i]);
    }
    printf("\n");
};
//=============================================================================
