//
// Tomás Oliveira e Silva, AED, October 2021
//
// the functions for the first exercise of class P.04
// (for a given positive value of n, find a formula for the return value of each function)
//

#include <stdio.h>
#include "elapsed_time.h"

unsigned int COUNTER;

int f1(int n)
{
  int i,r=0;

  for(i = 1;i <= n;i++) {
    r += 1; //executed n times - linear
    COUNTER++;
  }
  return r;
}

int f2(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= i;j++) {
      r += 1; //executed (n+1)*n/2 times - quadratic
      COUNTER++;
    }
  return r;
}

int f3(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= n;j++) {
      r += 1; //executed n*n times - quadratic
      COUNTER++;
    }
  return r;
}

int f4(int n)
{
  int i,r=0;

  for(i = 1;i <= n;i++) {
    r += i; //executed n times - linear
    COUNTER++;
  }
  return r;
}

int f5(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = i;j <= n;j++) {
      r += 1; //executed (n+1)*n/2 times - quadratic
      COUNTER++;
    }
  return r;
}

int f6(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= i;j++) {
      r += j; //executed (n+1)*n/2 times - quadratic
      COUNTER++;
    }
  return r;
}

int main(void) {
  printf("%2s %4s %4s %4s %4s %4s %4s\n", "n", "f1", "f2", "f3", "f4", "f5", "f6");
  
  int n;
  for(n = 1; n <= 10; n++) {
    printf("%2d", n);
    
    COUNTER = 0;
    f1(n);
    printf(" %4d", COUNTER);

    COUNTER = 0;
    f2(n);
    printf(" %4d", COUNTER);

    COUNTER = 0;
    f3(n);
    printf(" %4d", COUNTER);

    COUNTER = 0;
    f4(n);
    printf(" %4d", COUNTER);

    COUNTER = 0;
    f5(n);
    printf(" %4d", COUNTER);

    COUNTER = 0;
    f6(n);
    printf(" %4d\n", COUNTER);
  }
}
