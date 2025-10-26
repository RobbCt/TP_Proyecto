//biblio standar
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//biblio
#include "funciones.h"
#include "mem.h"

//define's
#define TODO_OK 0
#define TODO_MAL 1



char* dirUltComillas(char *);
int comaApunto(char *);
int valInt(int,int);
FECHA valFecha();
int esBien(char*, char*[]);
int esServicio(char*, char*[]);
int vectorInsertOrdPorCamp(GRUPO*,VecGenerico*,size_t);
int setearVarGrupo(DIVISION*,GRUPO*,char*);
int ejecutarBurbujeo(GRUPO*, int);
int OrdenarFecha(GRUPO*, int);



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

int vectorInsertOrdPorCamp(GRUPO* elem,VecGenerico* vec,size_t tam)
{
    if(vec->ce == vec->cap)
        if(!redimensionarVector(vec, vec->cap * INCR_FACTOR, tam))
            return TODO_MAL;


    GRUPO* i = (GRUPO*) vec -> vec;
    GRUPO* j = i + vec->ce - 1;

    while(i <= j && strcmpi(elem->grup, i -> grup) > 0)
        i++;


    // (opcional) para duplicados:
    // if (i <= j && strcmpi(elem->grup, i->grup) == 0)
    //     return TODO_MAL;

    for(; i <= j; j--){
        *(j + 1) = *j;
    }

    *i = *elem;
    vec->ce++;

    return TODO_OK;
}

int esBien(char* descrip, char* bienes[])
{
    int i;
    for(i=0;i<5;i++)
    {
        if(strcmpi(descrip, bienes[i])==0)
            return 1;
    }
    return 0;
}

int esServicio(char* descrip, char* servicios[])
{
    int i;
    for(i=0;i<8;i++)
    {
        if(strcmpi(descrip, servicios[i])==0)
            return 1;
    }
    return 0;
}

int setearVarGrupo(DIVISION* division,GRUPO* grupo,char* categoria)
{
    grupo -> f = division -> periodo_codif;

    strcpy(grupo -> descrip,division -> descrip);

    grupo -> ind_ipc = division -> ind_ipc;

    strcpy(grupo -> region,division -> region);

    strcpy(grupo -> grup,categoria);

    return TODO_OK;
}

int ordPorReg(VecGenerico *vec)
{
    GRUPO *reg = (GRUPO*) vec->vec;
    int pos = 0, cortar = 0;
    while(pos < vec->ce && cortar == 0)
    {
        if(strcmpi((reg+pos)->grup, "Bienes") == 0)
            pos++;

        else
            cortar=1;

    }


    ejecutarBurbujeo(vec -> vec, pos);//Orden para los bienes

    ejecutarBurbujeo(reg + pos, vec->ce - pos);//Orden para los servicios

    return TODO_OK;
}

int ejecutarBurbujeo(GRUPO *vec, int lim)
{
    GRUPO aux;

    for (int i = 0; i < lim - 1; i++)
    {
        for (int j = i + 1; j < lim; j++)
        {
            // Comparar regiones con aritmética de punteros
            if (strcmpi((vec + i)->region, (vec + j)->region) > 0)
            {
                // Intercambiar estructuras completas
                aux = *(vec + i);
                *(vec + i) = *(vec + j);
                *(vec + j) = aux;
            }
        }
    }

    return TODO_OK;
}

int ordFechaDeRegion(VecGenerico *vec)
{
    GRUPO *reg = (GRUPO*) vec->vec;
    char regAct[30] = "";
    int pos = 0;

    while (pos < vec->ce)
    {
        // Marca el inicio del grupo
        GRUPO *ini = reg;
        int count = 0;

        strcpy(regAct, reg->region);

        // Recorremos todos los elementos de esta misma región
        while (pos < vec->ce && strcmpi(regAct, reg->region) == 0)
        {
            pos++;
            reg++;
            count++;
        }

        // Ordenamos solo ese grupo
        OrdenarFecha(ini, count);
    }

    return TODO_OK;
}

int OrdenarFecha(GRUPO *vec, int cant)
{
    GRUPO aux;

    for (int i = 0; i < cant - 1; i++)
    {
        for (int j = i + 1; j < cant; j++)
        {
            // Comparar fechas (anio, luego mes)
            if ((vec + i)->f.anio > (vec + j)->f.anio ||
               ((vec + i)->f.anio == (vec + j)->f.anio &&
                (vec + i)->f.mes > (vec + j)->f.mes))
            {
                aux = *(vec + i);
                *(vec + i) = *(vec + j);
                *(vec + j) = aux;
            }
        }
    }

    return TODO_OK;
}






//definicon de primitivas
int divisionesArchTextAVar(FILE* archTxt,VecGenerico* vecDivision)
{
    DIVISION regV; //# de variable tipo struct
    char regT[MAXTAMREG];

    //saltar encabezado
    fgets(regT,MAXTAMREG,archTxt);

    while(fgets(regT,MAXTAMREG,archTxt))
    {
        regTextAVar(&regV,regT);

        vectorAgregar(&regV,vecDivision,sizeof(DIVISION));
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
    int vecCor[10] = {7,4,9,8,0,6,1,3,2,5};
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

int menu_ipc(VecGenerico* vecDivision)
{
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

    puts("\nIngrese Periodo Desde [formato aaaa-mm]");
    desde = valFecha();

    do{
        puts("Ingrese Periodo Hasta [formato aaaa-mm]: ");
        hasta = valFecha();

        if((hasta.anio < desde.anio) || (hasta.anio == desde.anio && hasta.mes <= desde.mes))
            puts("Invalido, el periodoHasta no puede ser menor (o igual) a periodoDesde, reingrese.. ");
    }while((hasta.anio < desde.anio) || (hasta.anio == desde.anio && hasta.mes <= desde.mes));

    if(!ajustarMontoIPC(vecDivision, monto, region, desde, hasta))
        return TODO_MAL;

    return TODO_OK;
}

int ajustarMontoIPC(VecGenerico* vecDiv, double monto, int region, FECHA desde, FECHA hasta)
{
    double ipcDesde = 0, ipcHasta = 0;
    char *regiones[] = {"Nacional", "GBA", "Pampeana", "Cuyo", "Noroeste", "Noreste", "Patagonia"};
    FECHA fDesde, fHasta;
    int i=0;

    while(i<vecDiv->ce) //&& (ipcDesde == 0 || ipcHasta == 0)) //por el momento funca sin esa cond, buscar optimizacion con casos de prueba
    {
        ///filtro de descr(por consigna)
        if (strcmpi(((DIVISION*)(vecDiv->vec) + i) -> descrip, "Nivel general") == 0)
        {  //filtro region
            if(strcmpi(((DIVISION*)(vecDiv->vec) + i) -> region, regiones[region - 1]) == 0)
            {   //buscamos que el anio y mes "desde" coincidan
               if (
                ((DIVISION*)(vecDiv->vec) + i) ->periodo_codif.anio == desde.anio &&
                ((DIVISION*)(vecDiv->vec) + i) ->periodo_codif.mes == desde.mes &&
                ipcDesde == 0)
//|| (vecDiv.periodo_codif.anio > desde.anio))
                { //Caso lindo: encontramos la fecha exacta
                    ipcDesde = ((DIVISION*)(vecDiv->vec) + i) ->ind_ipc;
                    fDesde = ((DIVISION*)(vecDiv->vec) + i) ->periodo_codif;
                }
                if ( ((((DIVISION*)vecDiv->vec + i)->periodo_codif.anio > desde.anio) ||
                  (((DIVISION*)vecDiv->vec + i)->periodo_codif.anio == desde.anio &&
                   ((DIVISION*)vecDiv->vec + i)->periodo_codif.mes > desde.mes)) &&
                 ipcDesde == 0 )
                {
                    puts("\nNo encontramos la fecha exacta, se usara la mas cercana a ella dentro del periodo...");
                    ipcDesde = ((DIVISION*)(vecDiv->vec) + i) ->ind_ipc;
                    fDesde = ((DIVISION*)(vecDiv->vec) + i) ->periodo_codif;
                }
            }
            // si la fecha del registro es anterior o igual al "hasta" solicitado
           if ( ((((DIVISION*)vecDiv->vec + i)->periodo_codif.anio < hasta.anio) ||
              (((DIVISION*)vecDiv->vec + i)->periodo_codif.anio == hasta.anio &&
               ((DIVISION*)vecDiv->vec + i)->periodo_codif.mes <= hasta.mes)) )
            {
                ipcHasta = ((DIVISION*)(vecDiv->vec) + i) ->ind_ipc;
                fHasta = ((DIVISION*)(vecDiv->vec) + i) ->periodo_codif;
            }
        }
        i++;
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

int grupoClasif(VecGenerico* vecDivision,VecGenerico* vecGrupo)
{
    DIVISION division;
    GRUPO grupo;
    int escribir;

    size_t ind = 0;

     char *bienes[] = {
        "Alimentos y bebidas no alcohólicas",
        "Bebidas alcohólicas y tabaco",
        "Prendas de vestir y calzado",
        "Bienes y servicios varios",
        "Equipamiento y mantenimiento del hogar"
    };

    char *servicios[] = {"Recreación y cultura",
                        "Restaurantes y hoteles","Salud","Transporte",
                        "Educación","Comunicación","Comunicación",
                        "Vivienda, agua, electricidad, gas y otros combustibles"
                       };

    while(ind < vecDivision -> ce)
    {
        escribir = 0;
        division = *((DIVISION*)vecDivision->vec + ind);

        if((escribir = esBien(division.descrip,bienes)))
            setearVarGrupo(&division,&grupo,"Bienes");
        else if((escribir = esServicio(division.descrip,servicios)))
            setearVarGrupo(&division,&grupo,"Servicio");

        if(escribir)
            vectorInsertOrdPorCamp(&grupo,vecGrupo,sizeof(GRUPO));

        ind++;
    }

    return TODO_OK;
}





















