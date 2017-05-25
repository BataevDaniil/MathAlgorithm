#include <stdio.h>
#include "Graph.h"
#include <math.h>

//==============================================================================

void ftrash( FILE *fp, int n );
void fileRead();
void fileWrite();
void writeTerminal();

void solveSec();
void solveDelMidl();

void drawOxy();
void drawMainF();
void drawSec();

double f( double x );

//==============================================================================

double a, b, c, d;

double eps;
double x0, x1;

int countInteracDelMidl;
double answerDelMidl;

int countInteracSec;
double answerSec;
#define maxNumberIntervalAnswer 10
double intervalAnswer[maxNumberIntervalAnswer];

//==============================================================================

int main()
{
      fileRead();
//------------------------------------------------------------------------------
      solveSec();

      solveDelMidl();
//------------------------------------------------------------------------------
      drawOxy();
      drawMainF();
      drawSec();

      writeTerminal();
//------------------------------------------------------------------------------
      fileWrite();
};
//==============================================================================

void drawSec()
{
      ReadWindow("output.bmp", a, b, c, d);
//------------------------------------------------------------------------------
      int countInterac;
      if (maxNumberIntervalAnswer < countInteracSec+2)
            countInterac = maxNumberIntervalAnswer;
      else countInterac = countInteracSec+2;

      SetColor(0,200,0);
      SetPoint(intervalAnswer[0], f(intervalAnswer[0]));
      for (int i = 2; i < countInterac; i++)
      {
            Line(intervalAnswer[i], 0);
            SetPoint(intervalAnswer[i-1], f(intervalAnswer[i-1]));
      }

      SetColor(0,0,200);
      for (int i = 0; i < countInterac; i++)
      {
            SetPoint(intervalAnswer[i], 0);
            Line(intervalAnswer[i], f(intervalAnswer[i]));
      }
//------------------------------------------------------------------------------
      CloseWindow();
};
//==============================================================================

void drawMainF()
{
      ReadWindow("output.bmp", a, b, c, d);
//------------------------------------------------------------------------------
      SetColor(199,49,19);

      int delPlot = 100;
      double xStep = (b-a)/delPlot;
      double x = a;
      SetPoint(x,f(x));
      for (int i = 0; i < delPlot; i++)
      {
            x+=xStep;
            Line(x,f(x));
      }
//------------------------------------------------------------------------------
      CloseWindow();
};
//==============================================================================

void drawOxy()
{
      SetColor(255,255,255);
      SetWindow(a,b,c,d);

      SetColor(0,0,0);
      xyLine(a,0,0.1,0.1);

      CloseWindow();
};
//==============================================================================

double f(double x)
{
      return sin(x) + pow(x,8) - 1.;
};
//==============================================================================

void solveSec()
{
      //Метод секущих

      intervalAnswer[0] = x0;
      intervalAnswer[1] = x1;

      double x0 = intervalAnswer[0];
      double x1 = intervalAnswer[1];

      countInteracSec = 0;
      do
      {
            answerSec = x1 - (x1-x0)/(f(x1)-f(x0))*f(x1);

            x0 = x1;
            x1 = answerSec;

            countInteracSec++;

            if (countInteracSec < maxNumberIntervalAnswer-1)
            {
                  intervalAnswer[countInteracSec+1] = answerSec;
            }
      }
      while(fabs(f(answerSec)) > eps);
};
//==============================================================================

void solveDelMidl()
{
      //Метод деления отрезка пополам.
      countInteracDelMidl = 0;

      double b = b;
      double a = a;

      do
      {
            answerDelMidl = (b+a)/2;

            if (f(answerDelMidl)*f(b) > 0)
                  {b = answerDelMidl;}
            else {a = answerDelMidl;}

      countInteracDelMidl++;
      }
      while(fabs(f(answerDelMidl)) > eps);
};
//==============================================================================

void fileWrite()
{
      FILE *fp;
      fp = fopen("output.txt", "w");

      fprintf(fp, "Метод секущих \n");
      fprintf(fp, "answer = %lf \n", answerSec);
      fprintf(fp, "fault = %lf \n", f(answerSec));
      fprintf(fp, "countInterac = %d \n", countInteracSec);

      fprintf(fp, "\n");
      fprintf(fp, "Метод деления отрезков пополам \n");
      fprintf(fp, "answer = %lf \n", answerDelMidl);
      fprintf(fp, "fault = %lf \n", f(answerDelMidl));
      fprintf(fp, "countInterac = %d \n", countInteracDelMidl);

      fclose(fp);
};
//==============================================================================

void writeTerminal()
{
      printf("a = %lf \n", a);
      printf("b = %lf \n", b);
      printf("c = %lf \n", c);
      printf("d = %lf \n", d);

      printf("\n");
      printf("Метод секущих \n");
      printf("x0 = %lf \n", x0);
      printf("x1 = %lf \n", x1);
      printf("answer = %.20lf \n", answerSec);
      printf("fault = %.20lf \n", f(answerSec));
      printf("countInterac = %d \n", countInteracSec);

      printf("\n");
      printf("Метод деления отрезков пополам \n");
      printf("answer = %lf \n", answerDelMidl);
      printf("fault = %lf \n", f(answerDelMidl));
      printf("countInterac = %d \n", countInteracDelMidl);

      printf("\n");
      int countInterac;
      if (maxNumberIntervalAnswer < countInteracSec+2)
            countInterac = maxNumberIntervalAnswer;
      else countInterac = countInteracSec+2;

      for (int i = 0; i < countInterac; i++)
      {
            printf("intervalAnswer[%d] = %.20lf \n", i, intervalAnswer[i]);
      }
};
//==============================================================================

void fileRead()
{
      FILE *fp;
      fp = fopen ("input.txt", "r");

      ftrash (fp, 1);
      fscanf(fp, "%lf", &a);

      ftrash (fp, 1);
      fscanf(fp, "%lf", &b);

      ftrash (fp, 1);
      fscanf(fp, "%lf", &c);

      ftrash (fp, 1);
      fscanf(fp, "%lf", &d);

      ftrash (fp, 1);
      fscanf(fp, "%lf", &eps);

      ftrash (fp, 2);
      fscanf(fp, "%lf", &x0);

      ftrash (fp, 1);
      fscanf(fp, "%lf", &x1);

      fclose(fp);
};
//==============================================================================

void ftrash (FILE *fp, int n)
{
      char trash[500];
      for (int i = 0; i < n; i++)
            {fscanf(fp, "%s", trash);}
};
//==============================================================================