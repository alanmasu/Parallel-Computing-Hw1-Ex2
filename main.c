/*                      INTRODUCTION TO PARALLEL COMPUTING - Prof. VELLA 

    Student: Alan Masutti - 226901
    Assignment 1 - Exercise 2:
      - T1: Write a C/C++ sequential program and the related routine, namely routine1, that takes the
            matrix M (use again random numbers to initialize it), its size n and a parameter block dimension
            b (integer) such that the matrix can be split into b-by-b blocks. Copy each block and its related
            elements, in the reverse order (assume row-major ordering) in the output matrix O of the same
            size. Figure 1 and 2 show an example. Use a wall-clock time, at the program level, that measures
            the time of the for loop only.
      - T2: Write a function, routine2, that utilizes implicit parallelism techniques like vectorization or soft-
            ware prefetching to improve performance.
      - T3: Benchmark and compare the performance of the two routines assuming that n is equal to 2^12 ,
            while b can vary from 2^2 to 2^8 . Summarize the results in a plot showing on the x-axis the size of
            the block size and on the y-axis the eff ective bandwidth of each routine.
      - T4: Write a short document, describing the solution implemented, the performance, and comment
            on the results you have obtained.
      - T5: (optional) Answer the following question. How far is your routine from the peak? Visu-
            alize in the performance plot the peak of the system.
    Notes:
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

uint64_t routine1(float* M, float* O, int n, int b){
    struct timespec start, end;

    int br, bc, r, c;
    int rM, cM, rO, cO;
    int N_B = n/b;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (br = 0; br < N_B; ++br){
        for(bc = 0; bc < N_B; ++bc){
            for(r = 0; r < b; ++r){
                for(c = 0; c < b; ++c){
                    rM = br*b + r;
                    cM = bc*b + c;
                    rO = n-1 - bc*b + c;
                    cO = n-1 - br*b + r;
                    O[rO*n + cO] = M[rM*n + cM];
                }
            }
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);

    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
}

int main(int argc, char const *argv[]){
    const int N = 4;
    const int B = 2;
     
    int i, j, ii;

    float M[N][N];
    float O[N][N];

    //Populating the matrix M with random numbers
    ii = 0;
    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j){
            M[i][j] = ii;
            ++ii;
        }
    }

    //Printing the matrix M
    printf("Matrix M:\n", time);
    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j)
            printf("%f ", M[i][j]);
        printf("\n");
    }

    uint64_t time = routine1((float*)M, (float*)O, N, B);

    //Printing the result
    printf("Time: %d us, Matrix O:\n", time);
    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j)
            printf("%f ", O[i][j]);
        printf("\n");
    }
    
    return 0;
}
