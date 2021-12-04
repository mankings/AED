#include <math.h>
#include <stdio.h>

void do_it(int N)
{
  int i;

  printf(" n cos(n) sin(n)\n");
  printf("-- ------ ------\n");
  for(i = 1;i <= N;i++)
    printf("%2d %1.4f %1.4f\n",i,cos(i*(M_PI/180)),sin(i*(M_PI/180)));
}

int main(void)
{
  do_it(90);
  return 0;
}