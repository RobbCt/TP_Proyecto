#include "funciones.h"


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


    int cifra[6], i;
    int anio=registro->periodo_codif.anio, mes=registro->periodo_codif.mes;

    *(cifra)=(anio/1000)% 10;
    *(cifra+1)=(anio/100)% 10;
    *(cifra+2)=(anio/10)% 10;
    *(cifra+3)=(anio/1)% 10;

    *(cifra+4)=(mes/10)% 10;
    *(cifra+5)= mes% 10;

    //duda personal: es necesario validar que se decodificaron fechas validas o nel? si es asi validarlo por algun lado¿
    int j;

    for (i=0;i<6;i++) //muchas iteraciones, optimizable
    {
        j = 0;
        while(*(vec+j) != *(cifra+i))
        {
            j++;
        }

        *(cifra+i) = j;
    }

    registro -> periodo_codif.anio = *(cifra)*1000 + *(cifra+1)*100 + *(cifra+2)*10 + *(cifra+3);
    registro -> periodo_codif.mes = *(cifra+4)*10 + *(cifra+5);


    //a todo esto optimizarlo, replazar vectores con aritemtica de punteros
    //ver si se pude remplazar el swicth con macros, validaciones etc etc...
    //fijate como hace las funciones de este tipo el profe
    //opciones->    retornar direccion (ambiguo)/ trabajar con la direccion y no retornar nada
}

void convertirFechaDecodificadaAString(DIVISION* reg) // Consigna 2
{
    //char stringFecha[17]; // 9 caracteres para el mes de nombre más largo ("septiembre"), 3 caracteres para la cadena " - ", 4 para el año y uno para el carácter de fin de línea
    char nombreMes[17];
    strcpy(nombreMes, reg->periodo_codif.periodo_letra);

    int mes = reg->periodo_codif.mes;

    int anio = reg->periodo_codif.anio;

    char anio_s[20];

    switch(mes)
    {
        case 1:
            strcpy(nombreMes, "Enero");
            break;
        case 2:
            strcpy(nombreMes, "Febrero");
            break;
        case 3:
            strcpy(nombreMes, "Marzo");
            break;
        case 4:
            strcpy(nombreMes, "ABril");
            break;
        case 5:
            strcpy(nombreMes, "Mayo");
            break;
        case 6:
            strcpy(nombreMes, "Junio");
            break;
        case 7:
            strcpy(nombreMes, "Julio");
            break;
        case 8:
            strcpy(nombreMes, "Agosto");
            break;
        case 9:
            strcpy(nombreMes, "Septiembre");
            break;
        case 10:
            strcpy(nombreMes, "Octubre");
            break;
        case 11:
            strcpy(nombreMes, "Noviembre");
            break;
        case 12:
            strcpy(nombreMes, "Diciembre");
            break;
      /*  case default:
            printf("\nError");
            getch();
            exit(1);
            break;  Nunca va a llegar a este break si se ejecuta exit(1) previamente. */
    }

    strcat(nombreMes, " - ");
    sprintf(anio_s, "%d", anio);
    strcat(nombreMes, anio_s);

    printf("\n%s", nombreMes);
}
