//biblio standar
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//biblio
#include "funciones.h"

//define's
#define TODO_OK 0
#define TODO_MAL 1



char* dirUltComillas(char *);
int comaApunto(char *);


//utilitarias
char* dirUltComillas(char *TrozoRegT)
{
    char *uComillas;
    uComillas = strrchr(TrozoRegT, '"');

    if(uComillas == NULL)
        return NULL;

    return uComillas;
}

int comaApunto(char *cadena)
{
    //paso de , a .
    while(*cadena != '\0' && *cadena != ',')
        cadena++;

    if(*cadena == ',')
        *cadena = '.';

    return TODO_OK;
}


//definicon de primitivas
int divisionesArchTextAVar(FILE* archTxt,VecDIVISION* vecDivision)
{
    DIVISION regV; //# de variable tipo struct
    char regT[MAXTAMREG];

    int i=0;

    //saltar encabezado
    fgets(regT,MAXTAMREG,archTxt);

    while(fgets(regT,MAXTAMREG,archTxt))
    {
        regTextAVar(&regV,regT);

        vectorAgregar(&regV,vecDivision);
    }

    return TODO_OK;
}

int regTextAVar(DIVISION *regV, char *regT)
{
    char *pFinCamp, *pIniCamp;

    pFinCamp = dirUltComillas(regT); //fecha
    *pFinCamp = '\0';
    pIniCamp = dirUltComillas(regT) + 1;

    divisionDecodificarFecha(pIniCamp,regV);
    divisionFechDecodAStr(regV);

    *(dirUltComillas(regT)) = '\0'; //o retroceder 1

    pFinCamp = dirUltComillas(regT); //region
    *pFinCamp = '\0';
    pIniCamp = dirUltComillas(regT) + 1;

    divisionSetString(pIniCamp,regV -> region);

    *(dirUltComillas(regT)) = '\0';


     pFinCamp = strrchr(regT,';'); //v_i_a_IPC
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT,';') + 1;

     divisionSetDouble(pIniCamp,&regV -> v_i_a_ipc);

     pFinCamp = strrchr(regT,';'); //v_m_IPC
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT,';') + 1;

     divisionSetDouble(pIniCamp,&regV -> v_m_ipc);

     pFinCamp = strrchr(regT,';'); //Indice_IPC
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT,';') + 1;

     divisionSetDouble(pIniCamp,&regV -> ind_ipc) ;

     pFinCamp = strrchr(regT,'"');
     *pFinCamp = '\0';


     pIniCamp = dirUltComillas(regT) + 1; //clasificador
     divisionSetString(pIniCamp,regV -> clasif);

     *(dirUltComillas(regT)) = '\0';



     pFinCamp = strrchr(regT, ';'); //version agregada de la descripcion
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT, ';');
     if(*(pIniCamp + 1) == '"')//Evaluo si tiene comillas o si es el NA
     {
         *(pFinCamp - 1) = '\0';
         divisionNormalizarDescr(pIniCamp + 2,regV);
         *(dirUltComillas(regT)) = '\0';
     }
     else
     {
         divisionNormalizarDescr(pIniCamp + 1, regV);
         *pIniCamp = '\0';
     }

     pFinCamp = strrchr(regT,';'); //codigo
     *(dirUltComillas(regT)) = '\0';

     pIniCamp = dirUltComillas(regT) + 1;

     divisionSetString(pIniCamp,regV -> cod);

     return TODO_OK;
}

int divisionDecodificarFecha(char* fechaStr, DIVISION* regV)
{
    int vecCor[9] = {7,4,9,8,0,6,1,3,2};
    int cifra[6];
    int indCifra, indCor;

    // Convertir cada carácter del string a dígito numérico
    for (indCifra = 0; indCifra < 6; indCifra++)
        *(cifra+indCifra) = *(fechaStr+indCifra) - '0';  // Convertir char a int (diferencia en ASCII)

    // Algoritmo de decodificación
    for (indCifra = 0; indCifra < 6; indCifra++)
        {

        indCor = 0;
        while(*(vecCor + indCor) != *(cifra + indCifra))
            indCor++;

        *(cifra + indCifra) = indCor;
    }

    // Guardar fecha decodificada en la estructura
    regV -> periodo_codif.anio = *(cifra)*1000 + *(cifra+1)*100 + *(cifra+2)*10 + *(cifra+3);
    regV -> periodo_codif.mes = *(cifra+4)*10 + *(cifra+5);

    return TODO_OK;
}

int divisionFechDecodAStr(DIVISION* regV)//P2
{
    char *formatoPerido = regV -> periodo_codif.periodo,
         anioStr[20]; //vec para guardar anio(int) como anioStr(string)

    int mes = regV->periodo_codif.mes,
        anio = regV->periodo_codif.anio;

    char matMes[MESES][CANTMAXCHAR] = {{"Enero"},{"Febrero"},{"Marzo"},{"Abril"},
                                       {"Mayo"},{"Junio"},{"Julio"},{"Agosto"},
                                       {"Septiembre"},{"Octubre"},{"Noviembre"},{"Diciembre"}
                                      };
    //convertir anio(int) a anioStr(string)
    sprintf(anioStr, "%d", anio);

    strcpy(formatoPerido,*(matMes+(mes-1))); //Enero
    strcat(formatoPerido, " - ");            //Enero -
    strcat(formatoPerido, anioStr);          //Enero - 2017

    return TODO_OK;
}

int divisionSetString(char *str,char *campo)
{
    strcpy(campo,str);
    return TODO_OK;
}

int divisionSetDouble(char *str, double *campo)
{
    if (*str == 'N' && *(str+1) == 'A')
        *campo = 0;
    else
    {
        comaApunto(str);
        sscanf(str,"%lf",campo);
    }

    return TODO_OK;
}

int divisionNormalizarDescr(char *str, DIVISION* reg)
{
    char *temp = str; //no perder el inicio del str

    *temp = toupper(*temp);

    while (*(temp++) != '\0')
        *temp = tolower(*temp);

    strcpy(reg->descrip, str);

    return TODO_OK;
}


//#######################################################################################################################


//memoria dinamica
bool vectorCrear(VecDIVISION* vec)
{
    vec->vec = malloc(sizeof(DIVISION) * DEFAULT_CAP);

    if(!(vec->vec))
    {
        vec->cap = 0;
        vec->ce = 0;
        return false;
    }

    vec->ce = 0;
    vec->cap = DEFAULT_CAP;

    return true;
}

bool vectorAgregar(DIVISION* regV, VecDIVISION* vecDivision)
{
    if (vecDivision -> ce >= vecDivision -> cap)
    {
        // Redimensionar
        size_t nueva_cap = vecDivision -> cap * INCR_FACTOR;

        DIVISION *temporal = realloc(vecDivision -> vec, sizeof(DIVISION) * nueva_cap);

        if (!temporal)
            return false;

        vecDivision -> vec = temporal;
        vecDivision -> cap = nueva_cap;
    }


    *(vecDivision->vec + vecDivision->ce) = *regV;
    vecDivision->ce++;

    return true;
}

void vectorDestruir(VecDIVISION* vec)
{
    free(vec -> vec);
    vec->vec = NULL;
    vec->ce = 0;
    vec->cap = 0;
}




