#include <stdio.h>
#include "mylib.h"

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

