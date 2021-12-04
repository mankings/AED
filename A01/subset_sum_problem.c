//
// AED, November 2021
//
// Solution of the first practical assignement (subset sum problem)
//
// 103341 - João Miguel Matos
// 103470 - Filipe Antão
//

#if __STDC_VERSION__ < 199901L
#error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
#define STUDENT_H_FILE "000000.h"
#endif

//
// include files
//

#include "../P02/elapsed_time.h"
#include <stdio.h>
#include <stdlib.h>
#include STUDENT_H_FILE

//
// custom data types
//
// the STUDENT_H_FILE defines the following constants and data types
//
//   #define min_n       24                   --- the smallest n value we will
//   handle #define max_n       57                   --- the largest n value we
//   will handle #define n_sums      20                   --- the number of sums
//   for each n value #define n_problems  (max_n - min_n + 1)  --- the number of
//   n values
//
//   typedef unsigned long long integer_t;    ---  64-bit unsigned integer
//   typedef struct
//   {
//     int n;                                 --- number of elements of the set
//     (for a valid problem, min_n <= n <= max_n) integer_t p[max_n]; --- the
//     elements of the set, already sorted in increasing order (only the first n
//     elements are used) integer_t sums[n_sums];                --- several
//     sums (problem: for each sum find the corresponding subset)
//   }
//   subset_sum_problem_data_t;               --- weights p[] and sums for a
//   given value of n
//
//   subset_sum_problem_data_t all_subset_sum_problems[n_problems]; --- // the
//   problems
//

//
// place your code here
//
// possible function prototype for a recursive brute-force function:
//   int brute_force(int n,integer_t p[n],int desired_sum,int
//   current_index,integer_t partial_sum);
// it sould return 1 when the solution is found and 0 otherwise
// note, however, that you may get a faster function by reducing the number of
// function arguments (maybe a single pointer to a struct?)
//

// auxiliary functions
void printBinary(int n, int *b) {
    for (int i = 0; i < n; ++i) {
        printf("%d", b[i]);
    }
    printf("\n");
}

integer_t sumAll(int n, integer_t p[n]) {
    integer_t sum = 0;
    for (int i = 0; i < n; i++) {
        sum += p[i];
    }
    return sum;
}

// 1st solution code
struct bruteForceData {
    int n;
    integer_t *p;
    integer_t desiredSum;
    int nextIndex;
    integer_t partialSum;
    int *b;
};
typedef struct bruteForceData BFData;

int bruteForce(BFData *data) {
    // trivial cases
    if (data->desiredSum == data->partialSum) {
        for (int i = data->nextIndex; i < data->n; ++i) {
            data->b[i] = 0;
        }
        return 1;
    }

    if (data->nextIndex == data->n) {
        return 0;
    }

    // set next bit to zero
    data->b[data->nextIndex] = 0;

    BFData newData = {data->n,          data->p,
                      data->desiredSum, data->nextIndex + 1,
                      data->partialSum, data->b};
    int result = bruteForce(&newData);
    if (result == 1) {
        return 1;
    }

    // set next bit to one - no solution found on zero
    data->b[data->nextIndex] = 1;
    newData.partialSum = data->partialSum + data->p[data->nextIndex];
    return bruteForce(&newData);
}

// 2nd solution code
struct branchAndBoundData {
    int n;
    integer_t *p;
    integer_t desiredSum;
    int nextIndex;
    integer_t partialSum;
    integer_t remainingSum;
    int *b;
};
typedef struct branchAndBoundData BBData;

int branchAndBound(BBData *data) {
    // trivial cases
    if (data->desiredSum == data->partialSum) {
        for (int i = data->nextIndex; i < data->n; ++i) {
            data->b[i] = 0;
        }
        return 1;
    }

    if (data->nextIndex == data->n) {
        return 0;
    }

    if ((data->partialSum + data->remainingSum) <= data->desiredSum) {
        return 0;
    }

    if (data->partialSum > data->desiredSum) {
        return 0;
    }

    // set next bit to zero
    data->b[data->nextIndex] = 0;

    BFData newData = {data->n,          data->p,
                      data->desiredSum, data->nextIndex + 1,
                      data->partialSum, data->b};
    int result = bruteForce(&newData);
    if (result == 1) {
        return 1;
    }

    // set next bit to one - no solution found on zero
    data->b[data->nextIndex] = 1;
    newData.partialSum = data->partialSum + data->p[data->nextIndex];
    return bruteForce(&newData);
    return 0;
}

// 3rd solution code
int meetInTheMiddle() { // non-recursive
    // 1st split and copy
    //
    return 0;
}

//
// main program
//

int main(void) {
    fprintf(stderr, "Program configuration:\n");
    fprintf(stderr, "  min_n ....... %d\n", min_n);
    fprintf(stderr, "  max_n ....... %d\n", max_n);
    fprintf(stderr, "  n_sums ...... %d\n", n_sums);
    fprintf(stderr, "  n_problems .. %d\n", n_problems);
    fprintf(stderr, "  integer_t ... %d bits\n", 8 * (int)sizeof(integer_t));
    //
    // place your code here
    //
    int i, result;
    printf("\nTesting... \n");

    int n;
    integer_t *p, *sums;
    

    printf("\nBruteForce function\n");
    n = all_subset_sum_problems[0].n;
    p = all_subset_sum_problems[0].p;
    sums = all_subset_sum_problems[0].sums;
    int bf[n];
    for (i = 0; i < 20; ++i) {
        BFData BFTest = {n, p, sums[i], 0, 0, bf};
        result = bruteForce(&BFTest);
        printf("%lld ", sums[i]);
        printBinary(n, BFTest.b);
        printf("Result 1: %d\n", result);
    }

    printf("\nBranchAndBound function\n");
    n = all_subset_sum_problems[0].n;
    p = all_subset_sum_problems[0].p;
    sums = all_subset_sum_problems[0].sums;
    int cbf[n];
    for (i = 0; i < 20; ++i) {
      BBData BBTest = {n, p, sums[i], 0, 0, sumAll(n, p), cbf};
      result = branchAndBound(&BBTest);
      printf("%lld ", sums[i]);
      printBinary(n, BBTest.b);
      printf("Result 2: %d\n", result);
    }

    return 0;
}