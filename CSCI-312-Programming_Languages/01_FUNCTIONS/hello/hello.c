#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if (argc != 2) {
		fprintf(stderr, "Usage: %s name\n", argv[0]);
	//exit(1);
	return EXIT_FAILURE;
	}
	printf("hello, %s\n", argv[1]);
	return EXIT_SUCCESS;
}

