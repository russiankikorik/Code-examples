#include <stdbool.h> // bool
#include <stddef.h>  // size_t

static const size_t INVALID = ~((size_t)0);

void* darray_create(size_t itemSize); //Создаёт пустой массив с размером элемента itemSize.
void darray_destroy(void* darray, void(*destroy)(void*)); //Уничтожает массив, если указана функция деструктор для элемента - последовательно применяет перед удалением.

size_t darray_count(const void* darray); //Возвращает число элементов в массиве, при невалидном указателе возвращает INVALID.
void* darray_item(void* darray, size_t i); //Возвращает указатель на элемент по индексу элемента, за пределами массива возвращает NULL. При невалидном указателе возвращает NULL.
//следуюшие функции используют darray_ptr -> darray в целях обновления идентификатора darray без прямого присвоения
void* darray_add(void** darray_ptr); //Добавляет элемент в конец массива, возвращает указатель на вставленный элемент. При невалидном указателе возвращает NULL.
void* darray_insert(void** darray_ptr, size_t i); //Вставляет элемент в середину/начало массива, при указании индекса за пределами массива возвращает NULL. При невалидном указателе возвращает NULL.
void darray_remove(void** darray_ptr, size_t i, void(*destroy)(void*)); //Удаляет элемент из массива. При невалидном указателе возвращает NULL.
