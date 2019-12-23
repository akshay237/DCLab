#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include<math.h>
#define K 4
int num_threads;
long num_points;
long** points;
int cluster[K][2] ={{75,25},{25,25},{25,75},{75,75}};
long cluster_count[K];
void populate_points()
{
	long i;
	points = (long**)malloc(sizeof(long) * num_points);
	for(i = 0;i < num_points;i++)
		points[i]= (long *)malloc(sizeof(long) * 2);
	for(i=0;i<num_points;i++)
	{
		points[i][0] = rand() % 100;
		points[i][1] = rand() % 100;
	}
	for(i = 0;i < K;i++)
		cluster_count[i] = 0;
}
double get_distance(int x1,int y1,int x2,int y2)
{
	int dist_x = x2 - x1;
	int dist_y = y2 - y1;
	return (double)sqrt(dist_x*dist_x + dist_y*dist_y);
}
void classify_points()
{
	long i;
	#pragma omp parallel for num_threads(num_threads)
	for(i = 0;i<num_points;i++)
	{
		double min_dist = 1000,curr_dist = 1;
		int cluster_index = -1,j;
		for(j = 0;j < K;j++)
		{
			curr_dist = get_distance(points[i][0],points[i][1],cluster[j][0],cluster[j][1]);
			if(curr_dist < min_dist)
			{
				min_dist = curr_dist;
				cluster_index = j;
			}
		}
		cluster_count[cluster_index]++;
	}
}
int main(int argc,char* argv[])
{
	num_points = atoi(argv[1]);
	num_threads = atoi(argv[2]);
	populate_points();
	double t1 = omp_get_wtime();
	classify_points();
	double t2 = omp_get_wtime();
	double t = (t2 - t1) * 1000;
	printf("Time taken: %lfms\n",t);
}
