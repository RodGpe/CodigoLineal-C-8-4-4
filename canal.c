#include <stdio.h>
#include <stdlib.h>

#define N 8

main(argc, argv)
int argc;       
char  *argv[];
{
    int i, c, invp, e;

    srand((int) getpid());
    invp = atoi(argv[1]);
    while ((c=getchar()) != EOF){
        e = 0 ;
        for (i = 0; i < N; i++)
            if(!(rand()%invp)) e ^= (1<<i);
        putchar(c^e);
    }
    //return;
}