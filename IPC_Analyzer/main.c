//biblio standar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//biblio
#include "funciones.h"

//define's
#define TAM 10 //temporal

void imprimirRegistros(DIVISION*);

void mostrarTxt(FILE* arch);

int main()
{
    FILE *archTxt = fopen("../Data/serie_ipc_divisiones(test).csv","rt");
    FILE *archTxt2 = fopen("../Data/serie_ipc_divisiones2(test).csv","w+t"); //nuevo arch txt2.0
    if(!archTxt){
        puts("No se pudo abrir el archivo (.txt): serie_ipc_divisiones(test)");
        exit(1);
    }
    if(!archTxt2){
        puts("No se pudo crear el archivo (.txt): serie_ipc_divisiones2(test)");
        fclose(archTxt);
        exit(1);
    }

    divisionesArchTextATxt(archTxt, archTxt2);

    mostrarTxt(archTxt2);

    menu_ipc(archTxt2);

    fclose(archTxt2);
    fclose(archTxt);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrarTxt(FILE* arch)
{
    rewind(arch);

    char linea[512];
    int i = 1;

    puts("------------------------------------------------------------\n");
    while (fgets(linea, sizeof(linea), arch))
        printf("Linea %d: %s", i++, linea);
    puts("------------------------------------------------------------\n");

    system("pause");
}

