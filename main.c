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

int main(int argc, char const *argv[]){

    
    return 0;
}
