#include <stdio.h>
#include <stdlib.h>

int large_function() {
     int arr[2047];
     int another_arr[4095];
     int biiiiig_arr[8191];
     return 0;
}

main() { 
     int i;
     printf("The stack top is near %p\n", &i);
   
     printf("Declaring large local arrays...\n"); 
     large_function();
 
     int j;
     printf("The stack top is near %p\n", &j);
     return 0;
}
