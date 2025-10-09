#include "funciones.h"
#define MESES 12
#define CANTMAXCHAR 17

#define TAM 10 //temporal


void divisionDecodificarFecha(DIVISION* registro)
{
    //- Para el dígito 7 corresponde un 0.
    //- Para el dígito 4 corresponde un 1.
    //- Para el dígito 9 corresponde un 2.
    //- Para el dígito 8 corresponde un 3.
    //- Para el dígito 0 corresponde un 4.
    //- Para el dígito 6 corresponde un 5.
    //- Para el dígito 1 corresponde un 6.
    //- Para el dígito 3 corresponde un 7.
    //- Para el dígito 2 corresponde un 8.

    /*armamos matriz para ahorrarme el switch*/
    int vec[9]={7,4,9,8,0,6,1,3,2};


    int cifra[6];
    int anio=registro->periodo_codif.anio, mes=registro->periodo_codif.mes;

    *(cifra)=(anio/1000)% 10;
    *(cifra+1)=(anio/100)% 10;
    *(cifra+2)=(anio/10)% 10;
    *(cifra+3)= anio% 10;

    *(cifra+4)=(mes/10)% 10;
    *(cifra+5)= mes% 10;

    int j, i;

    for (i=0;i<6;i++)
    {
        j = 0;
        while(*(vec+j) != *(cifra+i))
            j++;

        *(cifra+i) = j;
    }

    registro -> periodo_codif.anio = *(cifra)*1000 + *(cifra+1)*100 + *(cifra+2)*10 + *(cifra+3);
    registro -> periodo_codif.mes = *(cifra+4)*10 + *(cifra+5);
}

void convertirFechaDecodificadaAString(DIVISION* reg)
{
    //char stringFecha[17]; // 9 caracteres para el mes de nombre más largo ("septiembre"), 3 caracteres para la cadena " - ", 4 para el año y uno para el carácter de fin de línea
    char nombreMes[17];
    int mes = reg->periodo_codif.mes;
    int anio = reg->periodo_codif.anio;
    char anio_s[20];

    char matMes[MESES][CANTMAXCHAR] = {{"Enero"},{"Febrero"},{"Marzo"},{"Abril"},{"Mayo"},{"Junio"},{"Julio"},
                                      {"Agosto"},{"Septiembre"},{"Octubre"},{"Noviembre"},{"Diciembre"}};

    strcpy(nombreMes,*(matMes+(mes-1)));


    strcat(nombreMes, " - ");
    //    convertido tipo de dato a convertir   dato a convertir
    sprintf(anio_s, "%d", anio);
    strcat(nombreMes, anio_s);
    strcpy(reg->periodo_codif.periodo_letra,nombreMes);
}

void normalizarDescr(DIVISION* reg)
{
    char* i= reg->descrip;

    *i=toupper(*i);//esto por si la primera letra no es mayus

    i++;

    while(*i!='\0')
    {
        *i=tolower(*i);
        i++;
    }
}

void filtroRegClaf(DIVISION* reg) //necesaria??? parte del item 3
{
    int i;

    char desc[]="COICOP", regi[]="GBA";

    printf("\n\n\n\n%20s %30s %30s %13s %9s %11s %11s %8s",
           "CODIGO","DESCRIPCION","CLASIFICADOR",
           "INDICE_IPC","V_M_IPC","V_I_A_IPC","REGION","PERIODO");

    for(i=0;i<TAM;i++)
    {
        if(strcmpi(reg->clasif, desc)==0 && strcmpi(reg->region, regi)==0)
            printf("\n\n%20s %30s %30s %8.2lf %5.2lf %7.2lf      %9s %4d%2d %s",reg->cod,
               reg->descrip,reg->clasif,reg->ind_ipc,reg->v_m_ipc,reg->v_i_a_ipc,
               reg->region,reg->periodo_codif.anio,reg->periodo_codif.mes,reg->periodo_codif.periodo_letra);

        reg++;
    }
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
}
