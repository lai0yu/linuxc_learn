#include <stdio.h>


int main(int argc, char *argv[]){
	extern char** environ;
	printf("new process run\n");

	return 0;
}
