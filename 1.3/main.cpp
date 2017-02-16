//
#include <stdio.h>
#include "ReadImage.h"
//
void draw();
int transformationColor(int color);
//
int		h,w;
char  *R,*G,*B;

int main()
{
	GetSize("input3.bmp", &h, &w);				// читаем размеры файла в пикселях
											// (w -- ширина, h -- высота)
	R = new char[h*w];
	G = new char[h*w];
	B = new char[h*w];
	ReadImageFromFile("input3.bmp",B,G,R);			// считываем значения цветовых составляющих изображения:
											// R -- красной, G -- зеленой, B -- синей
	draw();

	WriteImage("output.bmp",B,G,R);				// создаем bmp-файл и записываем в него полученное "изображение"
};
//=========================================================================================================
void draw()
{
	#define CONTRAST 10

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
//=========================================================================================================
int transformationColor(int color)
{
	return (color < 0)?(color+=256):(color);
}
