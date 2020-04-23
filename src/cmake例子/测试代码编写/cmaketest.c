#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    int a = atof(argv[1]);
    int b = atoi(argv[2]);
    printf("results is %i", a + b);
}