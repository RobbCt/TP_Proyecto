//biblio standar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//biblio
#include "funciones.h"

//define's


int valEntero(int, int);

void imprimirVecDiv(VecGenerico*);
void imprimirVecGrupo(VecGenerico*);
void imprimirVecAp(VecGenerico*);


int main()
{
    int opcionMenu;
    FILE *archTxtD = fopen("../Data/serie_ipc_divisiones(test).csv","rt");

    if(!archTxtD){
        puts("No se pudo abrir el archivo (.txt): serie_ipc_divisiones");
        exit(1);
    }

    FILE *archTxtA = fopen("../Data/serie_ipc_aperturas(test).csv","rt");
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
    vectorCrear(&vecApertura,sizeof(APERTURA));

    ////////////////////////////////////WORK

    divisionesArchTextAVar(archTxtD,&vecDivision);

    aperturasArchTextAVar(archTxtA,&vecApertura);

    imprimirVecAp(&vecApertura);

    grupoClasif(&vecDivision,&vecGrupo);

    ordPorReg(&vecGrupo);

    ordFechaDeRegion(&vecGrupo);

    imprimirVecGrupo(&vecGrupo);


    puts("\n\n--OPCION--\n");
    puts("Seleccione:\n1-Variacion del IPC en Nivel general\n2-Calculadora de alquileres\n3-Salir");
    opcionMenu = valEntero(1,3);

    switch(opcionMenu)
    {
        case 1: menu_ipc(&vecDivision, opcionMenu); break;
        case 2: menu_ipc(&vecApertura, opcionMenu); break;
        default: puts("Fin del programa¿");
    }

    ////////////////////////////////////WORK

    vectorDestruir(&vecDivision);
    vectorDestruir(&vecGrupo);
    vectorDestruir(&vecApertura);

    fclose(archTxtD);
    fclose(archTxtA);

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int valEntero(int li, int ls)//sacarla cuando se modularizen los menu's
{
    int dato;

    scanf("%d",&dato);
    while(dato < li || dato > ls)
    {
        printf("reingresar: ");
        scanf("%d",&dato);
    }

    return dato;
}

void imprimirVecDiv(VecGenerico* vecDivision)
{
    int i;
    DIVISION* vec = (DIVISION*)vecDivision->vec;
    for(i=0;i < vecDivision -> ce;i++)
    {
        printf("\n-------------------------------------------------\n");
        printf("%s|%s|%s|%.2f|%.2f|%.2f|%s|%s(%d-%d)\n",
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
    }

    printf("\n%d registros",i);
}

void imprimirVecGrupo(VecGenerico* vecGrupo)
{
    size_t i;
    GRUPO* vec = (GRUPO*)vecGrupo->vec;

    for(i = 0; i < vecGrupo->ce; i++)
    {
        printf("\n\n---------------------------------------------------------------------------------------------------------------------------------\n");
        printf("%60s | %10s | %.2f | %20s | %s (%d-%d)\n",
            (vec + i)->descrip,
            (vec + i)->grup,
            (vec + i)->ind_ipc,
            (vec + i)->region,
            (vec + i)->f.per,   // asumo que FECHA tiene campo 'periodo'
            (vec + i)->f.anio,
            (vec + i)->f.mes
        );
    }

    printf("\n%lu registros\n",(unsigned long) i);
}

void imprimirVecAp(VecGenerico* vecA)
{
    int i;
    APERTURA* vec = (APERTURA*)vecA->vec;
    for(i=0;i < vecA -> ce;i++)
    {
        printf("\n\n---------------------------------------------------------------------------------------------------------------------------------\n");
        printf("%5s | %60s | %s | %.2f | %.2f | %.2f | %10s | %10s(%d-%d)",
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
    }

    printf("\n%d registros",i);
}

