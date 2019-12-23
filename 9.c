#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<math.h>
#define SEED 35791246
int main(int argc,char* argv[])
{
	int i,id,nodenum,count = 0,finalcount=0;
	long niter = 1000000,finalniter=0;
	double x,y,z,pi;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nodenum);
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	int recieved[nodenum];
	long recvniter[nodenum];
	srand(SEED+id);
	if(id != 0)
	{
		for(i=0;i<niter;i++)
		{
		  x=((double)rand())/RAND_MAX;
		  y=((double)rand())/RAND_MAX;
		  z=sqrt(x*x+y*y);
		  if(z<=1)
		     count++;
		}
		for(i=0;i<nodenum;i++)
		{
			MPI_Send(&count,1,MPI_INT,0,1,MPI_COMM_WORLD);
			MPI_Send(&niter,1,MPI_LONG,0,2,MPI_COMM_WORLD);
		}
	}
	else if(id == 0)
	{
	   	for(i=0;i<nodenum;i++)
		{
			MPI_Recv(&recieved[i],nodenum,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&recvniter[i],nodenum,MPI_LONG,MPI_ANY_SOURCE,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
	}
	if(id == 0)
	{
		for(i=0;i<nodenum;i++)
		{
			finalcount+=recieved[i];
			finalniter+=recvniter[i];
		}
		pi=((double)finalcount/(double)finalniter)*4.0;
		printf("Pi : %f\n",pi);
	}
	MPI_Finalize();
	return 0;
}






