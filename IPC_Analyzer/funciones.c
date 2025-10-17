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


void comaApunto(char*, int); //un parametro mas para generalizarla y reutilizarla dea

void reemplazoNAx0(char*, int);//para futuros calculos y previo al parseo


void divisionDecodificarFecha(DIVISION* registro)//P1
{
    /*Para el d�gito 7 corresponde un 0
      Para el d�gito 4 corresponde un 1
      Para el d�gito 9 corresponde un 2
      Para el d�gito 8 corresponde un 3
      Para el d�gito 0 corresponde un 4
      Para el d�gito 6 corresponde un 5
      Para el d�gito 1 corresponde un 6
      Para el d�gito 3 corresponde un 7
      Para el d�gito 2 corresponde un 8*/

    int anio = registro -> periodo_codif.anio,
        mes = registro -> periodo_codif.mes,
        vecCor[9] = {7,4,9,8,0,6,1,3,2}, //vec de correspondencia para la decodif
        cifra[6]; //vec para guardar fecha codif separada en cifras

    *(cifra) = (anio/1000)% 10;
    *(cifra+1) = (anio/100)% 10;
    *(cifra+2) = (anio/10)% 10;
    *(cifra+3) = anio% 10;

    *(cifra+4) = (mes/10)% 10;
    *(cifra+5) = mes% 10;

    int indCifra,indCor;

    //algoritmo de decodificacion
    for (indCifra = 0 ; indCifra < 6 ; indCifra++)
    {
        indCor = 0;
        while(*(vecCor + indCor) != *(cifra + indCifra))
            indCor++;

        *(cifra + indCifra) = indCor;
    }

    //guardar fecha decodif separada en cifras en sus respectivos campos
    registro -> periodo_codif.anio = *(cifra)*1000 + *(cifra+1)*100 + *(cifra+2)*10 + *(cifra+3);
    registro -> periodo_codif.mes = *(cifra+4)*10 + *(cifra+5);
}

void convertirFechaDecodificadaAString(DIVISION* reg)//P2
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
}

void normalizarDescr(DIVISION* reg)//P3
{
    char *desc = reg -> descrip;

    *desc = toupper(*desc); //primera letra a mayus

    desc++;

    while(*desc != '\0')
    {
        *desc = tolower(*desc); //letras siguientes a minus
        desc++;
    }
}

void filtroRegClaf(DIVISION* reg, char* desc, char *regi)//P3
{
    if(strcmpi(reg -> clasif, desc) == 0 && strcmpi(reg -> region, regi) == 0)
        printf("\n\n%20s %30s %30s %8.2lf %5.2lf %7.2lf      %9s %4d%2d %s",reg->cod,
               reg->descrip,reg->clasif,reg->ind_ipc,reg->v_m_ipc,reg->v_i_a_ipc,
               reg->region,reg->periodo_codif.anio,reg->periodo_codif.mes,reg->periodo_codif.periodo);
}

void conversionIndice(DIVISION* reg)
{
    //TENER EN CUENTA:
    /*
    En el csv original tenemos a indice_ipc como 100,3130 por ej.
    Cuando c lee ese num, puede interpretarlo como dos elementos de algun vector o struct incluso
    ya que ni siquiera se encuentra entre comillas como para que sea string (eso facilitaria la  chamba).

    Mi idea para esto es modificar nuestra struct (que ind_ipc sea de tipo DOUB)
    -DOUB seria otra struct que contenga:
            {int p_entera; int p_decimal; double nro_completo}

    como tendriamos el nro descompuesto, podemos parsearlo a string,
    concatenarlos directamente con un punto (lo que pide la consigna),
    luego volverlo a parsearlo como double y guardarlo en nro_completo para despues printear eso�

    En mi cabeza funca, les dejo la funci�n del planteo antes de olvidarla
    Acepto cr�ticas

    atte: dai
    */


    /*
        antes de nada, vamos a abrir el csv, a cada registro lo vamos a cargar por
        campos, cuando estemos en el campo
        indice_ipc, a ese string de ese campo le cambiamos la coma por el punto, con
        la funcion strrchr y

        este # cambiado lo tendremos q sobreescribir, asi con todos los #

        sscanf para el punto 5,

    */
}

void divisionParseReg()//P4
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

        /* comment ya debatido¿
        despues de tener la variable registro parseada, puedo
        sobreescribirla en la misma iteracion, parseando el arch
        completo (aun no, para no malograr el arch pq hay q revisar
        si todas las funciones se bancan el archivo

        fseek(archTxt, -sizeof(registro), SEEK_SET); //SEEK_CUR***
        fprintf(archTxt, "%s\n", registro);
        fflush(arch);
        */

        /*idea principal:
            a medida que va reemplazando la coma a punto, y NA a cero,
            vamos parseando y guardando como estructura dentro de un .bin
            paralelo al csv, asi después trabajamos solo en ese archivo.
            y, si la situación lo amerita en algun futuro, convertimos
            ese bin a csv y listo, sino nel
        */
        DIVISION regB;

        regTextABin(&regB, registro);

        fwrite(&regB, sizeof(DIVISION), 1, archBin); //vamos guardando en nuestro nuevo archivito
    }

    fclose(archBin);
    fclose(archTxt);
}

void comaApunto(char *pInf, int lac)
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
}

void reemplazoNAx0(char* pInf, int lac) //lac: lugar a cambiar (campo pero cac queda feo ahr)
{
    char *pSup, *finReg = strchr(pInf, '\n');
    int numCampo;

    if (finReg != NULL)
        *finReg = '\0';

    for (numCampo = 1; numCampo < lac; numCampo++)
        pInf = strchr(pInf + 1, ';');

    pSup = strchr(pInf+1, ';');

        // fin - inicio = ce�
    if ((pSup-(pInf+1) == 2) && *(pInf+1) == 'N' && *(pInf+2) == 'A')
    {
        *(pInf+1) = '0';
        *(pInf+2)=*(pInf+1);
    }
}

void regTextABin(DIVISION *regB, char *regT)
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
}

void divisionesArchTextABin()
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
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int regTextABin#V2(DIVISION *regB, char *regT)
{
    char *pIniCamp, *pAux;

    pIniCamp = dirComillas(regT);
    pAux = strrchr(pIniCamp,'"');

    if (pIniCamp == NULL) //fecha
        return TODO_MAL;


    if (pAux == NULL)
        return TODO_MAL;

    *pAux = '\0';

    divisionDecodificarFechaV2(pIniCamp,regB);





    /////no
    strncpy(regB->periodo_codif.periodo, );


    aux = atoi(regB->periodo_codif.periodo); //aux=9283 93 (ej)
    regB->periodo_codif.anio= aux/100; // anio= 9283
    regB->periodo_codif.mes= aux%100; // anio= 93

    /////no

    *pIniCamp='\0';



    pIniCamp = dirComillas(pIniCamp);
    if (pIniCamp == NULL) //region
        //return TODO MAL

    strncpy(regB->region, pIniCamp, sizeof(DIVISION.region) - 1);
    regB->region[sizeof(regB->region)-1]= '\0';
    *pIniCamp='\0';


    // y asi ...








}
*char dirComillas(char *TrozoRegT)
{
    pIniCamp = strrchr(TrozoRegT,';');

    if(pIniCamp == NULL)
        return NULL;

    return strchr(pIniCamp,'"') + 1;
}

void divisionDecodificarFecha#V2(char* fechaStr, DIVISION* regB)
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
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
