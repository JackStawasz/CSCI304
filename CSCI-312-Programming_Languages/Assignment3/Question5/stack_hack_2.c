#include <stdio.h>
#include <stdlib.h>

int global_var = 255;

int text_function() {
     return 0;
}

main() { 
     int i;
     int *heap_pointer = malloc(sizeof(int));
     printf("The stack top is near %p\n", &i);
     printf("The data segment is near %p\n", &global_var);
     printf("The text segment is near %p\n", text_function);
     printf("The heap is near %p\n", heap_pointer);
     return 0;
}
