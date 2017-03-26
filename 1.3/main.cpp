/*
Делает из цветной фотографии черно белую и можно задать контрастность в
процентах
*/
#include <stdio.h>
#include "ReadImage.h"
//==============================================================================
void draw();
int transformationColor(int color);
//==============================================================================
int   h,w;
char  *R,*G,*B;
#define CONTRAST 0
//==============================================================================

int main()
{
  GetSize("input.bmp", &h, &w);

  R = new char[h*w];
  G = new char[h*w];
  B = new char[h*w];
  ReadImageFromFile("input.bmp",B,G,R);

  draw();

  WriteImage("output.bmp",B,G,R);
};
//==============================================================================

void draw()
{
  for (int i=0; i < h*w; i++)
  {
    int middleColor = (int)((transformationColor(R[i]) + transformationColor(G[i]) + transformationColor(B[i]))/3);

    int contrast = (int)middleColor*CONTRAST/100;

    if (middleColor > 127)
    {
      if (middleColor + contrast < 255)
        {middleColor += contrast;}
      else middleColor = 255;
    }
    else {middleColor -= contrast;}

    R[i] = G[i] = B[i] = middleColor;
  }
};
//==============================================================================

int transformationColor(int color)
{
  return (color < 0)?(color+=256):(color);
}
//==============================================================================