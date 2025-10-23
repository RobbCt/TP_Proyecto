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
int divisionDecodificarFecha(char *,DIVISION*); //consigna 1

int convertirFechaDecodificadaAString(DIVISION*); // Consigna 2

int normalizarDescr(char *,DIVISION*); //consigna 3

void filtroRegClaf(DIVISION*, char*, char*); //consigna 3

void conversionIndice(DIVISION*); //consigna 4

void divisionParseReg(); //consigna 4 propuesto por robbi

int divisionesArchTextATxt(FILE* archTxt, FILE* archTxt2);

int menu_ipc(FILE*); //p5

//primitivasn't

int regTextABin(DIVISION*, char*); //creamos nuestro hermoso .bin

#endif // FUNCIONES_H_INCLUDED
