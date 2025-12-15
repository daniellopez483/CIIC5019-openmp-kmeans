# CIIC5019 - Parallel K-Means Using OpenMP

This project implements the K-Means clustering algorithm in C and parallelizes it using OpenMP.  

## Requirements
- C compiler
- OpenMP support  
- macOS users need `libomp`

Install OpenMP on macOS:
```bash
brew install libomp
```

## Compile

### macOS (clang)
```bash
clang -O3 kmeans_omp_gen.c -o kmeans_omp \
  -Xpreprocessor -fopenmp \
  -lomp
```

### Linux / GCC
```bash
gcc -O3 -fopenmp kmeans_omp_gen.c -o kmeans_omp
```

## Run
```bash
./kmeans_omp N D K iters threads
```

Example:
```bash
./kmeans_omp 100000 2 5 50 8
```

## Output
The program prints the total execution time in seconds.  
Run the program with different thread counts to evaluate speedup.

## Author
Daniel López Moreu  
University of Puerto Rico – Mayagüez
