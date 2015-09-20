#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
	
	int i=0;

	for(i=0;i<argc;i++){

		printf("\ncmd line arg(%d) is: %s, \tlength %d\n",i,argv[i],(int)strlen(argv[i]));
	}
	
  return 0;
}