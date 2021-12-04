//
// Tomás Oliveira e Silva, AED, October 2021
//
// the functions for the first exercise of class P.04
// (for a given positive value of n, find a formula for the return value of each function)
//

#include <stdio.h>
#include "elapsed_time.h"

int f1(int n)
{
  int i,r=0;

  for(i = 1;i <= n;i++)
    r += 1; //executed n times - linear
  return r;
}

int f2(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= i;j++)
      r += 1; //executed (n+1)*n/2 times - quadratic
  return r;
}

int f3(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= n;j++)
      r += 1; //executed n*n times - quadratic
  return r;
}

int f4(int n)
{
  int i,r=0;

  for(i = 1;i <= n;i++)
    r += i; //executed n times - linear
  return r;
}

int f5(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = i;j <= n;j++)
      r += 1;
  return r;
}

int f6(int n)
{
  int i,j,r=0;

  for(i = 1;i <= n;i++)
    for(j = 1;j <= i;j++)
      r += j;
  return r;
}

int main(void)
{
  double dt1, dt2, dt3, dt4, dt5, dt6;
  
  printf("%6s %10s %10s %10s %10s %10s %10s\n", "n", "f1", "f2", "f3", "f4", "f5", "f6");
  
  int n;
  for(n = 10; n <= 100000; n *= 10) {
    dt1 = cpu_time();
    f1(n);
    dt1 = cpu_time() - dt1;

    dt2 = cpu_time();
    f2(n);
    dt2 = cpu_time() - dt2;

    dt3 = cpu_time();
    f3(n);
    dt3 = cpu_time() - dt3;

    dt4 = cpu_time();
    f4(n);
    dt4 = cpu_time() - dt4;

    dt5 = cpu_time();
    f5(n);
    dt5 = cpu_time() - dt5;
    
    dt6 = cpu_time();
    f6(n);
    dt6 = cpu_time() - dt6;

    printf("%6d %9.3e %9.3e %9.3e %9.3e %9.3e %9.3e\n", n, dt1, dt2, dt3, dt4, dt5, dt6);
  }
}
