//biblio standar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//biblio
#include "funciones.h"

//define's


void imprimirVec(VecGenerico* vecDivision);
void imprimirVecGrupo(VecGenerico* vecGrupo);

int main()
{
    FILE *archTxt = fopen("../Data/serie_ipc_divisiones(test).csv","rt");

    if(!archTxt){
        puts("No se pudo abrir el archivo (.txt): serie_ipc_divisiones(test)");
        exit(1);
    }

    VecGenerico vecDivision;
    vectorCrear(&vecDivision,sizeof(DIVISION));

    VecGenerico vecGrupo;
    vectorCrear(&vecGrupo,sizeof(GRUPO));


    ////////////////////////////////////W

    divisionesArchTextAVar(archTxt,&vecDivision);

    //imprimirVec(&vecDivision);


    //menu_ipc(&vecDivision);

    grupoClasif(&vecDivision,&vecGrupo);

    puts("este es el main");
    imprimirVecGrupo(&vecGrupo);

    //evoIPCporGrupos(&vecGrupo);

    ////////////////////////////////////W
    vectorDestruir(&vecDivision);
    fclose(archTxt);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimirVec(VecGenerico* vecDivision)
{
    int i;
    DIVISION* vec = (DIVISION*)vecDivision->vec;
    for(i=0;i < vecDivision -> ce;i++)
    {
        printf("\n-------------------------------------------------");
        printf("%s | %s | %s | %.2f | %.2f | %.2f | %s | %s (%d-%d)\n",
        (*(vec + i)).cod,
        (*(vec + i)).descrip,
        (*(vec + i)).clasif,
        (*(vec + i)).ind_ipc,
        (*(vec + i)).v_m_ipc,
        (*(vec + i)).v_i_a_ipc,
        (*(vec + i)).region,
        (*(vec + i)).periodo_codif.periodo,
        (*(vec + i)).periodo_codif.anio,
        (*(vec + i)).periodo_codif.mes);
    }

    printf("\n%d registros",i);
}

void imprimirVecGrupo(VecGenerico* vecGrupo)
{
    size_t i;
    GRUPO* vec = (GRUPO*)vecGrupo->vec;

    for(i = 0; i < vecGrupo->ce; i++)
    {
        printf("\n-------------------------------------------------\n");
        printf("%s | %s | %.2f | %s | %s (%d-%d)\n",
            (vec + i)->descrip,
            (vec + i)->grup,
            (vec + i)->ind_ipc,
            (vec + i)->region,
            (vec + i)->f.periodo,   // asumo que FECHA tiene campo 'periodo'
            (vec + i)->f.anio,
            (vec + i)->f.mes
        );
    }

    printf("\n%zu registros\n", i);
}

