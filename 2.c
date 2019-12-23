#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
void main()
{
	int m,n,i,j;
	printf("Enter the size of matrix\n");
	scanf("%d%d",&m,&n);
	int mat[m][n],vec[n],res[m];
	printf("Enter the elements of matrix\n");
	for(i = 0;i < m;i++)
	{
		for(j = 0;j < n;j++)
			scanf("%d",&mat[i][j]);
		res[i] = 0;
		printf("\n");
	}
	printf("Enter the vector elements\n");
	for(i = 0;i < n;i++)
		scanf("%d",&vec[i]);
	printf("\n");
	printf("Matrix is\n");
	for(i = 0;i < m;i++)
	{
		for(j = 0;j < n;j++)
			printf("%d\t",mat[i][j]);
		printf("\n");
	}
	printf("Vector is\n");
	for(i = 0;i<n;i++)
		printf("%d\t",vec[i]);
	printf("\n");
	#pragma omp parllel for num_threads(8)
	for(i = 0;i < m;i++)
		for(j = 0;j < n;j++)
			res[i] = res[i] + mat[i][j] * vec[j];
	printf("Result after multiplication of matrix and vector is\n");
	for(i = 0;i < m;i++)
		printf("%d\n",res[i]);
}
