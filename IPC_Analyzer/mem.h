#ifndef MEM_H_INCLUDED
#define MEM_H_INCLUDED

//biblio standar
#include <stdbool.h>

//define's
#define INCR_FACTOR 2
#define DEFAULT_CAP 10

typedef struct
{
    void *vec;
    size_t ce;
    size_t cap;
}VecGenerico;

bool vectorCrear(VecGenerico*,size_t);

bool vectorAgregar(void*, VecGenerico*, size_t);

bool redimensionarVector(VecGenerico*,size_t,size_t);

void vectorDestruir(VecGenerico*);

#endif // MEM_H_INCLUDED
