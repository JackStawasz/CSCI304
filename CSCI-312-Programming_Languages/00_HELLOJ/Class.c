#include <stdio.h>

typedef void (*Method)(char *);

void method(char *name)
{
    printf("hello, %s\n", name);
}

typedef struct class
{
    int field;
    Method method;
} Class;

int main(int argc, char *argv[])
{
    Class object = { 0, method };  // Class object = new_Class(0, &method);
    printf("object.field = %d\n", object.field);
    object.method(argv[1]);
    return 0;
}
