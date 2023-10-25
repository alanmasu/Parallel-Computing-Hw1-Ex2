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
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#ifndef NOTES
    #define NOTES ""
#endif

// Random float generator
float randomF(int min, int max, int prec){ 
  prec = 10 * prec; 
  return (rand() % (max * prec - min * prec + 1) + min * prec) / (float)prec; 
}

uint64_t routine1(float* M, float* O, int n, int b){
    struct timespec start, end;

    int br, bc, r, c;
    int rM, cM, rO, cO;
    int N_B = n/b;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (br = 0; br < N_B; ++br){
        for(r = 0; r < b; ++r){
            for(bc = 0; bc < N_B; ++bc){
                for(c = 0; c < b; ++c){
                    rM = br*b + r;
                    cM = bc*b + c;
                    rO = n - b - br*b + r;
                    cO = n - b - bc*b + c;
                    O[rO*n + cO] = M[rM*n + cM];
                }
            }
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);

    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
}

int main(int argc, char const *argv[]){
    const int N = 4096;
    int B = 2;
     
    int i, j, ii;

    float M[N][N];
    float O[N][N];

    //Retriving some info about the machine
    char hostbuffer[256];
    int hostname;
 
    // retrieve hostname
    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    if (hostname == -1) {
        printf("Error when getting hostname\n");
    }

    FILE *fp;
    fp = fopen("resoults.csv", "a");

    if(fp == NULL){
        printf("Error opening file\n");
    }

    //Populating the matrix M with random numbers
    srand(time(NULL));
    for(i = 0; i < N; ++i){
        for(j = 0; j < N; ++j)
            M[i][j] = randomF(0, 1000, 3);
    }
    

    //Printing the matrix M [ONLY FOR DEBUGGING]
    // printf("Matrix M:\n", time);
    // for(i = 0; i < N; ++i){
    //     for(j = 0; j < N; ++j)
    //         printf("%d\t", (int)M[i][j]);
    //     printf("\n");
    // }

    uint64_t time;
    for(B = 4; B <= 256; B*=2){
        time = routine1((float*)M, (float*)O, N, B);
        printf("Time: %f s\n", time/1000000.0);
        if (fp != NULL){
            fprintf(fp, "%d,%f,%s,%s\n", B, time/1000000.0, hostbuffer, NOTES);
        }
    }
    

    //Printing the result [ONLY FOR DEBUGGING]
    // printf("Time: %d us, Matrix O:\n", time);
    // for(i = 0; i < N; ++i){
    //     for(j = 0; j < N; ++j)
    //         printf("%d\t", (int)O[i][j]);
    //     printf("\n");
    // }
    
    return 0;
}
