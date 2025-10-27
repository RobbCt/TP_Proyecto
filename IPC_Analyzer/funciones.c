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

char* IniCampConComillas(char*);
char* IniCampSinComillas(char*);
int comaApunto(char *);
int valInt(int,int);
double valDoub(int li);
FECHA valFecha();
int esBien(char*, char*[]);
int esServicio(char*, char*[]);
int setearVarGrupo(DIVISION*,GRUPO*,char*);




//utilitarias
char* IniCampConComillas(char* regT)
{
    char* uComillas;
    uComillas = strrchr(regT, '"');

    if(!uComillas)
        return NULL;

    *uComillas = '\0';

    uComillas = strrchr(regT, '"');

    if(!uComillas)
        return NULL;

    return uComillas + 1;
}

char* IniCampSinComillas(char* regT)
{
    char* iniCamp;

    iniCamp = strrchr(regT,';');

    if(!iniCamp)
        return NULL;

    return iniCamp + 1;
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
    int dato;

    scanf("%d",&dato);
    while(dato < li || dato > ls)
    {
        printf("reingresar: ");
        scanf("%d",&dato);
    }

    return dato;
}

double valDoub(int li)
{
    double x;
    do
    {
        scanf("%lf", &x);
        if(x<=li)
            puts("INVALIDO, reintente..");
    }while(x<=li);

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
    grupo -> f = division -> periodo;

    strcpy(grupo -> descrip,division -> descrip);

    grupo -> ind_ipc = division -> ind_ipc;

    strcpy(grupo -> region,division -> region);

    strcpy(grupo -> grup,categoria);

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
        regTextADiv(&regV,regT);

        vectorAgregar(&regV,vecDivision,sizeof(DIVISION));
    }

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
    regV -> periodo.anio = *(cifra)*1000 + *(cifra+1)*100 + *(cifra+2)*10 + *(cifra+3);
    regV -> periodo.mes = *(cifra+4)*10 + *(cifra+5);

    return TODO_OK;
}

int divisionFechDecodAStr(DIVISION* regV)
{
    char *formatoPerido = regV -> periodo.per,
         anioStr[20]; //vec para guardar anio(int) como anioStr(string)

    int mes = regV->periodo.mes,
        anio = regV->periodo.anio;

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

int divisionNormalizarDescr(char *str, DIVISION* reg)
{
    char *temp = str; //no perder el inicio del str

    *temp = toupper(*temp);

    while (*(temp++) != '\0')
        *temp = tolower(*temp);

    strcpy(reg->descrip, str);

    return TODO_OK;
}

int aperturasArchTextAVar(FILE* archTxt,VecGenerico* vecAp)
{
    APERTURA regAp; //# de variable tipo struct
    char regT[MAXTAMREG];

    //saltar encabezado
    fgets(regT,MAXTAMREG,archTxt);

    while(fgets(regT,MAXTAMREG,archTxt))
    {
        regTextAAp(&regAp,regT);

        vectorAgregar(&regAp,vecAp,sizeof(APERTURA));
    }

    return TODO_OK;
}

int aperturaConversionFecha(char* fechaStr, APERTURA* regAp)
{
    int cifra[6], indCifra;
    char* periodo= regAp->periodo.per;

    // Convertir cada carácter del string a dígito numérico (copy paste de otra funcion pol las dudash¿)
    for (indCifra = 0; indCifra < 6; indCifra++)
        *(cifra+indCifra) = *(fechaStr+indCifra) - '0';  // Convertir char a int (diferencia en ASCII)

    // Guardar fecha en estructura
    regAp -> periodo.anio = *(cifra)*1000 + *(cifra+1)*100 + *(cifra+2)*10 + *(cifra+3);
    regAp -> periodo.mes = *(cifra+4)*10 + *(cifra+5);

    sprintf(periodo, "%04d-%02d-01", regAp->periodo.anio, regAp->periodo.mes);

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

int menu_ipc(VecGenerico* vec, int opc)
{
    double monto;
    int region;
    FECHA desde, hasta;

    puts("\n\n--MONTOS AJUSTADOS--\n");
    puts("Ingrese un monto expresado en pesos: ");
    monto= valDoub(0);

    puts("\nSeleccione la region correspondiente:");
    puts("1 - Nacional\n2 - GBA\n3 - Pampeana\n4 - Cuyo\n5 - Noroeste\n6 - Noreste\n7 - Patagonia\n");
    puts("Opcion: ");
    region = valInt(1,7);

    puts("\nIngrese Periodo Desde [formato aaaa-mm]");
    desde = valFecha();

    if(opc==1)
    {
        do{
            puts("Ingrese Periodo Hasta [formato aaaa-mm]: ");
            hasta = valFecha();

            if((hasta.anio < desde.anio) || (hasta.anio == desde.anio && hasta.mes <= desde.mes))
                puts("Invalido, el periodoHasta no puede ser menor (o igual) a periodoDesde, reingrese.. ");
        }while((hasta.anio < desde.anio) || (hasta.anio == desde.anio && hasta.mes <= desde.mes));

    }
    if(!ajustarMontoIPC(vec, monto, region, desde, hasta, opc))
        return TODO_MAL;


    return TODO_OK;
}

int ajustarMontoIPC(VecGenerico* vec, double monto, int region, FECHA desde, FECHA hasta, int opc)
{
    double ipcDesde = 0, ipcHasta = 0;
    char *regiones[] = {"Nacional", "GBA", "Pampeana", "Cuyo", "Noroeste", "Noreste", "Patagonia"};
    char *filtroDescripcion[] = {"Nivel general", "Alquiler de la vivienda y gastos conexos"};
    FECHA fDesde, fHasta;
    int i = 0,nTabla = 0;
    TABLA* tabla = malloc(vec->ce * sizeof(TABLA)); // reserva máxima necesaria


    while(i < vec->ce)
    {
        void* reg;
        if(opc == 1) // DIVISION
            reg = (DIVISION*)(vec->vec) + i;
        else          // APERTURA
            reg = (APERTURA*)(vec->vec) + i;

        // Filtro por descripción y región (al estilo Calaz ahre)
        char* descrip = (opc == 1) ? ((DIVISION*)reg)->descrip : ((APERTURA*)reg)->descrip;
        char* regStr = (opc == 1) ? ((DIVISION*)reg)->region : ((APERTURA*)reg)->region;
        FECHA periodo = (opc == 1) ? ((DIVISION*)reg)->periodo : ((APERTURA*)reg)->periodo;
        double indIPC = (opc == 1) ? ((DIVISION*)reg)->ind_ipc : ((APERTURA*)reg)->ind_ipc;
    //buscamos ipcDesde sea cual sea la opcion
        if(strcmpi(descrip, filtroDescripcion[opc-1]) == 0 &&
           strcmpi(regStr, regiones[region - 1]) == 0)
        {
            if(ipcDesde == 0 &&
               periodo.anio == desde.anio && periodo.mes == desde.mes)
            {
                ipcDesde = indIPC;
                fDesde = periodo;
            }
            if(ipcDesde == 0 &&
               ((periodo.anio > desde.anio) ||
                (periodo.anio == desde.anio && periodo.mes > desde.mes)))
            {
                puts("\nno encontramos la fecha exacta, se escoge la mas cercana...");
                ipcDesde = indIPC;
                fDesde = periodo;
            }

            if(opc == 1)//buscamos el ipc hasta solo para desc=nivel gral
            {
                if(((periodo.anio < hasta.anio) ||
                    (periodo.anio == hasta.anio && periodo.mes <= hasta.mes)))
                {
                    ipcHasta = indIPC;
                    fHasta = periodo;
                }
            }
            else //guardamos todos los periodos desde el inicio para la tabla mes a mes solo para aperturas
                if(ipcDesde>0)
                {
                    tabla[nTabla].f = periodo;
                    tabla[nTabla].ipc = indIPC;
                    tabla[nTabla].montoAjustado = monto * (indIPC / ipcDesde);
                    tabla[nTabla].variacionAcum = (indIPC / ipcDesde - 1) * 100;
                    nTabla++;
                }
        }
        i++;
    }

    if(ipcDesde == 0 || (opc==1 && ipcHasta == 0))
    {
        puts("No se encontraron datos de IPC en los periodos indicados..");
        return TODO_MAL;
    }

    double montoAjustado = monto * (ipcHasta / ipcDesde);
    double variacion = (ipcHasta / ipcDesde - 1) * 100;

     if(opc == 1)
    {
        printf("\nMonto inicial: %.2lf$", monto);
        printf("\nPeriodo desde: %d-%02d \t IPC: %.2lf", fDesde.anio, fDesde.mes, ipcDesde);
        printf("\nPeriodo hasta: %d-%02d \t IPC: %.2lf", fHasta.anio, fHasta.mes, ipcHasta);
        printf("\nMonto ajustado: %.2lf$", montoAjustado);
        printf("\nVariacion porcentual: %.2lf\n", variacion);
    }
    else
    {
        printf("\nMonto inicial: %.2lf$\n", monto);
        printf("Periodo desde: %d-%02d \t IPC: %.2lf\n\n", fDesde.anio, fDesde.mes, ipcDesde);
        printf("Tabla mes a mes:\n");
        printf("Fecha\t\tIPC\tMonto Ajustado\tVariacion Acumulada\n");
        printf("-------------------------------------------------------------\n");
        for(int k = 0; k < nTabla; k++)
        {
            printf("%d-%02d\t%.2lf\t%.2lf\t\t%.2lf%%\n",
                   tabla[k].f.anio, tabla[k].f.mes,
                   tabla[k].ipc,
                   tabla[k].montoAjustado,
                   tabla[k].variacionAcum);
        }
        free(tabla);
    }
    return TODO_OK;
}




//definicion de primitivasn't

int regTextADiv(DIVISION *regV, char *regT)
{
    char *pIniCamp;

    pIniCamp = IniCampConComillas(regT); //PERIODO CODIF
    divisionDecodificarFecha(pIniCamp,regV);
    divisionFechDecodAStr(regV);

    *(strrchr(regT,';')) = '\0'; //cada q consumis un campo

    pIniCamp = IniCampConComillas(regT); //REGION
    setString(pIniCamp,regV -> region);

    *(strrchr(regT,';')) = '\0'; //cada q consumis un campo

    pIniCamp = IniCampSinComillas(regT); //v_i_a_IPC
    setDouble(pIniCamp,&regV -> v_i_a_ipc);

    *(strrchr(regT,';')) = '\0'; //cada q consumis un campo

    pIniCamp = IniCampSinComillas(regT); //v_m_IPC
    setDouble(pIniCamp,&regV -> v_m_ipc);

    *(strrchr(regT,';')) = '\0'; //cada q consumis un campo

    pIniCamp = IniCampSinComillas(regT); //Indice_IPC
    setDouble(pIniCamp,&regV -> ind_ipc) ;

    *(strrchr(regT,';')) = '\0'; //cada q consumis un campo

    pIniCamp = IniCampConComillas(regT); //CLASIFICADOR
    setString(pIniCamp,regV -> clasif);

    *(strrchr(regT,';')) = '\0'; //cada q consumis un campo

    if(!strrchr(regT, ';'))
        return TODO_MAL;

    if(*(strrchr(regT,';') + 1) == '"') //DESCRIPCION
        pIniCamp = IniCampConComillas(regT);

    else
        pIniCamp = IniCampSinComillas(regT);

    divisionNormalizarDescr(pIniCamp,regV);

    *(strrchr(regT,';')) = '\0'; //cada q consumis un campo

    pIniCamp = IniCampConComillas(regT); //CODIGO
    setString(pIniCamp,regV -> cod);

    return  TODO_OK;
}

int setString(char *str,char *campo)
{
    strcpy(campo,str);
    return TODO_OK;
}

int setDouble(char *str, double *campo)
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

int regTextAAp(APERTURA *regAp, char *regT)
{
    char *pIniCamp, *finReg;

    if(!(finReg = strrchr(regT,'\n')))
        return TODO_MAL;

    *finReg = '\0';

    pIniCamp = IniCampSinComillas(regT);//region

    setString(pIniCamp, regAp->region);

    *(strrchr(regT, ';'))='\0';

    pIniCamp= IniCampSinComillas(regT);//v_i_a_ipc

    setDouble(pIniCamp, &regAp->v_i_a_ipc);

    *(strrchr(regT, ';'))='\0';

    pIniCamp= IniCampSinComillas(regT);//v_m_ipc

    setDouble(pIniCamp, &regAp->v_m_ipc);

    *(strrchr(regT, ';'))='\0';

    pIniCamp= IniCampSinComillas(regT);//ind_ipc

    setDouble(pIniCamp, &regAp->ind_ipc);

    *(strrchr(regT, ';'))='\0';

    pIniCamp= IniCampSinComillas(regT);//periodo

    aperturaConversionFecha(pIniCamp, regAp);

    *(strrchr(regT, ';'))='\0';

    pIniCamp= IniCampSinComillas(regT);//clasificador

    setString(pIniCamp, regAp->clasif);

    *(strrchr(regT, ';'))='\0';

    pIniCamp= IniCampSinComillas(regT);//descrip

    setString(pIniCamp, regAp->descrip);

    *(strrchr(regT, ';'))='\0';

    pIniCamp = regT;

    setString(pIniCamp, regAp->cod);

    return  TODO_OK;
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



//ordenamiento
int ordPorReg(VecGenerico *vec)
{
    GRUPO *reg = (GRUPO *)vec->vec;
    int pos = 0, cortar = 0;

    while(pos < vec->ce && cortar == 0)
    {
        if(strcmpi((reg + pos)->grup, "Bienes") == 0)
            pos++;
        else
            cortar = 1;
    }

    // Orden para bienes y servicios
    burbujeo(vec->vec, pos, sizeof(GRUPO), cmpRegion);
    burbujeo(reg + pos, vec->ce - pos, sizeof(GRUPO), cmpRegion);

    return TODO_OK;
}

int ordFechaDeRegion(VecGenerico *vec)
{
    GRUPO *reg = (GRUPO *)vec->vec;
    char regAct[30] = "";
    int pos = 0;

    while (pos < vec->ce)
    {
        GRUPO *ini = reg; //guardo el reg de la reg actual (base del ordenam)
        int lim = 0;

        strcpy(regAct, reg->region);

        while (pos < vec->ce && strcmpi(regAct, reg->region) == 0)
        {
            pos++;
            reg++;
            lim++;
        }

        burbujeo(ini, lim, sizeof(GRUPO), cmpFecha);
    }

    return TODO_OK;
}

//Funcion generica (espero xd) de burbujeo god :3
int burbujeo(void *vec, int lim, size_t tamElem, Cmp fDeCmp)
{
    void *aux = malloc(tamElem);//con malloc por no saber el tipo de dato
    if(!aux)
        return TODO_MAL;

    char *base = (char *)vec;//casteo para moverme n bytes

    for (int i = 0; i < lim - 1; i++)
    {
        for (int j = 0; j < lim - 1 - i; j++)
        {
            //defino los elem a comparar
            void *a = base + j * tamElem;
            void *b = base + (j + 1) * tamElem;

            //a puro memcpy por ser puros voids* xd (hecho en base al resultado de la cmp en la f)
            if (fDeCmp(a, b) > 0)
            {
                memcpy(aux, a, tamElem);
                memcpy(a, b, tamElem);
                memcpy(b, aux, tamElem);
            }
        }
    }

    free(aux);
    return 0;
}
//Funciones de comparacion, para la funcion de comparacion generica (?
int cmpRegion(const void *a, const void *b)
{
    //cast a los tipos de datos respectivos
    const GRUPO *g1 = (const GRUPO *)a;
    const GRUPO *g2 = (const GRUPO *)b;
    return strcmpi(g1->region, g2->region);
}

int cmpFecha(const void *a, const void *b)
{
    const GRUPO *g1 = (const GRUPO *)a;
    const GRUPO *g2 = (const GRUPO *)b;

    if (g1->f.anio != g2->f.anio)
        return g1->f.anio - g2->f.anio;

    return g1->f.mes - g2->f.mes;
}












