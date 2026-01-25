#include<stdio.h>
#include<stdlib.h>

int* array = {0xD, 0xC0, 0xB00, 0xA000};
int main() {
    return Sum(array, 4);
}

int Sum(int* start, int count) {
    int sum = 0;
    while (count) {
        sum += *start;
        start++;
        count--;
    }
    return sum;
}