//				”чебна€ программа 
//				
//				ѕрограмма обработки изображений
//				в формате 24-пиксельных bmp-файлов
//				13 феврал€ 2015 г.				
//---------------------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "ReadImage.h"
#include <math.h>

using namespace std;

int		h,w;
char		*R,*G,*B;
int		kr,kg,kb,k1,k2,variant;

void Vvod();
void Ris1();									// изображение јндреевского флага
void Ris2();									// изображение эллипса
int f(int x,int y);
//---------------------------------------------------------------------------------------
int main()
{
	Vvod();
	GetSize("input2.bmp", &h, &w);				// читаем размеры файла в пиксел€х
											// (w -- ширина, h -- высота)
	R = new char[h*w];
	G = new char[h*w];
	B = new char[h*w];
	ReadImageFromFile("input2.bmp",B,G,R);			// считываем значени€ цветовых составл€ющих изображени€:
											// R -- красной, G -- зеленой, B -- синей
	switch (variant)
	{
		case 1:Ris1();break;
		case 2:Ris2();break;
	}
	WriteImage("output.bmp",B,G,R);				// создаем bmp-файл и записываем в него полученное "изображение"
}
//---------------------------------------------------------------------------------------
void Vvod()
{
	char		pust[100];
	float  scan;
	FILE *fp;									// указатель на файл
	fp=fopen("in.txt","r");						// открыть файл дл€ чтени€
											// чтение из файла
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&kr);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&kg);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&kb);
	
	fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);fscanf(fp,"%s",pust);
	fscanf(fp,"%d",&k1);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);
	fscanf(fp,"%d",&k2);fscanf(fp,"%s",pust);
	fscanf(fp,"%s",pust);fscanf(fp,"%d",&variant);
	fclose(fp);								// закрыть файл дл€ чтени€
}
//---------------------------------------------------------------------------------------
void Ris1()
{
	double sd=1,								// начальное положение курсора
											// (эксперимент показал, что это лучше, чем =0)
	dsd=(double)(w-k1+1)/h;						// сдвиг по вертикали за один шаг по горизонтали
											// с учетом ширины полосы
	int sdv;
	for (int i=0;i<h;i++)
	{
		sdv=(int)sd;
		for (int j=sdv;j<sdv+k1;j++)
		{
			R[i*w+j]=kr;
			G[i*w+j]=kg;
			B[i*w+j]=kb;
		}
		sd+=dsd;
	}
	sd=1;
	for (int i=h-1;i>=0;i--)
	{
		sdv=(int)sd;
		for (int j=sdv;j<sdv+k1;j++)
		{
			R[i*w+j]=kr;
			G[i*w+j]=kg;
			B[i*w+j]=kb;
		}
		sd+=dsd;
	}   
}
//---------------------------------------------------------------------------------------
void Ris2()
{
	int x0=w/2,y0=h/2;
	for (int y=0;y<h;y++)
	for (int x=0;x<w;x++)

		if (f(x-x0,y-y0)<=0)
		{
			R[y*w+x]=kr;
			G[y*w+x]=kg;
			B[y*w+x]=kb;
		}

//		//---------- уменьшить €ркость красной составл€ющей в 2 раза
//		{
//			int r=R[y*w+x];
//			if (r<0)r+=256;
//			R[y*w+x]=r/2;
//		}
		//----------

}
//---------------------------------------------------------------------------------------
int f(int x,int y)
{
	return(x*x+y*y-k2*k2);
}
