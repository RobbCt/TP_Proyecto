#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

//biblio standar
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

//define's
#define MAXTAMREG 4096
#define CANTMAXCHAR 17
#define MESES 12
#define INCR_FACTOR 2
#define DEFAULT_CAP 10

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
    FECHA periodo_codif;
}DIVISION;

typedef struct
{
    DIVISION *vec;
    size_t ce;
    size_t cap;
}VecDIVISION;

typedef struct
{
    FECHA f;
    char descrip[81];
    double ind_ipc;
    char region[30];
    char grup[10];
}GRUPO;


//Primitivas

int divisionesArchTextAVar(FILE*,VecDIVISION*);

int divisionDecodificarFecha(char*,DIVISION*);

int divisionFechDecodAStr(DIVISION*);

int divisionSetString(char*,char*);

int divisionSetDouble(char*,double*);

int divisionNormalizarDescr(char*,DIVISION*);


//primitivasn't

int regTextAVar(DIVISION*,char*);

int ajustarMontoIPC(VecDIVISION*, double, int, FECHA, FECHA);

int menu_ipc(VecDIVISION* );




//memoria dianmica

bool vectorCrear(VecDIVISION*);

bool vectorAgregar(DIVISION*, VecDIVISION*);

void vectorDestruir(VecDIVISION*);


#endif // FUNCIONES_H_INCLUDED
