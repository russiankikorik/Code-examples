#include "darray.h"
#include <stdlib.h>

void* darray_create(size_t itemSize) {
	void* darray = malloc(2 * sizeof(size_t));
	size_t* kek = (size_t*)darray;
	kek[0] = 0; //size in BYTES 
	kek[1] = itemSize;
	darray = (void*)((size_t*)darray + 2);

	return darray;
}

void darray_destroy(void* darray, void(*destroy)(void*)) {
	if (darray == NULL) return;
	size_t size = *((size_t*)darray - 2);
	size_t itemSize = *((size_t*)darray - 1);
	if (size % itemSize != 0 || size < 0 || itemSize < 0) return;

	if ( size != 0 && destroy != NULL) {
		for (int i = 0; i < size; i+=itemSize) {
			void* ptr = (void*)((char*)darray + i);
			destroy(ptr);
		}
	}
	free((size_t*)darray - 2);
}

size_t darray_count(const void* darray) {
	if (darray == NULL) return INVALID;
	size_t size = *((size_t*)darray - 2);
	size_t itemSize = *((size_t*)darray - 1);
	if (size % itemSize != 0 || size < 0 || itemSize < 0) return INVALID;

	return size / itemSize;
}

void* darray_item(void* darray, size_t i) {
	if (darray == NULL) return NULL;
	size_t size = *((size_t*)darray - 2);
	size_t itemSize = *((size_t*)darray - 1);
	if (size % itemSize != 0 || size < 0 || itemSize < 0) return NULL;

	if (i > size / itemSize - 1) return NULL;
	void* ptr = (void*)((char*)darray + i * itemSize);
	return ptr;
}

void* darray_add(void** darray_ptr) {
	void* darray = *darray_ptr;
	if (darray == NULL) return NULL;
	size_t size = *((size_t*)darray - 2);
	size_t itemSize = *((size_t*)darray - 1);
	if (size % itemSize != 0 || size < 0 || itemSize < 0) return NULL;

	void* new_darray = malloc(2 * sizeof(size_t) + size + itemSize);
	size_t* kek = (size_t*)new_darray;
	kek[0] = size + itemSize; //размер в байтах
	kek[1] = itemSize;
	new_darray = (void*)((size_t*)new_darray + 2);

	for (size_t j = 0; j < size; j += 1) {
		*((char*)new_darray + j) = *((char*)darray + j);
	}

	for ( size_t j = size ; j < size + itemSize; j += 1) {
		*((char*)new_darray + j) = "\0";
	}

	//BAD

	darray_destroy(darray, NULL);
	*darray_ptr = new_darray;
	void* itemPtr = (void*)((char*)new_darray + size);
	
	return itemPtr;
}

void* darray_insert(void** darray_ptr, size_t i) {
	void* darray = *darray_ptr;
	if (darray == NULL) return NULL;
	size_t size = *((size_t*)darray - 2);
	size_t itemSize = *((size_t*)darray - 1);
	if (size % itemSize != 0 || size < 0 || itemSize < 0) return NULL;

	if (size / itemSize < i) return NULL;

	void* lastPtr = darray_add(darray_ptr);
	darray = *darray_ptr;
	for (int j = (size_t)lastPtr - (size_t)darray - 1; j >= i * itemSize; j-=1) {
		*((char*)darray + j + itemSize) = *((char*)darray + j);
	}

	return (void*)((char*)darray + i * itemSize);

}

void darray_remove(void** darray_ptr, size_t i, void(*destroy)(void*)) {
	void* darray = *darray_ptr;
	if (darray == NULL) return ;
	size_t size = *((size_t*)darray - 2);
	size_t itemSize = *((size_t*)darray - 1);
	if (size % itemSize != 0 || size < 0 || itemSize < 0) return ;

	if (i > size / itemSize - 1) return;

	if (destroy != NULL) {
		void* ptr = (void*)((char*)darray + i * itemSize);
		destroy(ptr);
	}
	
	void* new_darray = malloc(2 * sizeof(size_t) + size - itemSize);
	*((size_t*)new_darray) = size - itemSize; //размер в байтах
	*((size_t*)new_darray + 1) = itemSize;
	new_darray = (void*)((size_t*)new_darray + 2);

	for (size_t j = 0; j < i * itemSize; j += 1) {
		*((char*)new_darray + j) = *((char*)darray + j);
	}

	for (size_t j = (i + 1) * itemSize; j < size; j += 1) {
		*((char*)new_darray + j-itemSize) = *((char*)darray + j);
	}

	
	darray_destroy(darray, NULL);
	*darray_ptr = new_darray;
	
}

