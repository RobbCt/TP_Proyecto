//biblio standar
#include <stdlib.h>

//biblio
#include "funciones.h"

//define's
#define MESES 12
#define CANTMAXCHAR 17
#define TAM 10 //temporal


void comaApunto(char*);


void divisionDecodificarFecha(DIVISION* registro)//P1
{
    /*Para el dígito 7 corresponde un 0
      Para el dígito 4 corresponde un 1
      Para el dígito 9 corresponde un 2
      Para el dígito 8 corresponde un 3
      Para el dígito 0 corresponde un 4
      Para el dígito 6 corresponde un 5
      Para el dígito 1 corresponde un 6
      Para el dígito 3 corresponde un 7
      Para el dígito 2 corresponde un 8*/

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
    luego volverlo a parsearlo como double y guardarlo en nro_completo para despues printear eso¿

    En mi cabeza funca, les dejo la función del planteo antes de olvidarla
    Acepto críticas

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

void divisionParsearCampo()//P4 propuesto por robbi
{
    FILE *archTxt = fopen("../Data/serie_ipc_divisiones(test).csv","r+t");
    char registro[MAXTAMREG];


    if(!archTxt)
    {
        puts("No se pudo abrir el archivo: serie_ipc_divisiones(test)");
        exit(1);
    }

    fgets(registro,MAXTAMREG,archTxt); //saltar encabezados

    while(fgets(registro,MAXTAMREG,archTxt)) //fgets siempre trae unn registro a variable con \0 al final
    {
        printf("\n\nantes ---------------------------------");
        printf("\n%s",registro);


        comaApunto(registro);


        printf("despues +++++++++++++++++++++++++++++++");
        printf("\n%s\n\n",registro);

        /*
        despues de tener la variable registro parseada, puedo
        sobreescribirla en la misma iteracion, parseando el arch
        completo (aun no, para no malograr el arch pq hay q revisar
        si todas las funciones se bancan el archivo

        fseek(archTxt, -sizeof(registro), SEEK_SET);
        fprintf(archTxt, "%s\n", registro);
        fflush(arch);
        */
    }

    fclose(archTxt);
}

void comaApunto(char *pInf)//P4 propuesto por robbi
{
    //nos desplazamos en el str registro por los separadores
    //pInf(inferior), pSup(superior)
    char *pSup,
         *finReg = strchr(pInf,'\n');
    int numCampo;


    //archivo sin \n (solo \0) en el ultimo registro -> registro valido
    if(finReg != NULL)
        *finReg = '\0';

    //indice_IPC campo nro 4
    for(numCampo = 1 ; numCampo < 4 ; numCampo++)
        pInf = strchr(pInf + numCampo,';'); //pInf en el separador antes del campo clave

    pSup = strchr(pInf+1,';'); //pInf en el separador despues del campo clave

    //paso de , a .
    while(pInf != pSup && *pInf != ',')
        pInf++;

    if(pInf != pSup)
        *pInf = '.';
}
