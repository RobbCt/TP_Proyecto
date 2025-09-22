#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED



typedef struct
{
    char cod[21];
    char descrip[31];
    char clasi[31];
    double float ind_ipc;
    double float v_m_ipc;
    double float V_i_a_ipc;
    char region[10];
    int periodo_codif;

}Division;


//Primitivas
Division* divisionDecodificarFecha(Division*);




//primitivasn't





#endif // FUNCIONES_H_INCLUDED
