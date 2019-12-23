#include<stdio.h>
#include<string.h>
#include<gd.h>
#include<omp.h>
int main(int argc,char *argv[])
{
	if(argc < 4)
	{
		printf("Provide the arguments\n");
		return 1;
	}
	char *input = argv[1];
	char *output = argv[2];
	int num_threads = atoi(argv[3]);
	int color,x,y,i;
	int red,green,blue;
	FILE *fp;
	if((fp = fopen(input,"r")) == NULL)
	{
		printf("Error in opening file %s\n",input);
		return 1;
	}
	gdImagePtr img = gdImageCreateFromPng(fp);
	int width = gdImageSX(img);
	int height = gdImageSY(img);
	double t1 = omp_get_wtime();
	#pragma omp parallel for private(y,color,red,green,blue) num_threads(num_threads)
	for(x = 0;x < width;x++)
	{	
	   #pragma omp critical
	    {
		for(y = 0;y< height;y++)
		{
		  color = x + 0;
		  color = gdImageGetPixel(img,x,y);
		  red = 255 -gdImageRed(img,color);
		  green = 255 -gdImageGreen(img,color);
		  blue = 255 -gdImageBlue(img,color);
		  int avg = (gdImageRed(img,color) + gdImageGreen(img,color) + gdImageBlue(img,color))/3;
		  color =  gdImageColorAllocate(img,avg,avg,avg);
		  gdImageSetPixel(img,x,y,color);
		}
	    }
	}
	double t2 = omp_get_wtime();
	if((fp = fopen(output,"w")) == NULL)
	{
		printf("Error in opening output file");
		return 1;
	}
	gdImagePng(img,fp);
	gdImageDestroy(img);
	fclose(fp);
	printf("File Size:%d x %d\n",width,height);
	printf("Time taken:%lf\n",(t2 -t1));
	return 0;
}


