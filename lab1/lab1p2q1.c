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
* Purpose: Prints the difference between to given intergers.
* Input: None
* Output: None
*/
void subtraction() {
    int n = 10;
    int m = 3;
    printf("The difference between %d and %d is %d\n", n, m, n-m);

}

void division() {
    float x = 1;
    float y = 3;
    printf("%f / %f is %f\n", x, y, x/y);

}

int main (int argc, char **argv)
{
    percent();
    subtraction();
    division();
    return EXIT_SUCCESS;
}

