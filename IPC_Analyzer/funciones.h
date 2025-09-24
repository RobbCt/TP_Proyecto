#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct
{
    int anio; //4
    int mes; //2
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
DIVISION* divisionDecodificarFecha(DIVISION* registro);


//primitivasn't


#endif // FUNCIONES_H_INCLUDED
