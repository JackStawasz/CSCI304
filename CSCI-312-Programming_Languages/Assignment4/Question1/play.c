#include <stdio.h>

char ga[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void one(char ca[]) {
	printf("%p\n", &ca);
	printf("%p\n", &(ca[0]));
	printf("%p\n", &(ca[1]));
}

void two(char pa[]) {
	printf("%p\n", &pa);
	printf("%p\n", &(pa[0]));
	printf("%p\n", &(pa[1]));
	printf("%p\n", ++pa);
}

int main() {
	// Part 1
	char ca[2];
	one(ca);
	
	// Part 2
	char *pa;
	two(pa);
	
	// Part 3
	one(ga);
	two(ga);

	// Part 4
	printf("%p\n", &ga);
	printf("%p\n", &(ga[0])); 	
	printf("%p\n", &(ga[1]));

 	return 0;
}
