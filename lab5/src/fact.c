#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "utils.h"

#include <pthread.h>


void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}

int main(int argc, char **argv) {
  /*
   *  TODO:
   *  threads_num by command line arguments
   *  array_size by command line arguments
   *	seed by command line arguments
   */

  uint32_t k = -1;
  uint32_t pnum = -1;
  uint32_t mod = -1;

  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"k", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            k = atoi(optarg);
            // your code here
            // error handling
            if (k <= 0)
            {
                printf("k must be positive");
                k = -1;
            }
            break;
          case 1:
            pnum = atoi(optarg);
            // your code here
            // error handling
            if (pnum <= 0)
            {
                printf("pnum must be positive");
                pnum = -1;
            }
            break;
          case 2:
            mod = atoi(optarg);
            if (mod <= 0)
            {
                printf("mod is positive number");
                mod = -1;
            }
            break; 

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }
  if (k == -1 || pnum == -1 || mod == -1) {
    printf("Usage: %s --k \"num\" --pnum \"num\" --mod \"num\"\n",
           argv[0]);
    return 1;
  }

  pthread_t threads[threads_num];
  int n = k / pnum;
  struct SumArgs args[threads_num];
  for (uint32_t i = 0; i < threads_num; i++) {
    args[i].array = array; 
    args[i].begin = i * n; 
    args[i].end = (i+1)*n;
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args[i])) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    total_sum += sum;
  }
  
  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);
  printf("Total: %d\n", total_sum);
  printf("Elapsed time: %fms\n", elapsed_time);
  return 0;
}