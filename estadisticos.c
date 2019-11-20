#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int pesoHamming(unsigned int n)
{
    unsigned int c;
    for (c = 0; n; n >>= 1)
    {
        c += n & 1;
    }
    return c;
}

main(argc, argv) int argc;
char *argv[];
{
    FILE *fpCodificados;
    if ((fpCodificados = fopen(argv[1], "r")) == NULL)
    {
        printf("Error al abrir el archivo %s\n", argv[1]);
        return;
    }
    FILE *fpRecibidos;
    if ((fpRecibidos = fopen(argv[2], "r")) == NULL)
    {
        printf("Error al abrir el archivo %s\n", argv[2]);
        return;
    }
    FILE *fpDecodificados;
    if ((fpDecodificados = fopen(argv[3], "r")) == NULL)
    {
        printf("Error al abrir el archivo %s\n", argv[3]);
        return;
    }
    printf("hsta aqui se abrieron bien los archivos \n");
    //unsigned char c = 0;
    unsigned int c = 0;
    unsigned int r = 0;
    unsigned int d = 0;
    unsigned int diferenciaX_Xprima = 0;
    unsigned int diferenciaX_Xdeco = 0;
    int erroresPesoX_Xprima[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int erroresPesoX_Xdeco[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    //---para las A----
    unsigned int cA = 0;
    unsigned int rA = 0;
    unsigned int dA = 0;
    unsigned int diferenciaA_Aprima = 0;
    unsigned int diferenciaA_Adeco = 0;
    int erroresPesoA_Aprima[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int erroresPesoA_Adeco[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    //---fin de para las A---

    while ((c = fgetc(fpCodificados)) != EOF)
    {
        cA = (c >> 4) & 0x0f;
        r = fgetc(fpRecibidos);
        rA = (r >> 4) & 0x0f;
        d = fgetc(fpDecodificados);
        dA = (d >> 4) & 0xff;
        diferenciaX_Xprima = c ^ r;
        diferenciaX_Xdeco = c ^ d;
        diferenciaA_Aprima = cA ^ rA;
        diferenciaA_Adeco = cA ^ dA;
        //pesoHamming(diferenciaX_Xprima);
        //pesoHamming(diferenciaX_Xdeco);
        //pesoHamming(diferenciaA_Aprima);
        //pesoHamming(diferenciaA_Adeco);
        erroresPesoX_Xprima[pesoHamming(diferenciaX_Xprima)]++;
        erroresPesoX_Xdeco[pesoHamming(diferenciaX_Xdeco)]++;

        erroresPesoA_Aprima[pesoHamming(diferenciaA_Aprima)]++;
        erroresPesoA_Adeco[pesoHamming(diferenciaA_Adeco)]++;
    }
    printf("\n___(X-X')____'\n");
    printf("%d\n", erroresPesoX_Xprima[0]);
    printf("%d\n", erroresPesoX_Xprima[1]);
    printf("%d\n", erroresPesoX_Xprima[2]);
    printf("%d\n", erroresPesoX_Xprima[3]);
    printf("%d\n", erroresPesoX_Xprima[4]);
    printf("%d\n", erroresPesoX_Xprima[5]);
    printf("%d\n", erroresPesoX_Xprima[6]);
    printf("%d\n", erroresPesoX_Xprima[7]);
    printf("%d\n", erroresPesoX_Xprima[8]);
    printf("___(X-X^)____\n");
    printf("%d\n", erroresPesoX_Xdeco[0]);
    printf("%d\n", erroresPesoX_Xdeco[1]);
    printf("%d\n", erroresPesoX_Xdeco[2]);
    printf("%d\n", erroresPesoX_Xdeco[3]);
    printf("%d\n", erroresPesoX_Xdeco[4]);
    printf("%d\n", erroresPesoX_Xdeco[5]);
    printf("%d\n", erroresPesoX_Xdeco[6]);
    printf("%d\n", erroresPesoX_Xdeco[7]);
    printf("%d\n", erroresPesoX_Xdeco[8]);
    printf("___(A-A')____\n");
    printf("%d\n", erroresPesoA_Aprima[0]);
    printf("%d\n", erroresPesoA_Aprima[1]);
    printf("%d\n", erroresPesoA_Aprima[2]);
    printf("%d\n", erroresPesoA_Aprima[3]);
    printf("%d\n", erroresPesoA_Aprima[4]);
    printf("%d\n", erroresPesoA_Aprima[5]);
    printf("%d\n", erroresPesoA_Aprima[6]);
    printf("%d\n", erroresPesoA_Aprima[7]);
    printf("%d\n", erroresPesoA_Aprima[8]);
    printf("___(A-A^)____\n");
    printf("%d\n", erroresPesoA_Adeco[0]);
    printf("%d\n", erroresPesoA_Adeco[1]);
    printf("%d\n", erroresPesoA_Adeco[2]);
    printf("%d\n", erroresPesoA_Adeco[3]);
    printf("%d\n", erroresPesoA_Adeco[4]);
    printf("%d\n", erroresPesoA_Adeco[5]);
    printf("%d\n", erroresPesoA_Adeco[6]);
    printf("%d\n", erroresPesoA_Adeco[7]);
    printf("%d\n", erroresPesoA_Adeco[8]);

    float bitsEnError = 0;
    bitsEnError =
        erroresPesoX_Xprima[1] * 1 +
        erroresPesoX_Xprima[2] * 2 +
        erroresPesoX_Xprima[3] * 3 +
        erroresPesoX_Xprima[4] * 4 +
        erroresPesoX_Xprima[5] * 5 +
        erroresPesoX_Xprima[6] * 6 +
        erroresPesoX_Xprima[7] * 7 +
        erroresPesoX_Xprima[8] * 8;

    float bitsTotales = 0;
    bitsTotales =
        erroresPesoX_Xprima[0] * 8 +
        erroresPesoX_Xprima[1] * 8 +
        erroresPesoX_Xprima[2] * 8 +
        erroresPesoX_Xprima[3] * 8 +
        erroresPesoX_Xprima[4] * 8 +
        erroresPesoX_Xprima[5] * 8 +
        erroresPesoX_Xprima[6] * 8 +
        erroresPesoX_Xprima[7] * 8 +
        erroresPesoX_Xprima[8] * 8;

    float symError = 0;
    symError =
        erroresPesoA_Adeco[1] * 1 +
        erroresPesoA_Adeco[2] * 2 +
        erroresPesoA_Adeco[3] * 3 +
        erroresPesoA_Adeco[4] * 4 +
        erroresPesoA_Adeco[5] * 5 +
        erroresPesoA_Adeco[6] * 6 +
        erroresPesoA_Adeco[7] * 7 +
        erroresPesoA_Adeco[8] * 8;

    printf("\nBits totales = %f", bitsTotales);
    printf("\nBits en error = %f", bitsEnError);
    printf("\nP = %f / %f  =%f",bitsEnError, bitsTotales, (bitsEnError / bitsTotales));
    printf("\nPerr = %f / %f = %f",(float)erroresPesoX_Xdeco[4],(float)(erroresPesoX_Xdeco[0] + erroresPesoX_Xdeco[4]), ((float)erroresPesoX_Xdeco[4] / (float)(erroresPesoX_Xdeco[0] + erroresPesoX_Xdeco[4])));
    printf("\nPsym = %f / %f = %f",symError, (bitsTotales/2), (symError/(bitsTotales/2)));

    fclose(fpCodificados);
    fclose(fpRecibidos);
    fclose(fpDecodificados);

    //  EMPIEZA EL CODIGO PARA EL ESTADISTICO EN LOS BITS UNICAMENTE DEL MENSAJE
}
