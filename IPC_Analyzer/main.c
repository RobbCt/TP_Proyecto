//biblio standar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//biblio
#include "funciones.h"

//define's

void imprimirVecDiv(VecGenerico*);

//necesario que sigan siendo dos funciones distintas?? no, permiso para unificarla¿
void imprimirVecGrupo(VecGenerico*);
void imprimirVecAp(VecGenerico*);

int main()
{
    FILE *archTxtD = fopen("../Data/serie_ipc_divisiones.csv","rt");

    if(!archTxtD){
        puts("No se pudo abrir el archivo (.txt): serie_ipc_divisiones");
        exit(1);
    }

    FILE *archTxtA = fopen("../Data/serie_ipc_aperturas.csv","rt");
    if(!archTxtA){
        puts("No se pudo abrir el archivo (.txt): serie_ipc_aperturas");
        fclose(archTxtD);
        exit(1);
    }

    VecGenerico vecDivision;
    vectorCrear(&vecDivision,sizeof(DIVISION));

    VecGenerico vecGrupo;
    vectorCrear(&vecGrupo,sizeof(GRUPO));

    VecGenerico vecApertura;
    vectorCrear(&vecApertura,sizeof(DIVISION));

    /////////////////WORK///////////////////

    divisionesArchTextAVar(archTxtD,&vecDivision);

    //imprimirVecDiv(&vecDivision);///(opcional)

    aperturasArchTextAVar(archTxtA,&vecApertura);

    //imprimirVecAp(&vecApertura);///(opciona)

    grupoClasif(&vecDivision,&vecGrupo);

    ordPorReg(&vecGrupo);

    ordGrupoDeRegion(&vecGrupo);

    //imprimirVecGrupo(&vecGrupo);///(opciona)

    menu(&vecDivision, &vecApertura, &vecGrupo); //aun es modificable y puede ser utilizado para mas puntos

    /////////////////WORK///////////////////

    vectorDestruir(&vecDivision);
    vectorDestruir(&vecGrupo);
    vectorDestruir(&vecApertura);

    fclose(archTxtD);
    fclose(archTxtA);

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimirVecDiv(VecGenerico* vecDivision)
{
    int i;
    DIVISION* vec = (DIVISION*)vecDivision->vec;

    for(i = 0; i < vecDivision->ce; i++)
    {
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
        DIVISION* actual = vec + i;  // Aritmética de punteros

        printf("\n%-10s|%-54s | %-33s |%6.2f | %6.2f | %6.2f | %-8s | %-10s (%04d-%02d)",
               actual->cod,
               actual->descrip,
               actual->clasif,
               actual->ind_ipc,
               actual->v_m_ipc,
               actual->v_i_a_ipc,
               actual->region,
               actual->periodo.per,
               actual->periodo.anio,
               actual->periodo.mes);
    }

    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n[%d REGISTROS]\n\n\n",i);
}

void imprimirVecGrupo(VecGenerico* vecGrupo)
{
    int i;
    GRUPO* vec = (GRUPO*)vecGrupo->vec;

    for(i = 0; i < vecGrupo->ce; i++)
    {
        printf("%-60s | %10s | %.2f | %20s | %s (%d-%d)\n",
            (vec + i)->descrip,
            (vec + i)->grup,
            (vec + i)->ind_ipc,
            (vec + i)->region,
            (vec + i)->f.per,   // asumo que FECHA tiene campo 'periodo'
            (vec + i)->f.anio,
            (vec + i)->f.mes
        );
        printf("\n-------------------------------------------------------------------------------------------------------------------------------------\n");

    }

    printf("\n[%d REGISTROS]\n\n\n",i);
}

void imprimirVecAp(VecGenerico* vecA)
{
    int i;
    DIVISION* vec = (DIVISION*)vecA->vec;
    for(i=0;i < vecA -> ce;i++)
    {
        printf("%5s | %-57s | %s | %.2f | %5.2f | %.2f | %10s | %10s(%d-%d)",
        (*(vec + i)).cod,
        (*(vec + i)).descrip,
        (*(vec + i)).clasif,
        (*(vec + i)).ind_ipc,
        (*(vec + i)).v_m_ipc,
        (*(vec + i)).v_i_a_ipc,
        (*(vec + i)).region,
        (*(vec + i)).periodo.per,
        (*(vec + i)).periodo.anio,
        (*(vec + i)).periodo.mes);
        printf("\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    }

    printf("\n[%d REGISTROS]\n\n\n",i);
}

