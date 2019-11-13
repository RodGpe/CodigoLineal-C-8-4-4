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

int pesoHamming(unsigned char n)
{
    unsigned int c;
    for (c = 0; n; n >>= 1)
    {
        c += n & 1;
    }
    return c;
}

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
    unsigned char palabraCorregida = palabra;
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
    //---------para escribir los vectores recividos
    FILE *fpVR;
    fpVR = fopen("./VectoresRecibidos.txt", "w");
    if (fpVR == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    //-------fin para vectores recibidos
    //---------para escribir los vectores DECODIFICADOS
    FILE *fpDEC;
    fpDEC = fopen("./VectoresDecodificados.txt", "w");
    if (fpDEC == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    //-------fin para vectores DECODIFICADOS
    int contadorVectores = 0;
    while ((c = getchar()) != EOF)
    {
        fprintf(fpVR, "%c", c); //para escribir los vectores recibidos
        contadorVectores++;
        c = decodificar(H, c);
        fprintf(fpDEC, "%c", c); //para escribir los vectores decodificados
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
    fclose(fpVR);
    fclose(fpDEC);
    printf(" El numero de vectores  fue : %d \n", contadorVectores);
    //------------pruebas de peso de hammng
    //unsigned char peso = 0x00;
    //unsigned char pesoPrueba = pesoHamming(peso);
    //printf(" peso de hamming es = %d", pesoPrueba);
    //------------fin de pruebas de peso de hamming
    //return;
}
