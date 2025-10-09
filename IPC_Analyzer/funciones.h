#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <ctype.h>



typedef struct
{
    int anio; //4
    int mes; //2
    char periodo_letra[17];
}FECHA;

typedef struct
{
    char cod[21];
    char descrip[31];
    char clasif[31];
    double ind_ipc;
    double v_m_ipc;
    double v_i_a_ipc;
    char region[10];
    FECHA periodo_codif; //asi tenemos separada la fecha(capaz lo necesitemos mas adelante)
}DIVISION;

//Primitivas
void divisionDecodificarFecha(DIVISION*); //consigna 1

void convertirFechaDecodificadaAString(DIVISION*); // Consigna 2

void normalizarDescr(DIVISION*); //consigna 3 y medio¿

void filtroRegClaf(DIVISION*, char*, char*);//necesaria??? parte de consigna 3

void conversionIndice(DIVISION*);//consigna 4

//primitivasn't


#endif // FUNCIONES_H_INCLUDED
