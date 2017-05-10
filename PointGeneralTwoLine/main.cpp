#include <stdio.h>
#include <math.h>
#include "Graph.h"
//==============================================================================

double fLine1(double x, double y);
double fLine2(double x, double y);

void writeTerminal();

void drawLine();
//==============================================================================

double a,b,c,d;

double A1, B1, C1;
double A2, B2, C2;
//==============================================================================

int main()
{
      a = -40; b = 40;
      c = -40; d = 40;

      A1 = 1; B1 = -1, C1 = 0;
      A2 = 2; B2 = -1, C2 = 0;

      drawLine();

      {
            double delta  = A1*B2 - B1*A2;
            double delta1 = B1*C2 - C1*B2;
            double delta2 = C1*A2 - A1*C2;

            double x = delta1 / delta;
            double y = delta2 / delta;

            printf("x = %lf\n", x);
            printf("y = %lf\n", y);
      }

      writeTerminal();
};
//==============================================================================

double fLine1(double x, double y)
{
      return A1*x + B1*y + C1;
};
//==============================================================================

double fLine2(double x, double y)
{
      return A2*x + B2*y + C2;
};
//==============================================================================

void drawLine()
{
      SetColor( 250, 250, 250 );
      SetWindow( a,b,c,d );

      SetColor( 0, 0, 0 );
      xyLine( 0, 0, (b-a)/10, (d-c)/10 );
//------------------------------------------------------------------------------

      double xStep = (b - a) / w;
      double yStep = (d - a) / h;

      int xY = 0;
      double eps = 0.0000000001;
      for (double y = c; y < d; y+=yStep)
      {
            for (double x = a; x < b; x+=xStep)
            {

                  if (fabs(fLine1( x, y )) < eps)
                  {
                        R[xY] = 0;
                        G[xY] = 0;
                        B[xY] = 255;
                  }

                  if (fabs(fLine2( x, y )) < eps)
                  {
                        R[xY] = 0;
                        G[xY] = 255;
                        B[xY] = 0;
                  }

                  xY++;
            }
      }
//------------------------------------------------------------------------------
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
      printf("A1 = %lf\n", A1);
      printf("B1 = %lf\n", B1);
      printf("C1 = %lf\n", C1);

      printf("\n");
      printf("A2 = %lf\n", A2);
      printf("B2 = %lf\n", B2);
      printf("C2 = %lf\n", C2);
};
//==============================================================================