#include <stdio.h>
#include <stdlib.h>

/* Percent Function
* Purpose: Prints the string "One half is 50%".
* Input: None
* Output: None
*/
void percent() {
    char string[] = "One half is 50%";
    printf("%s\n", string);
}

/* Subtraction Function
* Purpose: Prints the difference between two given intergers.
* Input: None
* Output: None
*/
void subtraction() {
    int int1 = 10;
    int int2 = 3;
    printf("The difference between %d and %d is %d\n", int1, int2, int1-int2);
}


/* Division Function
* Purpose: Prints the quotient between two given floats.
* Input: None
* Output: None
*/
void division() {
    float float1 = 1;
    float float2 = 3;
    printf("%f / %f is %f\n", float1, float2, float1/float2);
}

/* Main Function
* Purpose: Controls program, runs all three printing functions.
* Input: None
* Output: Return Exit Status
*/
int main (int argc, char **argv)
{
    percent();
    subtraction();
    division();
    return EXIT_SUCCESS;
}

