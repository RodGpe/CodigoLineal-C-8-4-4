#include <stdio.h>
#include <stdlib.h>

#define N 8

unsigned char H[4] = {0xff, 0x78, 0xb4, 0xd2};
unsigned char Errores[16] = {
    0x00, //0
    0x03, //1
    0x05, //2
    0x06, //3
    0x09, //4
    0x0a, //5
    0x0c, //6
    0x11, //7
    0x01, //8
    0x02, //9
    0x04, //a
    0x80, //b
    0x08, //c
    0x40, //d
    0x20, //e
    0x10  //f
};

void calcularSindrome(unsigned char H[4])
{
    unsigned int suma = 0;
    unsigned char sindrome = 0;
    unsigned char palabra = 0x1f; //PC 0001-1110 mas el error e = 0000-0001
    //unsigned char palabra = 0x2f; //PC 0010-1101 mas el error e = 0000-0010
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            unsigned int tempH = (H[i] >> j) & 0x01;
            unsigned int tempP = (palabra >> j) & 0x01;
            suma = suma ^ (tempH * tempP);
        }
        sindrome = (suma << 3-i) ^ sindrome;
        printf("%x", suma);
        suma = 0;
    }
    printf(" <- sindrome con bit mas significativo hasta la derecha \n");
    if (sindrome != 0)
    {
        palabra= palabra ^ Errores[sindrome];
        printf("%x ", sindrome);
        printf("%x", palabra);
    }else
    {
        printf("%x", palabra);
    }
    
    
}

main(argc, argv) int argc;
char *argv[];
{
    calcularSindrome(H);
    //int i, c, invp, e;
    //
    //srand((int) getpid());
    //invp = atoi(argv[1]);
    //while ((c=getchar()) != EOF){
    //    e = 0 ;
    //    for (i = 0; i < N; i++)
    //        if(!(rand()%invp)) e ^= (1<<i);
    //    putchar(c^e);
    //}
    //printf("\n\n\n hi");
    ////return;
}
