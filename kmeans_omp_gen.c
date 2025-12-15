#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dist2(double *a, double *b, int d)
{
  double s = 0.0;
  for (int i = 0; i < d; i++)
  {
    double diff = a[i] - b[i];
    s += diff * diff;
  }
  return s;
}

int main(int argc, char **argv)
{
  if (argc < 6)
  {
    printf("Usage: %s N D K iters threads\n", argv[0]);
    return 1;
  }

  int N = atoi(argv[1]);
  int D = atoi(argv[2]);
  int K = atoi(argv[3]);
  int iters = atoi(argv[4]);
  int threads = atoi(argv[5]);

  omp_set_num_threads(threads);
  srand(123);

  double *data = malloc(N * D * sizeof(double));
  double *centroids = malloc(K * D * sizeof(double));
  int *labels = malloc(N * sizeof(int));

  for (int i = 0; i < N * D; i++)
    data[i] = (double)rand() / RAND_MAX;

  for (int k = 0; k < K; k++)
    for (int j = 0; j < D; j++)
      centroids[k * D + j] = data[k * D + j];

  double start = omp_get_wtime();

  for (int it = 0; it < iters; it++)
  {

#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
      int best = 0;
      double best_dist = dist2(&data[i * D], &centroids[0], D);

      for (int k = 1; k < K; k++)
      {
        double d = dist2(&data[i * D], &centroids[k * D], D);
        if (d < best_dist)
        {
          best_dist = d;
          best = k;
        }
      }
      labels[i] = best;
    }

    double *sum = calloc(K * D, sizeof(double));
    int *count = calloc(K, sizeof(int));

    for (int i = 0; i < N; i++)
    {
      int c = labels[i];
      count[c]++;
      for (int j = 0; j < D; j++)
        sum[c * D + j] += data[i * D + j];
    }

    for (int k = 0; k < K; k++)
    {
      if (count[k] == 0)
        continue;
      for (int j = 0; j < D; j++)
        centroids[k * D + j] = sum[k * D + j] / count[k];
    }

    free(sum);
    free(count);
  }

  double end = omp_get_wtime();
  printf("Time: %.6f seconds\n", end - start);

  free(data);
  free(centroids);
  free(labels);
  return 0;
}
