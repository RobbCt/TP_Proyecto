#include "funciones.h"
#define MESES 12
#define CANTMAXCHAR 17


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
    *(cifra+3)=(anio/1)% 10;

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

