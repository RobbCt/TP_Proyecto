//biblio standar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//biblio
#include "funciones.h"

//define's


void imprimirVec(VecDIVISION* vecDivision);

int main()
{
    FILE *archTxt = fopen("../Data/serie_ipc_divisiones.csv","rt");

    if(!archTxt){
        puts("No se pudo abrir el archivo (.txt): serie_ipc_divisiones(test)");
        exit(1);
    }

    VecDIVISION vecDivision;
    vectorCrear(&vecDivision);

    divisionesArchTextAVar(archTxt,&vecDivision);

    imprimirVec(&vecDivision);

    fclose(archTxt);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimirVec(VecDIVISION* vecDivision)
{

    int i;
    for(i=0;i < vecDivision -> ce;i++)
    {
        printf("\n-------------------------------------------------");
        printf("%s | %s | %s | %.2f | %.2f | %.2f | %s | %s (%d-%d)\n",
        vecDivision->vec[i].cod,
        vecDivision->vec[i].descrip,
        vecDivision->vec[i].clasif,
        vecDivision->vec[i].ind_ipc,
        vecDivision->vec[i].v_m_ipc,
        vecDivision->vec[i].v_i_a_ipc,
        vecDivision->vec[i].region,
        vecDivision->vec[i].periodo_codif.periodo,
        vecDivision->vec[i].periodo_codif.anio,
        vecDivision->vec[i].periodo_codif.mes);
    }

    printf("\n%d registros",i);
}
