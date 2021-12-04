//
// Tomás Oliveira e Silva, AED, October 2021
//
// list all command line arguments
//

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[argc]) {
  for(int i = 0;i < argc;i++)
    if(argv[i] == "0" || atoi(argv[i]) != 0) {
      printf("argv[%2d] = \"%s\", int value = %2d\n",i,argv[i], atoi(argv[i]));
    } else {
      printf("argv[%2d] = \"%s\"\n",i,argv[i]);
    }
  return 0;
}