#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "funciones.h"

int main()
{
    DIVISION reg[10] = {
    // {cod, descrip, clasif, ind_ipc, v_m_ipc, v_i_a_ipc, region, periodo_codif}
    {"0", "NIVEL GENERAL", "Nivel general y divisiones", 100.0, 0.0, 0.0, "GBA", 974149},
    {"0", "NIVEL GENERAL", "Nivel general y divisiones", 100.0, 0.0, 0.0, "Nacional", 974149},
    {"01", "Alimentos y bebidas no alcohólicas", "Nivel general y divisiones COICOP", 100.0, 0.0, 0.0, "Pampeana", 974149},
    {"02", "Bebidas alcohólicas y tabaco", "Nivel general y divisiones COICOP", 100.0, 0.0, 0.0, "Noroeste", 974149},
    {"03", "Prendas de vestir y calzado", "Nivel general y divisiones COICOP", 100.0, 0.0, 0.0, "Cuyo", 974149},
    {"04", "Vivienda, agua, electricidad, gas ", "Nivel general y divisiones COICOP", 100.0, 0.0, 0.0, "Patagonia", 974149},
    {"0", "NIVEL GENERAL", "Nivel general y divisiones COICOP", 101.313, 1.3, 0.0, "GBA", 974374},
    {"01", "Alimentos y bebidas no alcohólicas", "Nivel general y divisiones COICOP", 101.3069, 1.3, 0.0, "GBA", 974374},
    {"04", "gas y otros combustibles", "Nivel general y divisiones COICOP", 110.3184, 10.3, 0.0, "Patagonia", 974374},
    {"70", "NA", "Categorias", 101.6969, 1.7,7.1, "Nacional", 974374}
    //{"Estacional", "NA", "Categorias", 101.6969, 1.7,"NA", "Nacional", 974374} da problemas, pero es un # real
    };
    //pensar q ya tenemos los # en el programa, listos para testear


    divisionDecoFecha(reg);


    return 0;
}
//si hago %4d%2d para la fecha, podria separar los digitos en 2 campos diferentes o una variable de tipo estructura anidada









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
