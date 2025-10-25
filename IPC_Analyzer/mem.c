
//biblio standar
#include <stdbool.h>

//vectorCrear(dir var tipo VecGenerico, tam de elemento)
bool vectorCrear(VecGenerico* vec,size_t tam)
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
        // Redimensionar
        size_t nueva_cap = vec->cap * INCR_FACTOR;
        void* temporal = realloc(vec->vec,nueva_cap * tam);

        if (!temporal)
            return false;

        vec->vec = temporal;
        vec->cap = nueva_cap;
    }

    memcpy((char*)vec->vec + vec->ce * tam, elem, tam);
    vec->ce++;

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
