#include "funciones.h"


Division* divisionDecodificarFecha(Division* registro)
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

    int cifra[5], i;

    //ej: 123456
    cifra[0] = registro->periodo_codif / 100000 % 10;  // 1
    cifra[1] = registro->periodo_codif / 10000 % 10;   // 2
    cifra[2] = registro->periodo_codif / 1000 % 10;    // 3
    cifra[3] = registro->periodo_codif / 100 % 10;     // 4
    cifra[4] = registro->periodo_codif / 10 % 10;      // 5
    cifra[5] = registro->periodo_codif % 10;           // 6

    for (i=0;i<=5;i++)
    {
        switch(cifra[i])
        {
            case 7:cifra[i] = 0;
            break;
            case 4:cifra[i] = 1;
            break;
            case 9:cifra[i] = 2;
            break;
            case 8:cifra[i] = 3;
            break;
            case 0:cifra[i] = 4;
            break;
            case 6:cifra[i] = 5;
            break;
            case 1:cifra[i] = 6;
            break;
            case 3:cifra[i] = 7;
            break;
            case 2:cifra[i] = 8;
            break;
        }

    }

    registro->periodo_codif =  cifra[0] * 100000 +
                               cifra[1] * 10000 +
                               cifra[2] * 1000 +
                               cifra[3] * 100 +
                               cifra[4] * 10 +
                               cifra[5];

    //a todo esto optimizarlo, replazar vectores con aritemtica de punteros
    //ver si se pude remplazar el swicth con macros, validaciones etc etc...

    return registro;
    //fijate como hace las funciones de este tipo el profe
    //opciones->    retornar direccion (ambiguo)/ trabajar con la direccion y no retornar nada
}







