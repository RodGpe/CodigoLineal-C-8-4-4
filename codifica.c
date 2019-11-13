#include <stdio.h>
#include <stdlib.h>

unsigned char PC[16] = {
    0x00,
    0x1e,
    0x2d,
    0x33,
    0x4b,
    0x55,
    0x66,
    0x78,
    0x87,
    0x99,
    0xaa,
    0xb4,
    0xcc,
    0xd2,
    0xe1,
    0xff,
};

main(argc, argv) int argc;
char *argv[];
{
    //printf("aloo");
    FILE *fp;
    //------------para escribir vectores codificados en un archivo
    FILE *fpV;
    fpV = fopen("./VectoresCodificados.txt", "w");
    if (fpV == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    //-----------fin para el uso del archivo
    int c;
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("Error al abrir el archivo %s\n", argv[1]);
        return;
    }
    while ((c = fgetc(fp)) != EOF)
    {
        putchar(PC[c & 15]);
        fprintf(fpV, "%c", PC[c & 15]); //para escribir en el archivo de vectores
        putchar(PC[(c >> 4) & 15]);
        fprintf(fpV, "%c", PC[(c >> 4) & 15]); //para escribir en el archivo de vectores 
    }
    fclose(fp);
    fclose(fpV);
}