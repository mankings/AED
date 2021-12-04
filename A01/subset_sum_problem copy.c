//
// AED, November 2021
//
// Solution of the first practical assignement (subset sum problem)
//
// 103341 - João Miguel Matos
// 103470 - Filipe Antão
//

#if __STDC_VERSION__ < 199901L
# error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
# define STUDENT_H_FILE "000000.h"
#endif

//
// include files
//

#include <stdio.h>
#include <stdlib.h>
#include "../P02/elapsed_time.h"
#include STUDENT_H_FILE

//
// custom data types
//
// the STUDENT_H_FILE defines the following constants and data types
//
//   #define min_n       24                   --- the smallest n value we will handle
//   #define max_n       57                   --- the largest n value we will handle
//   #define n_sums      20                   --- the number of sums for each n value
//   #define n_problems  (max_n - min_n + 1)  --- the number of n values
//
//   typedef unsigned long long integer_t;    ---  64-bit unsigned integer
//   typedef struct
//   {
//     int n;                                 --- number of elements of the set (for a valid problem, min_n <= n <= max_n)
//     integer_t p[max_n];                    --- the elements of the set, already sorted in increasing order (only the first n elements are used)
//     integer_t sums[n_sums];                --- several sums (problem: for each sum find the corresponding subset)
//   }
//   subset_sum_problem_data_t;               --- weights p[] and sums for a given value of n
//
//   subset_sum_problem_data_t all_subset_sum_problems[n_problems]; --- // the problems
//

//
// place your code here
//
// possible function prototype for a recursive brute-force function:
//   int brute_force(int n,integer_t p[n],int desired_sum,int current_index,integer_t partial_sum);
// it sould return 1 when the solution is found and 0 otherwise
// note, however, that you may get a faster function by reducing the number of function arguments (maybe a single pointer to a struct?)
// 

void printBinary(int n, int* b) {
  for(int i = 0; i < n; ++i) {
    printf("%d", b[i]);
  }
  printf("\n");
}

struct bruteForceData {
  int n;
  integer_t* p;
  integer_t desiredSum;
  int nextIndex;
  integer_t partialSum;
  int* b;
};

int bruteForce(int n, integer_t p[n], integer_t desiredSum, int nextIndex, integer_t partialSum, int* b) { // to improve - arguments need to be a pointer to a struct
  // trivial cases
  if(desiredSum == partialSum) {
    for(int i = nextIndex; i < n; ++i) { b[i] = 0;}
    return 1;
  }
  
  if(nextIndex == n) {
    return 0;
  }

  // set next bit to zero
  b[nextIndex] = 0;
  int result = bruteForce(n, p, desiredSum, nextIndex + 1, partialSum, b);
  if (result == 1) {
    return 1;
  }

  // set next bit to one - no solution found on zero
  b[nextIndex] = 1;
  return bruteForce(n, p, desiredSum, nextIndex + 1, partialSum + p[nextIndex], b);
}

int branchAndBound() { // recursive
  
}

int meetInTheMiddle() { // non-recursive

}

//
// main program
//

int main(void) {
  fprintf(stderr,"Program configuration:\n");
  fprintf(stderr,"  min_n ....... %d\n",min_n);
  fprintf(stderr,"  max_n ....... %d\n",max_n);
  fprintf(stderr,"  n_sums ...... %d\n",n_sums);
  fprintf(stderr,"  n_problems .. %d\n",n_problems);
  fprintf(stderr,"  integer_t ... %d bits\n",8 * (int)sizeof(integer_t));
  //
  // place your code here
  //

  printf("\nTesting... \n");
  integer_t array[] = {1, 3, 5, 7, 9};
  int b[5];
  int result = bruteForce(5, array, 12, 0, 0, b);
  printBinary(5, b);
  printf("Result: %d\n", result);
  return 0;
}