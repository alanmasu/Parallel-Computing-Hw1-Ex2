# Introduction to parallel computing - Homework 1 -  Exercise 2

## Compiling and running the code
After download this repository on the UniTN cluster, we must request for an interactive session with the following command:
```bash
qsub -I -q short_cpuQ
```
so, after the request is accepted, we can load the module for the Intel compiler with the following command:
```bash
module load gcc91
```

Then, we can compile the code **in serial** with the following command:
```bash
gcc main.c -DNOTES=\"<what_kind_of_notes_you_want>\" 
```

for enable **only software prefetching**, or with the following command:

```bash
git checkout prefetching
gcc main.c -DNOTES=\"<only-prefetching>\" 
```

for compiling the code **with vectorization**, we must use the following command:
```bash 
git checkout vectorization-only
gcc main.c -DNOTES=\"<what_kind_of_notes_you_want>\" -O3 -mavx [-ftree-vectorizer-verbose=2] 
```

For compiling the code **whit vectorization and prefetching**, we must use the following command:
```bash
git checkout main
gcc main.c -DNOTES=\"<what_kind_of_notes_you_want>\" -O3 -mavx [-ftree-vectorizer-verbose=2] 
```
the flag `-ftree-vectorizer-verbose=2` is optional and it is used to print the vectorization report.

## Running the code
After the compilation, we can run the code with the following command:
```bash
./a.out
```

## Gettig the results and plotting them
After the execution of the program it's possible to see the results on a file called `resoults.csv` and this file can be also used to plot the results with the python script `chart.py`.

In order to plot the results, we can use the following command:
```bash
module add python-3.8.13

#If there isn't the libraries, we can install them with the following command:
pip3 install matplotlib numpy pandas

#or just run the script
python3 chart.py
```
