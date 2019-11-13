#include <stdio.h>
#include <stdlib.h>

#define N 8
#define TRUE 1
#define FALSE 0;

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

unsigned char decodificar(unsigned char H[4], unsigned char palabra) //no es un buen nombre porque sí corrigue
{
    unsigned int suma = 0;
    unsigned char sindrome = 0;
    //unsigned char palabra = 0x1f; //PC 0001-1110 mas el error e = 0000-0001
    //unsigned char palabra = 0x2f; //PC 0010-1101 mas el error e = 0000-0010
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            unsigned int tempH = (H[i] >> j) & 0x01;
            unsigned int tempP = (palabra >> j) & 0x01;
            suma = suma ^ (tempH * tempP);
        }
        sindrome = (suma << 3 - i) ^ sindrome;
        //printf("%x", suma);
        suma = 0;
    }
    //printf(" <- sindrome con bit mas significativo hasta la derecha \n");
    if (sindrome != 0)
    {
        palabra = palabra ^ Errores[sindrome];
        //printf("%x", sindrome);
        printf("%x ", palabra);
    }
    else
    {
        printf("%x", palabra);
    }
    unsigned char palabraCorregida= palabra;
    return palabraCorregida;
}

main(argc, argv) int argc;
char *argv[];
{
    decodificar(H, 0x1f);
    FILE *fp;
    int c = 0x00;
    unsigned char palabraY = 0;
    unsigned char primerMitad = TRUE; //empieza en uno porque siempre se recibe primero la primera mitad
    fp = fopen("./salida.txt", "w");
    if (fp == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    while ((c = getchar()) != EOF)
    {
        c = decodificar(H,c);
        //    putchar(c);
        if (primerMitad)
        {
            palabraY = ((c >> 4) & 0x0f) ^ palabraY;
            primerMitad = FALSE;
        }
        else
        {
            palabraY = (c & 0xf0) ^ palabraY;
            primerMitad = TRUE;
            //printf("%x", palabraY);
            fprintf(fp, "%c", palabraY);
            palabraY = 0;
        }
    }
    fclose(fp);
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
