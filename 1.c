#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
void merge(int* a,int l,int m,int r)
{
    int i=0,j=0;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1],R[n2];
    for(int i = 0;i < n1;i++)
        L[i] = a[l + i];
    for(int j = 0;j < n2;j++)
        R[j] = a[m + 1 + j];
    int k = l;
    while(i < n1 & j < n2)
    {
        if(L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }
    while(j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}
void mergesort(int* a,int l,int r)
{
    if(l < r)
    {
        int m;
        #pragma omp parallel sections
        {
            m = (l+r)/2;
            #pragma omp section
            {
                mergesort(a,l,m);
            }
            #pragma omp section
            {
                mergesort(a,m+1,r);
            }
        }
        merge(a,l,m,r);
    }
}
void main()
{
    omp_set_nested(1);
    int i,j,size;
    printf("Enter the size of array\n");
    scanf("%d",&size);
    for(i = 0; i<4; i++)
	{
		int a[size];
		for(j = 0; j<size; j++)
		{
			a[j] = rand()%100000;
		}
		for(i = 0; i<4; i++)
		{
			omp_set_num_threads(2*(i));
			double t1 = omp_get_wtime();
			mergesort(a,0,size-1);
			double t2 = omp_get_wtime();
			printf("%lf\t",t2-t1);
		}
		printf("\n");
		for(i = 0;i < size;i++)
	    {
			printf("%d\t",a[i]);
	    }
		printf("\n");
	}
    
}
