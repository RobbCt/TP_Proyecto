#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

//biblio standar
#include <string.h>
#include <stdio.h>
#include <ctype.h>

//biblio
#include "mem.h"

//define's
#define MAXTAMREG 4096
#define CANTMAXCHAR 17
#define MESES 12

typedef struct
{
    int anio; //4 cifras
    int mes; //2 cifras
    char per[17]; //chars para formato: 9 mes, 3 separador, 4 anio, 1 \0
}FECHA;

typedef struct
{
    FECHA f;
    char descrip[81];
    double ind_ipc;
    char region[30];
    char grup[10];
}GRUPO;

typedef struct
{
    char cod[21];
    char descrip[81];
    char clasif[51];
    double ind_ipc;
    double v_m_ipc;
    double v_i_a_ipc;
    char region[30];
    FECHA periodo;
}DIVISION;

typedef struct
{
    char cod[21];
    char descrip[81];
    char clasif[51];
    FECHA periodo; //el espacio en char será utilizado para escribir anio-mes-dia en str
    double ind_ipc;
    double v_m_ipc;
    double v_i_a_ipc;
    char region[30];
}APERTURA;
//para apertura, tenemos que acumular los montos mes a mes
typedef struct {
    FECHA f;
    double ipc;
    double montoAjustado;
    double variacionAcum;
}TABLA;

//Primitivas

int divisionesArchTextAVar(FILE*,VecGenerico*);

int divisionDecodificarFecha(char*,DIVISION*);

int divisionFechDecodAStr(DIVISION*);

int setString(char*,char*);

int setDouble(char*,double*);

int divisionNormalizarDescr(char*,DIVISION*);


//primitivasn't

int regTextADiv(DIVISION*,char*);

int menu_ipc(VecGenerico*, int);

int ajustarMontoIPC(VecGenerico*, double, int, FECHA, FECHA, int);

int grupoClasif(VecGenerico*,VecGenerico*);

int ordPorReg(VecGenerico*);

int ordFechaDeRegion(VecGenerico*);

int conversionFecha(char*, APERTURA*);

int regTextAAp(APERTURA *, char *);

int aperturasArchTextAVar(FILE*,VecGenerico*);

#endif // FUNCIONES_H_INCLUDED
