#include <stdio.h>

int global_array[1000] = {255};

int function() {
    int local_array1[1000];
    int local_array2[1000] = {255};
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
