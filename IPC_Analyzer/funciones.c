//biblio standar
#include <stdlib.h>

//biblio
#include "funciones.h"

//define's
#define MESES 12
#define CANTMAXCHAR 17
#define TAM 10 //temporal
#define TODO_OK 1
#define TODO_MAL 0


int comaApunto(char*); //un parametro mas para generalizarla y reutilizarla dea
char* dirUltComillas(char *);
int setearString(char *,char *);
int setearDouble(char *, double *);

int divisionesArchTextABin()
{
    FILE *archTxt = fopen("../Data/serie_ipc_divisiones(test).csv","rt");
    FILE *archBin = fopen("../Data/serie_ipc_divisiones(test).dat","wb"); //nuevo arch bin

    if(!archTxt)
    {
        puts("No se pudo abrir el archivo (.txt): serie_ipc_divisiones(test)");
        exit(1);
    }

    if(!archBin)
    {
        puts("No se pudo crear el archivo (.bin): serie_ipc_divisiones(test)");
        fclose(archTxt);
        exit(1);
    }

    char regT[MAXTAMREG];

    fgets(regT,MAXTAMREG,archTxt); //saltar encabezado

    while(fgets(regT,MAXTAMREG,archTxt))
    {
        DIVISION regB;

        regTextABin(&regB,regT);

        fwrite(&regB, sizeof(DIVISION), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    puts("\nTODO_OK\n");

    return TODO_OK;
}

int regTextABin(DIVISION *regB, char *regT)
{
    char *pFinCamp, *pIniCamp;

    pFinCamp = dirUltComillas(regT); //fecha
    *pFinCamp = '\0';
    pIniCamp = dirUltComillas(regT) + 1;

    divisionDecodificarFecha(pIniCamp,regB);
    convertirFechaDecodificadaAString(regB);

    *(dirUltComillas(regT)) = '\0'; //o retroceder 1

    pFinCamp = dirUltComillas(regT); //region
    *pFinCamp = '\0';
    pIniCamp = dirUltComillas(regT) + 1;

    setearString(pIniCamp,regB -> region);

    *(dirUltComillas(regT)) = '\0';


     pFinCamp = strrchr(regT,';'); //v_i_a_IPC
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT,';') + 1;

     setearDouble(pIniCamp,&regB -> v_i_a_ipc);

     pFinCamp = strrchr(regT,';'); //v_m_IPC
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT,';') + 1;

     setearDouble(pIniCamp,&regB -> v_m_ipc);

     pFinCamp = strrchr(regT,';'); //Indice_IPC
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT,';') + 1;

     setearDouble(pIniCamp,&regB -> ind_ipc) ;

     pFinCamp = strrchr(regT,'"');
     *pFinCamp = '\0';


     pIniCamp = dirUltComillas(regT) + 1; //clasificador
     setearString(pIniCamp,regB -> clasif);

     *(dirUltComillas(regT)) = '\0';

     pFinCamp = strrchr(regT, ';'); //version agregada de la descripcion
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT, ';');
     if(*(pIniCamp + 1) == '"')//Evaluo si tiene comillas o si es el NA
     {
         *(pFinCamp - 1) = '\0';
         normalizarDescr(pIniCamp + 2,regB);
         *(dirUltComillas(regT)) = '\0';
     }
     else
     {
         normalizarDescr(pIniCamp + 1, regB);
         *pIniCamp = '\0';
     }

     pFinCamp = strrchr(regT,';'); //codigo
     *(dirUltComillas(regT)) = '\0';

     pIniCamp = dirUltComillas(regT) + 1;

     setearString(pIniCamp,regB -> cod);

     return TODO_OK;
}

char* dirUltComillas(char *TrozoRegT)
{
    char *uComillas;
    uComillas = strrchr(TrozoRegT, '"');

    if(uComillas == NULL)
        return NULL;

    return uComillas;
}

int divisionDecodificarFecha(char* fechaStr, DIVISION* regB)
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
    regB -> periodo_codif.anio = *(cifra)*1000 + *(cifra+1)*100 + *(cifra+2)*10 + *(cifra+3);
    regB -> periodo_codif.mes = *(cifra+4)*10 + *(cifra+5);

    return TODO_OK;
}

int convertirFechaDecodificadaAString(DIVISION* reg)//P2
{
    char *formatoPerido = reg -> periodo_codif.periodo,
         anioStr[20]; //vec para guardar anio(int) como anioStr(string)

    int mes = reg->periodo_codif.mes,
        anio = reg->periodo_codif.anio;

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

int setearString(char *cadena,char *campo)
{
    strcpy(campo,cadena);

    return TODO_OK;
}

int setearDouble(char *cadena, double *campo)
{
    if (*cadena == 'N' && *cadena+1 == 'A')
        *campo = 0;
    else
    {
        comaApunto(cadena);
        sscanf(cadena,"%lf",campo);
    }

    return TODO_OK;
}

int normalizarDescr(char *cadena, DIVISION* reg)
{
    int largoDeLaCadena = strlen(cadena);
    //printf("\nLargo de la cadena: %d", largoDeLaCadena);

    if (largoDeLaCadena == 0) {
        printf("\nError: cadena vacia");
        return TODO_MAL;
    }
    else if (largoDeLaCadena == 1) {
        printf("\nAdvertencia: cadena de largo 1");
    }

    // Crear copia temporal
    char temp[largoDeLaCadena + 1];
    strcpy(temp, cadena);

    // Normalizar la copia
    temp[0] = toupper(temp[0]);
    for (int i = 1; temp[i] != '\0'; i++) {
        temp[i] = tolower(temp[i]);
    }

    // Copiar al registro
    strcpy(reg->descrip, temp);

    //printf("\nDescripción normalizada: %s", reg->descrip);
    return TODO_OK;
}

void filtroRegClaf(DIVISION* reg, char* desc, char *regi)//P3
{
    if(strcmpi(reg -> clasif, desc) == 0 && strcmpi(reg -> region, regi) == 0)
        printf("\n\n%20s %30s %30s %8.2lf %5.2lf %7.2lf      %9s %4d%2d %s",reg->cod,
               reg->descrip,reg->clasif,reg->ind_ipc,reg->v_m_ipc,reg->v_i_a_ipc,
               reg->region,reg->periodo_codif.anio,reg->periodo_codif.mes,reg->periodo_codif.periodo);
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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
