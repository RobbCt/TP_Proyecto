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

void mostrarBin(FILE*);

int main()
{
    divisionParsearCampo();
    system("pause");

    puts("archivo bin generado:");
    FILE* pf=fopen("../Data/divisionesss.dat", "rb");
    mostrarBin(pf);
    fclose(pf);

    system("pause");

    int i;
    DIVISION reg[TAM] ={
    {"023", "NIVEL GENERAL", "Nivel general", 150.01, 16.0, 18.5, "GBA",{9741,49,""}},
    {"045", "NIVEL GENERAL", "Nivel general y divisiones", 100.5, 90.0, 0.1, "Nacional",{9741,49}},
    {"x23", "bebidas alcohólicas", "Nivel general y COICOP", 140, 0.1, 10.0, "Pampeana",{9741,49}},
    {"11", "Bebidas y tabaco", "COICOP", 11, 500, 70, "Noroeste",{9741,49}},
    {"03", "Prendas de vestir", "divisiones COICOP", 70, 0, 14, "Cuyo",{9741,49}},
    {"04", "Vivienda, electricidad, gas ", "Nivel general", 80, 0, 14, "Patagonia",{9741,49}},
    {"35", "NIVEL GENERAL", "COICOP", 101.313, 1.3, 0, "GBA",{9743,74}},
    {"abc", "bebidas no alcoholicas", "COICOP", 101.3069, 1.3, 14, "GBA",{9743,74}},
    {"04", "gas y otros combustibles", "Nivel COICOP", 110.3184, 10.3, 19, "Patagonia",{9743,74}},
    {"xd", "NA", "Categorias", 101.6969, 1.7,7.1, "Nacional",{9743,74}}
    };

    //imprimirRegistros(reg);

    for(i = 0;i<TAM;i++)
    {
        divisionDecodificarFecha(reg+i);
    }

    imprimirRegistros(reg);

    printf("\n\n\n\n%20s %30s %30s %13s %9s %11s %11s %8s",
           "CODIGO","DESCRIPCION","CLASIFICADOR",
           "INDICE_IPC","V_M_IPC","V_I_A_IPC","REGION","PERIODO");
    for(i = 0;i<TAM;i++)
    {
        convertirFechaDecodificadaAString(reg+i);
        normalizarDescr(reg+i);
        filtroRegClaf(reg+i,"COICOP", "GBA");
    }

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void imprimirRegistros(DIVISION* reg)
{
    int i;

    printf("\n\n\n\n%20s %30s %30s %13s %9s %11s %11s %8s",
           "CODIGO","DESCRIPCION","CLASIFICADOR",
           "INDICE_IPC","V_M_IPC","V_I_A_IPC","REGION","PERIODO");

    for(i=0;i<TAM;i++)
    {
        printf("\n\n%20s %30s %30s %8.2lf %5.2lf %7.2lf      %9s %4d%2d %s",reg->cod,
               reg->descrip,reg->clasif,reg->ind_ipc,reg->v_m_ipc,reg->v_i_a_ipc,
               reg->region,reg->periodo_codif.anio,reg->periodo_codif.mes,reg->periodo_codif.periodo);

        reg++;
    }
}
//si hago %4d%2d para la fecha, podria separar los digitos en 2 campos diferentes o una variable de tipo estructura anidada

void mostrarBin(FILE* pf)
{
    DIVISION reg;
    int i = 1;

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
}












/*#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funciones.h"


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    FILE *pf = fopen("../Data/serie_ipc_divisiones(test).csv","r+t");
    DIVISION reg;

    if(pf == NULL)
    {
        printf("\nERROR\n");
        exit(1);
    }


    typedef struct
{
    char cod[21];
    char descrip[31];
    char clasif[31];
    double ind_ipc;
    double v_m_ipc;
    double v_i_a_ipc;
    char region[10];
    FECHA periodo_codif; //asi tenemos separada la fecha(capaz lo necesitemos mas adelante)
    }DIVISION;

    fread(&reg,sizeof(DIVISION),1,pf);
    while(!feof(pf))
    {
        fscanf(pf,"%s;%s;%s;%f;%f;%f;%s;%d",reg.cod,reg.descrip,reg.clasif,&reg.ind_ipc,&reg.v_m_ipc,&reg.v_i_a_ipc,reg.region,&reg.periodo_codif);

        printf("%s %s %s %f %f %f %s %d\n",reg.cod,reg.descrip,reg.clasif,reg.ind_ipc,reg.v_m_ipc,reg.v_i_a_ipc,reg.region,reg.periodo_codif);



        //printf("%s \n\n", registro.cod);
        fread(&reg,sizeof(DIVISION),1,pf);
    }





}*/
