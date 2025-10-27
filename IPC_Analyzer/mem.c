//biblio standar
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//biblio
#include "mem.h"

//vectorCrear(dir var tipo vecGenerico, tam de elemento)
bool vectorCrear(VecGenerico* vec, size_t tam)
{
    vec->vec = malloc(tam * DEFAULT_CAP);

    if(!(vec->vec))
    {
        vec->cap = 0;
        vec->ce = 0;
        return false;
    }

    vec->ce = 0;
    vec->cap = DEFAULT_CAP;

    return true;
}

//vectorAgregar(dir elemento, dir vector, tam del elemento)
bool vectorAgregar(void* elem, VecGenerico* vec, size_t tam)
{
    if (vec->ce >= vec->cap)
    {
        if(!redimensionarVector(vec,vec->cap * INCR_FACTOR,tam))
            return false;
    }

    memcpy((char*)vec->vec + vec->ce * tam, elem, tam);
    vec->ce++;

    return true;
}

//redimensionarVector(dir var tipo vecGenerico, nueva cantidad de indices, tam del elemento)
bool redimensionarVector(VecGenerico* vec,size_t cap,size_t tam)
{
    void* temporal = realloc(vec->vec, cap * tam);

    if(!(temporal))
    {
        return false;
    }

    vec->vec = temporal;
    vec->cap = cap;

    return true;
}

//vectorDestruir(dir var tipo VecGenerico)
void vectorDestruir(VecGenerico* vec)
{
    free(vec -> vec);
    vec->vec = NULL;
    vec->ce = 0;
    vec->cap = 0;
}


