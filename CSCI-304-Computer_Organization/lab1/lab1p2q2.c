#include <stdlib.h>
#include <stdio.h>

/* Sum Function
* Purpose: Prints the sum of two user provided integers.
* Input: None
* Output: None
*/
void sum() {
    int int1, int2;
    printf("Give two integers: ");
    scanf("%d%d", &int1, &int2);
    printf("You entered %d and %d, their sum is: %d \n", int1, int2, int1+int2);
}

/* Product Function
* Purpose: Prints the product of two user provided floats.
* Input: None
* Output: None
*/
void product() {
    float float1, float2;
    printf("Give two floats: ");
    scanf("%f%f", &float1, &float2);
    printf("You entered %f and %f, their product is: %f \n", float1, float2, float1*float2);
}

/* Repeat Function
* Purpose: Prints two copies of a user provided string.
* Input: None
* Output: None
*/
void repeat(){
    char word[100];
    printf("Give a word: ");
    scanf("%s", word);
    printf("%s %s \n", word, word);
}

/* Main Function
* Purpose: Controls program, runs all three printing functions.
* Input: None
* Output: Return Exit Status
*/
int main (void) {
    sum();
    product();
    repeat();
    return EXIT_SUCCESS;
}
