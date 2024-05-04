#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Error.h"

typedef struct {
	void** _array;   /* array that holds objects of type 'void*' */
	size_t _length; /* the amount of items in the array - its length */
} vector;

typedef int (*vector_opfunc)(void*, void*);

vector* vector_ctor();
void vector_dtor(vector* vec);

void vector_append(vector* vec, void* item);

void vector_insert(vector* vec, void* item, int index);
void* vector_delete(vector* vec, int index);

void vector_swap(vector* vec, int i1, int i2);
void vector_sort(vector* vec, vector_opfunc opfunc);
int vector_find(vector* vec, vector_opfunc opfunc, void* item);

#endif