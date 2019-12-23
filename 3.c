#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
int *primeTable(int prime_num)
{
	int i = 2,j,p = 0,flag;
	int *primes = (int*)malloc(prime_num*sizeof(int));
	while(p < prime_num)
	{
		flag = 1;
		for(j = 2;j < i;j++)
		{
			if(i%j == 0)
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			primes[p] = i;
			p += 1;
		}
		i += 1;
	}
	return primes;
}
double *sineTable(int sine_num)
{
	int i,j;
	double a,pi = 3.1415;
	double *sines= (double*)malloc(sine_num * sizeof(double));
	for(i = 0;i < sine_num;i++)
	{
		sines[i] = 0.0;
		for(j = 0;j <= i;j++)
		{
			a = (j *pi )/180;
			sines[i] = sin(a);
		}
	}
	return sines;
}
void main()
{
	int size;
	printf("Enter size till which prime Table and sine Table is found\n");
	scanf("%d",&size);
	#pragma omp parallel sections
	{
		#pragma omp secton
		{
			int *a = (int*)malloc(size*sizeof(int));
			a = primeTable(size);
			for(int i = 0;i < size;i++)
				printf("%d\n",a[i]);
		}
		#pragma omp section
		{
			double *b = (double*)malloc(size * sizeof(double));
			b = sineTable(size);
			for(int i = 0;i < size;i++)
				printf("%lf\n",b[i]);
		}
	}
}

