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

void mostrarBin();

int main()
{

    divisionesArchTextATxt();

    mostrarBin();

    menu_ipc();

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mostrarBin()
{
    FILE* pf = fopen("../Data/serie_ipc_divisiones(test).dat", "rb");
    DIVISION reg;
    int i = 0;

    puts("------------------------------------------------------------\n");
    while (fread(&reg, sizeof(DIVISION), 1, pf) == 1) {
        printf("Registro %d:\n", i++);
        printf("  Codigo: %s\n", reg.cod);
        printf("  Descripcion: %s\n", reg.descrip);
        printf("  Clasificacion: %s\n", reg.clasif);
        printf("  ind_ipc: %.2f\n", reg.ind_ipc);
        printf("  v_m_ipc: %.2f\n", reg.v_m_ipc);
        printf("  v_i_a_ipc: %.2f\n", reg.v_i_a_ipc);
        printf("  Region: %s\n", reg.region);
        printf("  Fecha: %s\n", reg.periodo_codif.periodo);
        printf("  Fecha (anio - mes ): %d - %d\n", reg.periodo_codif.anio, reg.periodo_codif.mes);
        puts("------------------------------------------------------------\n");
    }

    fclose(pf);
    system("pause");
}

