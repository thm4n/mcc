#include "vector.h"

#define VEC_ERR_MEM_ALLOC    "vector: could not allocate memory"
#define VEC_ERR_NULL_REC     "vector: recieved NULL"
#define VEC_ERR_OUT_OF_BOUND "vector: index out of vector bounds"

/*
 * vector_ctor
 * constructor for the vector structure - initializes the data for further use.
 * 
 * output:
 *  - vector* - the address of the initialized vector.
 * 
 */
vector* vector_ctor(void) {
	vector* vec = (vector*)malloc(sizeof(vector));
	if(!vec) 
		exitWithError(_errcode_external, VEC_ERR_MEM_ALLOC);
		
	vec->_array = NULL;
	vec->_length = 0;

	return vec;
}

/*
 * vector_dtor
 * deconstructor for the vector structure - frees allocated memory by the constructor and other vector functions.
 * 
 * NOTE: freeing the objects held in the array are the programmer's responsiblity, as they were not allocated by the vector functions.
 * 
 * input:
 *  - vec - the vector to deconstruct and free.
 * 
 */
void vector_dtor(vector* vec) { 
	if(vec) {
		if(vec->_array)
			free(vec->_array);
		free(vec);	
	}
}

/*
 * vector_append
 * appends an item to the given vector structure at the vector's end.
 * 
 * input:
 *  - vec - the vector to add the item to.
 *  - item - the item to add
 * 
 */
void vector_append(vector* vec, void* item) {
	if(!vec)
		exitWithError(_errcode_external, VEC_ERR_NULL_REC);

	if(!vec->_array) {
		vec->_array = (void**)malloc(sizeof(void*));
		if(!vec->_array)
			exitWithError(_errcode_external, VEC_ERR_MEM_ALLOC);
	}
	else {
		vec->_array = (void**)realloc(vec->_array, sizeof(void*) * (vec->_length + 1));
		if(!vec->_array)
			exitWithError(_errcode_external, VEC_ERR_MEM_ALLOC);
	}
	vec->_array[vec->_length++] = item; 
}

/*
 * vector_insert
 * inserts an item to the given vector structure at the given index.
 * 
 * input:
 *  - vec - the vector to insert the item to.
 *  - index - the index of the new item to insert.
 * 
 */
void vector_insert(vector* vec, void* item, int index) {
	void** tmp = NULL;
	int i, j;

	if(!vec)
		exitWithError(_errcode_external, VEC_ERR_NULL_REC);

	if(!vec->_array) 
		exitWithError(_errcode_external, VEC_ERR_OUT_OF_BOUND);

	if(index > vec->_length || index < 0)
		exitWithError(_errcode_external, VEC_ERR_OUT_OF_BOUND);

	tmp = vec->_array;
	vec->_length++;
	vec->_array = (void**)malloc(sizeof(void*) * vec->_length);

	j = 0;
	for(i = 0; i < vec->_length; i++) {
		if(j == index)
			vec->_array[i++] = item;
		vec->_array[i] = tmp[j++];
	}

	free(tmp);
}

/*
 * vector_delete
 * deletes an item from the given vector structure at the given index.
 * 
 * input:
 *  - vec - the vector to delete the item from.
 *  - index - the index of the item to delete.
 * 
 */
void* vector_delete(vector* vec, int index) {
	void** tmp = NULL;
	void* obj = NULL;
	int i, j;

	if(!vec)
		exitWithError(_errcode_external, VEC_ERR_NULL_REC);
	
	if(!vec->_array)
		return NULL;

	if(index >= vec->_length)
		return NULL;

	vec->_length--;
	tmp = malloc(sizeof(void*) * vec->_length);

	obj = vec->_array[index];

	j = 0;
	for(i = 0; i < vec->_length; i++) {
		if(j == index) j++;
		tmp[i] = vec->_array[j++];
	}

	free(vec->_array);
	vec->_array = tmp;

	return obj;
}

/*
 * vector_swap
 * swaps to items by index in the given vector.
 * 
 * input:
 *  - vec - the vector to swap items in.
 *  - i1 - the index of the first item.
 *  - i2 - the index of the second item.
 * 
 */
void vector_swap(vector* vec, int i1, int i2) {
	void* tmp = NULL;
	
	if(!vec)
		exitWithError(_errcode_external, VEC_ERR_NULL_REC);
	
	if(i1 >= vec->_length || i2 >= vec->_length)
		exitWithError(_errcode_external, VEC_ERR_OUT_OF_BOUND);

	tmp = vec->_array[i1];
	vec->_array[i1] = vec->_array[i2];
	vec->_array[i2] = tmp;
}

/*
 * vector_sort
 * sorts the vector array by the user's needs.
 * 
 * input:
 *  - vec - the vector to sort
 *  - opfunc - the binary function that is given by the user to determine if two items should be swapped or not.
 * 
 */
void vector_sort(vector* vec, vector_opfunc opfunc) {
	int i, j;
	int swapped = 0;
	for(i = 0; i < vec->_length - 1; i++) {
		swapped = 0;
		for(j = 0; j < vec->_length - i - 1; j++) {
			if(opfunc(vec->_array[j], vec->_array[j + 1])) {
				vector_swap(vec, j, j+1);
				swapped = 1;
			}
		}
		
		if(!swapped) 
			break;
	}
}

/*
 * vector_find
 * finds the index of the first item in the vector array that matches the item by the user's needs.
 * 
 * input:
 *  - vec - the vector to find the item in.
 *  - opfunc - the binary function that is given by the user to determine if two items are equal.
 *  - item - the item to search for in the vector.
 * 
 * output:
 *  - int - the index of the first occurance of the item given by the user. if found - returns the index. otherwise - returns (-1)
 * 
 */
int vector_find(vector* vec, vector_opfunc opfunc, void* item) {
	int i;
	for(i = 0; i < vec->_length; i++)
		if(opfunc(vec->_array[i], item))
			return i;
	return -1;
}