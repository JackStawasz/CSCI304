// Compute sum of consecutive integers from 1 to N (inclusive)

#include <stdio.h>

long cumulative_sum(int N) {
	long accumulator;
	if (N==1) {
		accumulator = 1;
	} else {
		accumulator = N + cumulative_sum(N-1);
	}

	return accumulator;
//	long accumulator = 0;
//	for (int i=1; i<=N; i++) {
//		accumulator += i;
//	}
//
//	return accumulator;
}

int main(int argc, char *argv[]) {
	int N;
	long result;

	// Ask for number
	printf("Enter an integer: ");
	scanf("%d", &N);

	// Compute result
	result = cumulative_sum(N);

	// Display result
	printf("The cumulative sum from 1 to %d is %ld\n", N, result);
	return 0;
}
