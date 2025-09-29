#include <stdlib.h>
#include <stdio.h>


void sum() {
    int num1, num2;
    printf("Give two integers: ");
    scanf("%d%d", &num1, &num2);
    printf("You entered %d and %d, their sum is: %d \n", num1, num2, num1+num2);
}
void product() {
    float num1, num2;
    printf("Give two floats: ");
    scanf("%f%f", &num1, &num2);
    printf("You entered %f and %f, their product is: %f \n", num1, num2, num1*num2);
}

void repeat(){
    char word[100];
    printf("Give a word: ");
    scanf("%s", word);
    printf("%s %s \n", word, word);
}

int main (void) {
    sum();
    product();
    repeat();
}
