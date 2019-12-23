#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define VECLEN 100
int main(int argc,char* argv[])
{
	int i,id,numprocess,len = VECLEN;
	double a[len],b[len];
	double mysum,allsum;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocess);
	if(id == 0)
		printf("Starting dot product using % d tasks\n",numprocess);
	for(i=0;i<len;i++)
	{
		a[i]=1.0;
		b[i]=a[i];
	}
	mysum = 0.0;
	for(i=0;i<len;i++)
		mysum += a[i]*b[i];
	printf("Task %d partial sum:%f\n",id,mysum);
	MPI_Reduce(&mysum,&allsum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(id == 0)
		printf("Global sum : %f\n",allsum);
	MPI_Finalize();
}
