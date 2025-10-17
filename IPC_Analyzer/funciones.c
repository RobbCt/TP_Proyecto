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

void filtroRegClaf(DIVISION* reg, char* desc, char *regi)//P3
{
    if(strcmpi(reg -> clasif, desc) == 0 && strcmpi(reg -> region, regi) == 0)
        printf("\n\n%20s %30s %30s %8.2lf %5.2lf %7.2lf      %9s %4d%2d %s",reg->cod,
               reg->descrip,reg->clasif,reg->ind_ipc,reg->v_m_ipc,reg->v_i_a_ipc,
               reg->region,reg->periodo_codif.anio,reg->periodo_codif.mes,reg->periodo_codif.periodo);
}


/*void divisionParseReg()
{
    FILE *archTxt = fopen("../Data/serie_ipc_divisiones(test).csv","r+t");

    FILE *archBin = fopen("../Data/serie_ipc_divisiones(test).dat", "wb"); //nuevo arch bin

    char registro[MAXTAMREG];


    if(!archTxt)
    {
        puts("No se pudo abrir el archivo: serie_ipc_divisiones(test)");
        exit(1);
    }

    fgets(registro,MAXTAMREG,archTxt); //saltar encabezado

    while(fgets(registro,MAXTAMREG,archTxt)) //fgets siempre trae un registro a variable con \0 al final
    {
        printf("\n\nantes ---------------------------------");
        printf("\n%s",registro);

        comaApunto(registro, 4); //sabiendo la estructura y como estan divididos
        comaApunto(registro, 5); //

        reemplazoNAx0(registro, 5); //sabiendo la estructura y como estan divididos
        reemplazoNAx0(registro, 6); //

        printf("despues +++++++++++++++++++++++++++++++"); //valido lo del ultimo reg
        printf("\n%s\n\n",registro);

         comment ya debatido¿
        despues de tener la variable registro parseada, puedo
        sobreescribirla en la misma iteracion, parseando el arch
        completo (aun no, para no malograr el arch pq hay q revisar
        si todas las funciones se bancan el archivo

        fseek(archTxt, -sizeof(registro), SEEK_SET); //SEEK_CUR***
        fprintf(archTxt, "%s\n", registro);
        fflush(arch);


        idea principal:
            a medida que va reemplazando la coma a punto, y NA a cero,
            vamos parseando y guardando como estructura dentro de un .bin
            paralelo al csv, asi después trabajamos solo en ese archivo.
            y, si la situación lo amerita en algun futuro, convertimos
            ese bin a csv y listo, sino nel

        DIVISION regB;

        regTextABin(&regB, registro);

        fwrite(&regB, sizeof(DIVISION), 1, archBin); //vamos guardando en nuestro nuevo archivito
    }

    fclose(archBin);
    fclose(archTxt);
}*/

/*void comaApunto(char *pInf, int lac)
{
    //nos desplazamos en el str registro por los separadores
    //pInf(inferior/inicio del campo), pSup(superior/fin del campo)
    char *pSup,
         *finReg = strchr(pInf,'\n');
    int numCampo;

    //archivo sin \n (solo \0) en el ultimo registro -> registro valido
    if(finReg != NULL)
        *finReg = '\0';

    //indice_IPC campo nro 4
    for(numCampo = 1 ; numCampo < lac ; numCampo++)
        pInf = strchr(pInf + numCampo,';'); //pInf en el separador antes del campo clave

    pSup = strchr(pInf+1,';'); //pInf en el separador despues del campo clave

    //paso de , a .
    while(pInf != pSup && *pInf != ',')
        pInf++;

    if(pInf != pSup)
        *pInf = '.';
}*/


/*void regTextABin(DIVISION *regB, char *regT)
{
    char *pf;
    int aux;

    pf = strrchr(regT, ';');
    if (pf != NULL) //fecha
    {                                      //pf+2 para quitar las comillas iniciales
        strncpy(regB->periodo_codif.periodo, pf + 2,sizeof(regB->periodo_codif.periodo) - 1);
        regB->periodo_codif.periodo[sizeof(regB->periodo_codif.periodo)-11]= '\0';
                                                            //-11: hardcodeo pa quitar  las comillas finales
        //atoi = string to int (string a pasar)!!!!!!!!!!!! ASCII to Integer
        aux = atoi(regB->periodo_codif.periodo); //aux=9283 93 (ej)
        regB->periodo_codif.anio= aux/100; // anio= 9283
        regB->periodo_codif.mes= aux%100; // anio= 93

        *pf='\0';
    }

    pf= strrchr(regT, ';');
    if(pf!= NULL) //region
    {
        strncpy(regB->region, pf+1, sizeof(regB->region) - 1);
        regB->region[sizeof(regB->region)-1]= '\0';
        *pf='\0';
    }

    pf= strrchr(regT, ';');
    if(pf!=NULL)
    {                   //strtod: string to double (string, NULL)
        regB->v_i_a_ipc = strtod(pf+1, NULL);
        *pf='\0';
    }

    pf= strrchr(regT, ';');
    if(pf!=NULL)
    {                   //strtod: string to double (string, NULL)
        regB->v_m_ipc = strtod(pf+1, NULL);
        *pf='\0';
    }

    pf= strrchr(regT, ';');
    if(pf!=NULL)
    {                   //strtod: string to double (string, NULL)
        regB->ind_ipc = strtod(pf+1, NULL);
        *pf='\0';
    }

    pf= strrchr(regT, ';');
    if(pf!=NULL) //clasificacion
    {
        strncpy(regB->clasif, pf+1, sizeof(regB->clasif) - 1);
        regB->clasif[sizeof(regB->clasif)-1]= '\0';
        *pf='\0';
    }

    pf= strrchr(regT, ';');
    if(pf!=NULL) //descripcion
    {
        strncpy(regB->descrip, pf+1, sizeof(regB->descrip) - 1);
        regB->descrip[sizeof(regB->descrip)-1]= '\0';
        *pf='\0';
    }

    //ya llego al inicio del regT pal cod
    strncpy(regB->cod, regT, sizeof(regB->cod) - 1);
    regB->cod[sizeof(regB->cod)-1]= '\0';


    puts("cargao");
}*/






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

    puts("TODO_OK");

    return TODO_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

     //*(dirUltComillas(regT)) = '\0';


     pFinCamp = strrchr(regT,';'); //v_m_IPC
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT,';') + 1;

     setearDouble(pIniCamp,&regB -> v_m_ipc);

     //*(dirUltComillas(regT)) = '\0';

     pFinCamp = strrchr(regT,';'); //Indice_IPC
     *pFinCamp = '\0';
     pIniCamp = strrchr(regT,';') + 1;

     setearDouble(pIniCamp,&regB -> ind_ipc) ;

     pFinCamp = strrchr(regT,'"');
     *pFinCamp = '\0';


     pIniCamp = dirUltComillas(regT) + 1; //clasificador
     setearString(pIniCamp,regB -> clasif);

     *(dirUltComillas(regT)) = '\0';






     /*pFinCamp = strrchr(regT,';'); //descripcion
     *(dirUltComillas(regT)) = '\0';

     pIniCamp = dirUltComillas(regT) + 1;

     normalizarDescr(pIniCamp,regB);

     *(dirUltComillas(regT)) = '\0';*/


    pFinCamp = strrchr(regT,';'); // ERROR, el ultimo # tiene en el campo "descripcion"  o consideramos
     *pFinCamp = '\0';            // que no pude tener " al inicio y al fin
     pIniCamp = strrchr(regT,';') + 1;

     normalizarDescr(pIniCamp,regB);
    *(dirUltComillas(regT)) = '\0';










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

int comaApunto(char *cadena)
{
    //paso de , a .
    while(*cadena != '\0' && *cadena != ',')
        cadena++;

    if(*cadena == ',')
        *cadena = '.';

    return TODO_OK;
}

int normalizarDescr(char *cadena, DIVISION* reg)
{
    int largoDeLaCadena = strlen(cadena);
    printf("\nLargo de la cadena: %d", largoDeLaCadena);

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

    printf("\nDescripción normalizada: %s", reg->descrip);
    return TODO_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
