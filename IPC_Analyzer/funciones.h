#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

//biblio standar
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

//define's
#define MAXTAMREG 160

typedef struct
{
    int anio; //4 cifras
    int mes; //2 cifras
    char periodo[17]; //chars para formato: 9 mes, 3 separador, 4 anio, 1 \0
}FECHA;

typedef struct
{
    char cod[21];
    char descrip[81];
    char clasif[51];
    double ind_ipc;
    double v_m_ipc;
    double v_i_a_ipc;
    char region[30];
    FECHA periodo_codif; //asi tenemos separada la fecha(capaz lo necesitemos mas adelante)
}DIVISION;

//Primitivas
void divisionDecodificarFecha(DIVISION*); //consigna 1

void convertirFechaDecodificadaAString(DIVISION*); // Consigna 2

void normalizarDescr(DIVISION*); //consigna 3

void filtroRegClaf(DIVISION*, char*, char*);//consigna 3

void conversionIndice(DIVISION*);//consigna 4

void divisionParsearCampo();//consigna 4 propuesto por robbi

void parsearRegistro(DIVISION*, char*); //creamos nuestro hermoso .bin

//primitivasn't


#endif // FUNCIONES_H_INCLUDED
