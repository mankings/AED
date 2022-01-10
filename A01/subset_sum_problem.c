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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "elapsed_time.h"
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
void printIntArray(int n, int *b) {  // prints an int array
    for (int i = 0; i < n; ++i) {
        printf("%d", b[i]);
    }
    printf("\n");
}

void printTArray(int n, integer_t *b) {  // prints a integer_t array
    for (int i = 0; i < n; ++i) {
        printf("%llu\n", b[i]);
    }
}

void printCharArray(int n, char *b) {  // prints a char array
    for (int i = 0; i < n; ++i) {
        printf("%c", b[i]);
    }
    printf("\n");
}

integer_t sumAll(int n, integer_t p[n]) {  //
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

    BFData newData = {data->n, data->p,
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

    if ((data->partialSum + data->remainingSum) < data->desiredSum) {
        return 0;
    }

    if (data->partialSum > data->desiredSum) {
        return 0;
    }

    // set next bit to zero
    data->b[data->nextIndex] = 0;

    BBData newData = {data->n, data->p, data->desiredSum, data->nextIndex + 1, data->partialSum, data->remainingSum - data->p[data->nextIndex + 1], data->b};

    int result = branchAndBound(&newData);
    if (result == 1) {
        return 1;
    }

    // set next bit to one - no solution found on zero
    data->b[data->nextIndex] = 1;
    newData.partialSum = data->partialSum + data->p[data->nextIndex];
    return branchAndBound(&newData);
    return 0;
}

// 3rd solution code
void swap(int x, int y, integer_t array[], char **bin) {
    //swap two integer_t elements
    integer_t temp = array[x];
    array[x] = array[y];
    array[y] = temp;

    //swap corresponding binary entries
    char *tmp = bin[x];
    bin[x] = bin[y];
    bin[y] = tmp;
}

int partition(integer_t array[], int low, int high, char **bin) {
    // select the rightmost element as pivot
    integer_t pivot = array[high];

    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(i, j, array, bin);
        }
    }

    // swap the pivot element with the greater element at i
    swap(i + 1, high, array, bin);

    // return the partition point
    return (i + 1);
}

void quickSort(integer_t array[], int low, int high, char **bin) {  // Complexidade O(n log n)
    if (low < high) {
        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, low, high, bin);

        // recursive call on the left of pivot
        quickSort(array, low, pi - 1, bin);

        // recursive call on the right of pivot
        quickSort(array, pi + 1, high, bin);
    }
}

int meetInTheMiddle(int n, integer_t *p, integer_t desiredSum, char *bin) {  // non-recursive
    int high = ceil(n / 2.0f), low = floor(n / 2.0f);
    int aSize = (int)pow(2, high), bSize = (int)pow(2, low);
    integer_t *a = (integer_t *)malloc(aSize * sizeof(integer_t)), *b = (integer_t *)malloc(bSize * sizeof(integer_t));
    integer_t sum;
    char **aBin = (char **)malloc(aSize * sizeof(char *)), **bBin = (char **)malloc(bSize * sizeof(char *));
    int i, j, k;

    // get all subset sums
    for (i = 0; i < aSize; ++i) {
        sum = 0;
        aBin[i] = (char *)malloc(high * sizeof(char));
        for (j = 0; j < high; ++j) {
            if (i & (1 << j)) {
                sum += p[j];
                aBin[i][j] = '1';
            } else {
                aBin[i][j] = '0';
            }
        }
        a[i] = sum;
    }

    for (i = 0; i < bSize; ++i) {
        sum = 0;
        bBin[i] = (char *)malloc(low * sizeof(char));
        for (j = 0; j < low; ++j) {
            if (i & (1 << j)) {
                sum += p[j + high];
                bBin[i][j] = '1';
            } else {
                bBin[i][j] = '0';
            }
        }
        b[i] = sum;
    }

    // sort them and corresponding binary arrays
    quickSort(a, 0, aSize - 1, aBin);
    quickSort(b, 0, bSize - 1, bBin);

    // find solution
    i = 0;
    j = bSize - 1;
    while (i < aSize || j >= 0) {
        sum = a[i] + b[j];
        if (sum < desiredSum) {
            i++;
        } else if (sum > desiredSum) {
            j--;
        } else {  // found the solution
            for (k = 0; k < high; ++k) {
                bin[k] = aBin[i][k];
            }
            for (k = 0; k < low; ++k) {
                bin[k + high] = bBin[j][k];
            }

            for (int p = 0; p < aSize; ++p) free(aBin[p]);
            for (int p = 0; p < bSize; ++p) free(bBin[p]);
            free(a);
            free(b);
            free(aBin);
            free(bBin);

            return 1;
        }
    }
    
    for (int p = 0; p < aSize; ++p) free(aBin[p]);
    for (int p = 0; p < bSize; ++p) free(bBin[p]);
    free(a);
    free(b);
    free(aBin);
    free(bBin);

    return 0;  // array went out of bounds; didn't find a solution
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
    int i, j, result;
    printf("\nTesting...\n");
    int n;
    integer_t *p, *sums;

    /*
    for (i = min_n; i <= 0; ++i) {
        n = all_subset_sum_problems[i].n;
        p = all_subset_sum_problems[i].p;
        sums = all_subset_sum_problems[i].sums;

        int bf[n];
        for (j = 0; j < n_sums; ++j) {
            BFData BFTest = {n, p, sums[j], 0, 0, bf};
            result = bruteForce(&BFTest);
        }
    }

    for (i = min_n; i <= 0; ++i) {
        n = all_subset_sum_problems[i].n;
        p = all_subset_sum_problems[i].p;
        sums = all_subset_sum_problems[i].sums;

        int cbf[n];
        for (j = 0; j < n_sums; ++j) {
            BBData BBTest = {n, p, sums[j], 0, 0, sumAll(n, p, 0), cbf};
            result = branchAndBound(&BBTest);
        }
    }
    */

    for (i = 0; i < n_problems; ++i) {
        n = all_subset_sum_problems[i].n;
        p = all_subset_sum_problems[i].p;
        sums = all_subset_sum_problems[i].sums;

        char cbf[n];
        for (j = 0; j < n_sums; ++j) {
            result = meetInTheMiddle(n, p, sums[j], cbf);
            printf("result: %d\n", result);
            printCharArray(n, cbf);
        }

        printf("%d done\n \n", n);
    }

    /*
    n = all_subset_sum_problems[26].n;
    p = all_subset_sum_problems[26].p;
    sums = all_subset_sum_problems[26].sums;

    int cbf[n];

    for (j = 0; j < n_sums; ++j) {
        integer_t sum = sums[j];
        result = meetInTheMiddle(n, p, sum, cbf);
        printf("result: %d\n", result);
        printIntArray(n, cbf);
    }
    printf("%d done\n \n", n);
*/
    return 0;
}
