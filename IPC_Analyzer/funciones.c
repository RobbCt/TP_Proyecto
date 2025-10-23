//biblio standar
#include <stdlib.h>
//#include <string.h>

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

int ajustarMontoIPC(FILE*, double, int, FECHA, FECHA);

int valInt(int,int);
FECHA valFecha();

int divisionesArchTextATxt(FILE* archTxt, FILE* archTxt2) ///agregar encabezado
{
    char regT[MAXTAMREG];
    fgets(regT,MAXTAMREG,archTxt); //saltar encabezado

    while(fgets(regT,MAXTAMREG,archTxt))
    {
        DIVISION regB;
        regTextABin(&regB,regT);
        fprintf(archTxt2, "%s;%s;%s;%.2lf;%.2lf;%.2lf;%s;%d;%d;%s\n", regB.cod, regB.descrip, regB.clasif, regB.ind_ipc, regB.v_m_ipc, regB.v_i_a_ipc, regB.region, regB.periodo_codif.anio, regB.periodo_codif.mes, regB.periodo_codif.periodo);
    }

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
    if (*cadena == 'N' && *(cadena+1) == 'A')
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

int menu_ipc(FILE* pf)
{
    rewind(pf);
    if(!pf) {
    puts("No se pudo abrir el archivo de datos IPC.");
    return TODO_MAL;}

    double monto;
    int region;
    FECHA desde, hasta;

    puts("\n\n--MONTOS AJUSTADOS--\n");
    do{
        puts("Ingrese un monto expresado en pesos: ");
        scanf("%lf", &monto);
        if(monto<=0)
            puts("INVALIDO, monto fuera de rango, reintente. ");
    }while(monto<=0);

    puts("\nSeleccione la region correspondiente:");
    puts("1 - Nacional\n2 - GBA\n3 - Pampeana\n4 - Cuyo\n5 - Noroeste\n6 - Noreste\n7 - Patagonia\n");
    puts("Opcion: ");
    region = valInt(1,7);

    puts("\nIngrese Periodo Desde [formato dddd-mm]");
    desde = valFecha();

    do{
        puts("Ingrese Periodo Hasta [formato dddd-mm]: ");
        hasta = valFecha();

        if((hasta.anio < desde.anio) || (hasta.anio == desde.anio && hasta.mes <= desde.mes))
            puts("Invalido, el periodoHasta no puede ser menor (o igual) a periodoDesde, reingrese.. ");
    }while((hasta.anio < desde.anio) || (hasta.anio == desde.anio && hasta.mes <= desde.mes));

    if(!ajustarMontoIPC(pf, monto, region, desde, hasta))
        return TODO_MAL;

    return TODO_OK;
}

int valInt(int li, int ls)
{
    int x;
    do{
        scanf("%d", &x);
        if(x<li || x>ls)
            puts("INVALIDO, reintente..");
    }while(x<li || x>ls);

    return x;
}
FECHA valFecha()
{
    FECHA x;
    do
    {
        scanf("%d-%d", &x.anio, &x.mes);
        if((x.anio<2000 || x.anio>2025)||(x.mes<1 || x.mes>12))
            puts("FECHA INVALIDA, reintente..");
    }while((x.anio<2000 || x.anio>2025)||(x.mes<1 || x.mes>12));

    return x;
}
int ajustarMontoIPC(FILE *pf, double monto, int region, FECHA desde, FECHA hasta)
{
    DIVISION reg;
    double ipcDesde = 0, ipcHasta = 0;
    char *regiones[] = {"Nacional", "GBA", "Pampeana", "Cuyo", "Noroeste", "Noreste", "Patagonia"};
    char linea[512];
    FECHA fDesde, fHasta;

    while(fgets(linea, sizeof(linea), pf)) //&& (ipcDesde == 0 || ipcHasta == 0)) //por el momento funca sin esa cond, buscar optimizacion con casos de prueba
    {   ///SOLUCION MOMENTANEA (hasta que un profe conteste(?)
        /*re-parseamos to' nuestro .txt2 y la pasamos a un reg para filtrar y
        trabajar de forma mas comodita*/
        sscanf(linea, "%[^;];%[^;];%[^;];%lf;%lf;%lf;%[^;];%d;%d;%[^;]", reg.cod, reg.descrip, reg.clasif, &reg.ind_ipc, &reg.v_m_ipc, &reg.v_i_a_ipc, reg.region, &reg.periodo_codif.anio, &reg.periodo_codif.mes, reg.periodo_codif.periodo);
        /*Desventajas de esto: lo hacemos solo dentro de esta funcion
         pero volvemos a recorrer el .txt2 completo (o hasta que se encuentre los ipc's)
         No estaría  taaaan mal si solo lo hicieramos acá por unica vez,
         pero más adelante necesitaremos trabajar de nuevo con el .txt2,
         de forma que tendríamos que volver a leerlo y parsearlo (nos quita eficiencia)

         La solución que se me ocurre: dejar la materia y avanzar con el tp del cuatri que viene¿
         Bueno no, pero leerlo una sola vez y almacenar solo los registros relevantes
         en memoria (ej un array de structs) para no tener que reabrir en cada punto¿¿¿

         */

        ///filtro de descr(por consigna)
        if (strcmpi(reg.descrip, "Nivel general") == 0)
        {  //filtro region
            if(strcmpi(reg.region, regiones[region - 1]) == 0)
            {   //buscamos que el anio y mes "desde" coincidan
                if((reg.periodo_codif.anio == desde.anio && reg.periodo_codif.mes == desde.mes)&& ipcDesde == 0)//|| (reg.periodo_codif.anio > desde.anio))
                { //Caso lindo: encontramos la fecha exacta
                    ipcDesde = reg.ind_ipc;
                    fDesde = reg.periodo_codif;
                }
                if(((reg.periodo_codif.anio > desde.anio) || (reg.periodo_codif.anio == desde.anio && reg.periodo_codif.mes > desde.mes)) && ipcDesde == 0)
                {   //Caso feo: no encontramos la fecha exacta, tomamos la proxima mayor
                    ipcDesde = reg.ind_ipc;
                    fDesde = reg.periodo_codif;
                }
            }
            // si la fecha del registro es anterior o igual al "hasta" solicitado
            if (((reg.periodo_codif.anio < hasta.anio) || (reg.periodo_codif.anio == hasta.anio && reg.periodo_codif.mes <= hasta.mes)))
            {
                ipcHasta = reg.ind_ipc;
                fHasta = reg.periodo_codif;
            }
        }
    }

    if (ipcDesde == 0 || ipcHasta == 0) {
        puts("No se encontraron datos de IPC en los periodos indicados..");
        return TODO_MAL; //ahre
    }

    double montoAjustado = monto*(ipcHasta/ipcDesde);
    double variacion = (ipcHasta/ipcDesde-1) *100;

    printf("\nMonto inicial: %.2lf$", monto);
    printf("\nPeriodo desde: %d-%02d \t IPC: %.2lf", fDesde.anio, fDesde.mes, ipcDesde);
    printf("\nPeriodo hasta: %d-%02d \t IPC: %.2lf", fHasta.anio, fHasta.mes, ipcHasta);
    printf("\nMonto ajustado: %.2lf$", montoAjustado);
    printf("\nVariacion porcentual: %.2lf\n", variacion);

    return TODO_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
