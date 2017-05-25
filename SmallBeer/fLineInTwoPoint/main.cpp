#include <stdio.h>
#include <math.h>
#include "Graph.h"
//==============================================================================

void searchCoefficentLine();

double fLine(double x, double y);

void writeTerminal();

void drawLine();
//==============================================================================

double point1[2];
double point2[2];

double a,b,c,d;

double Ak, Bk, Ck;
//==============================================================================

int main()
{
      a = -10; b = 10;
      c = -10; d = 10;

      point1[0] = 1;
      point1[1] = 1;

      point2[0] = 3;
      point2[1] = 2;

      searchCoefficentLine();

      drawLine();

      writeTerminal();
};
//==============================================================================

double fLine(double x, double y)
{
      return Ak*x + Bk*y + Ck;
};
//==============================================================================

void searchCoefficentLine()
{
      Ak = point1[1] - point2[1];
      Bk = point2[0] - point1[0];
      Ck = point1[0]*(point2[1] - point1[1]) + point1[1]*(point1[0] - point2[0]);
};
//==============================================================================

void drawLine()
{
      SetColor( 250, 250, 250 );
      SetWindow( a,b,c,d );

      SetColor( 0, 0, 0 );
      xyLine( 0, 0, (b-a)/10, (d-c)/10 );


      double xStep = (b - a) / w;
      double yStep = (d - a) / h;

      int xY = 0;
      double eps = 0.0000000001;
      for (double y = c; y < d; y+=yStep)
      {
            for (double x = a; x < b; x+=xStep)
            {

                  if (fabs(fLine( x, y )) < eps)
                  {
                        R[xY] = 0;
                        G[xY] = 0;
                        B[xY] = 255;
                  }

                  xY++;
            }
      }

      CloseWindow();
};
//==============================================================================

void writeTerminal()
{
      printf("\n");
      printf("a = %lf \n", a);
      printf("b = %lf \n", b);
      printf("c = %lf \n", c);
      printf("d = %lf \n", d);

      printf("\n");
      printf("point1 = ( %lf, %lf ) \n", point1[0], point1[1]);
      printf("point2 = ( %lf, %lf ) \n", point2[0], point2[1]);

      printf("\n");
      printf("Ak = %lf\n", Ak);
      printf("Bk = %lf\n", Bk);
      printf("Ck = %lf\n", Ck);
};
//==============================================================================