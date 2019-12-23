DCLab
For OpenMp Programs execution
gcc -fopenmp fileName.c
./a.out

For MPI Programs execution
mpicc fileName.c
mpirun -np 4 ./a.out

For Program 5:
gcc -fopenmp 5.c -lm
./a.out arg1 arg2(Both argument of Integer type)

For Program 6:
gcc -fopenmp 6.c -lgd
./a.out arg1 arg2 arg3(arg1 and arg2 are image file name in png format and arg3 of Integer type)
