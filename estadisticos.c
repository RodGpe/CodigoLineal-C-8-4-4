#include <stdio.h>
#include <stdlib.h>

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
    int erroresPeso[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int erroresPesoX_Xdeco[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    while ((c = fgetc(fpCodificados)) != EOF)
    {
        r = fgetc(fpRecibidos);
        d = fgetc(fpDecodificados);
        diferenciaX_Xprima = c ^ r;
        diferenciaX_Xdeco= c ^ d;
        pesoHamming(diferenciaX_Xprima);
        pesoHamming(diferenciaX_Xdeco);
        erroresPeso[pesoHamming(diferenciaX_Xprima)]++;
        erroresPesoX_Xdeco[pesoHamming(diferenciaX_Xdeco)]++;
    }
    printf("%d\n", erroresPeso[0]);
    printf("%d\n", erroresPeso[1]);
    printf("%d\n", erroresPeso[2]);
    printf("%d\n", erroresPeso[3]);
    printf("%d\n", erroresPeso[4]);
    printf("%d\n", erroresPeso[5]);
    printf("%d\n", erroresPeso[6]);
    printf("%d\n", erroresPeso[7]);
    printf("%d\n", erroresPeso[8]);
    printf("-----------------\n");
    printf("%d\n", erroresPesoX_Xdeco[0]);
    printf("%d\n", erroresPesoX_Xdeco[1]);
    printf("%d\n", erroresPesoX_Xdeco[2]);
    printf("%d\n", erroresPesoX_Xdeco[3]);
    printf("%d\n", erroresPesoX_Xdeco[4]);
    printf("%d\n", erroresPesoX_Xdeco[5]);
    printf("%d\n", erroresPesoX_Xdeco[6]);
    printf("%d\n", erroresPesoX_Xdeco[7]);
    
    fclose(fpCodificados);
    fclose(fpRecibidos);
    fclose(fpDecodificados);

    //  EMPIEZA EL CODIGO PARA EL ESTADISTICO EN LOS BITS UNICAMENTE DEL MENSAJE
}
