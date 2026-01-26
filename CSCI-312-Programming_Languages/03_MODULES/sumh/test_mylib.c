#include <assert.h>
#include <stdio.h>
#include "mylib.h"

static void test_cumulative_sum()
{
    long actual, expected;

    // Assemble
    expected = 1;
    // Act
    actual = cumulative_sum(1);
    // Assert
    assert(actual == expected);
    printf(".");

    // Assemble
    expected = 3;
    // Act
    actual = cumulative_sum(2);
    // Assert
    assert(actual == expected);
    printf(".");

    // Assemble
    expected = 55;
    // Act
    actual = cumulative_sum(10);
    // Assert
    assert(actual == expected);
    printf(".");
}

int main(int argc, char *argv[])
{
    test_cumulative_sum();
    printf("\nAll tests passed!\n");
    return 0;
}
