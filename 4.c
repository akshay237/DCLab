#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
long factorial(int n)
{
	if(n==0||n==1)
		return 1;
	long fact = 1;
	for(int i = 2;i <=n;i++)
		fact = fact * i;
	return fact;
}
void main()
{
	int i,n;
	printf("Enter the number whose factorial is calculated:\n");
	scanf("%d",&n);
	long *x;
	x = (long*)malloc((n+1) * sizeof(long));
	for(i = 0;i <= n;i++)
		x[i] = factorial(i);
	#pragma omp parallel for firstprivate(x)
	for(i = 1;i <= n;i++)
		x[i] = i * x[i - 1];
	for(i = 1;i <= n;i++)
		printf("Factorial of %d : %ld\n",i,x[i]);
}
