#include "funciones.h"

DIVISION* divisionDecodificarFecha(DIVISION* registro)
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
    int mat[9]={7,4,9,8,0,6,1,3,2};

    int cifra[6], i;
    int anio=registro->periodo_codif.anio, mes=registro->periodo_codif.mes;

    *(cifra)=(anio/1000)% 10;
    *(cifra+1)=(anio/100)% 10;
    *(cifra+2)=(anio/10)% 10;
    *(cifra+3)=(anio/1)% 10;

    *(cifra+4)=(mes/10)% 10;
    *(cifra+5)= mes% 10;

    //duda personal: es necesario validar que se decodificaron fechas validas o nel? si es asi validarlo por algun lado¿

    for (i=0;i<=5;i++) //muchas iteraciones, optimizable
    {
        for(int j=0;j<9;j++)
            if(*(mat+j)==*(cifra+i))
            {
                 *(cifra+i)=j;
                 break;
            }
    }

    registro->periodo_codif.anio= *(cifra)*1000+*(cifra+1)*100+*(cifra+2)*10+*(cifra+3);
    registro->periodo_codif.mes= *(cifra+4)*10+*(cifra+5);


    //a todo esto optimizarlo, replazar vectores con aritemtica de punteros
    //ver si se pude remplazar el swicth con macros, validaciones etc etc...

    return registro;
    //fijate como hace las funciones de este tipo el profe
    //opciones->    retornar direccion (ambiguo)/ trabajar con la direccion y no retornar nada
}
