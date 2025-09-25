#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "funciones.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    FILE *pf = fopen("../Data/serie_ipc_divisiones(test).csv", "rt");
    if (pf == NULL) {
        printf("ERROR al abrir archivo\n");
        exit(1);
    }

    char linea[512];
    fgets(linea, sizeof(linea), pf); // Leer encabezado y descartarlo

    DIVISION reg;

    while (fgets(linea, sizeof(linea), pf)) {
        char cod[32], descrip[64], clasif[64], ind[32], vm[32], via[32], region[32], periodo[32];

        // Separar por ;
        if (sscanf(linea, "\"%[^\"]\";\"%[^\"]\";\"%[^\"]\";%31[^;];%31[^;];%31[^;];\"%[^\"]\";\"%[^\"]\"",
                   cod, descrip, clasif, ind, vm, via, region, periodo) == 8) {

            // Copiar strings a la struct
            strncpy(reg.cod, cod, sizeof(reg.cod));
            strncpy(reg.descrip, descrip, sizeof(reg.descrip));
            strncpy(reg.clasif, clasif, sizeof(reg.clasif));
            strncpy(reg.region, region, sizeof(reg.region));

            // Convertir números (cambiando coma por punto)
            for (char *p = ind; *p; p++) if (*p == ',') *p = '.';
            for (char *p = vm; *p; p++) if (*p == ',') *p = '.';
            for (char *p = via; *p; p++) if (*p == ',') *p = '.';

            reg.ind_ipc   = (strcmp(ind, "NA") == 0) ? 0 : atof(ind);
            reg.v_m_ipc   = (strcmp(vm, "NA") == 0) ? 0 : atof(vm);
            reg.v_i_a_ipc = (strcmp(via, "NA") == 0) ? 0 : atof(via);

            // Periodo como AAAAMM (ej. 974149 → año=9741 mes=49)
            int periodo_num = atoi(periodo);
            reg.periodo_codif.anio = periodo_num / 100;
            reg.periodo_codif.mes  = periodo_num % 100;

            // Mostrar resultado
            printf("%s | %s | %s | %.2f | %.2f | %.2f | %s | %04d-%02d\n",
                   reg.cod, reg.descrip, reg.clasif,
                   reg.ind_ipc, reg.v_m_ipc, reg.v_i_a_ipc,
                   reg.region, reg.periodo_codif.anio, reg.periodo_codif.mes);
        }
    }

    fclose(pf);
    return 0;
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
