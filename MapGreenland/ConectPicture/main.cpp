#include <stdio.h>
#include "ReadImage.h"
#include <math.h>

//==============================================================================
int h,w;
int h1,w1;
int h2,w2;

char *R,*G,*B;
char *R1,*G1,*B1;
char *R2,*G2,*B2;
//==============================================================================

int main()
{
      GetSize("C:\\Users\\daniil\\Documents\\Drobotenko\\MapGreenland\\MapGreenland\\MapGreenland.bmp", &h1, &w1);
      R1 = new char[h1*w1];
      G1 = new char[h1*w1];
      B1 = new char[h1*w1];
      ReadImageFromFile("C:\\Users\\daniil\\Documents\\Drobotenko\\MapGreenland\\MapGreenland\\MapGreenland.bmp", B1, G1, R1);
      WriteImage("MapGreenland.bmp",B1,G1,R1);

      GetSize("C:\\Users\\daniil\\Documents\\Drobotenko\\MapGreenland\\TempMapGreenland\\TempMapGreenland.bmp", &h2, &w2);
      R2 = new char[h2*w2];
      G2 = new char[h2*w2];
      B2 = new char[h2*w2];
      ReadImageFromFile("C:\\Users\\daniil\\Documents\\Drobotenko\\MapGreenland\\TempMapGreenland\\TempMapGreenland.bmp", B2, G2, R2);
      WriteImage("TempMapGreenland.bmp",B2,G2,R2);

      GetSize("input.bmp", &h, &w);
      R = new char[h*w];
      G = new char[h*w];
      B = new char[h*w];
      ReadImageFromFile("input.bmp",B,G,R);
//------------------------------------------------------------------------------
      for (int i = 0; i < h; i++)
      {
            for (int j = 0; j < w; j++)
            {
                  int index = i*w + j;
                  if (R1[index] == 0 && G1[index] == 0 && B1[index] == 0)
                        {R[index] = G[index] = B[index] = 0;}
                  else
                  {
                        R[index] = R2[index];
                        G[index] = G2[index];
                        B[index] = B2[index];
                  }
            }
      }
//------------------------------------------------------------------------------
      WriteImage("output.bmp",B,G,R);
};
//==============================================================================