#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "darray.h"

typedef struct {
    int array[8];
    float d_variable;
} Value;

void destroy_Value(void* ptrValue) {
    printf("DESTRRRUCTION!!!");
}

int main(int argc, char* argv[])
{
    //Создаем динамический массив с элементами типа Value;
    void* darray = darray_create(sizeof(Value));

    assert(0 == darray_count(darray));

    //Создаем объекты для динамического массива
    Value value0 = { {1, 2, 3, 4, 5, 6, 7, 8}, 0.f };
    Value value1 = { {8,7,6,5,4,3,2,1}, 1.5f };
    Value value2 = { {10, 20, 30, 40, 50, 60, 70, 80}, 228.f };

    //Добавляем ПЕРВЫЙ элемент в динамический массив

    Value* insertedValue0 = (Value*)darray_add(&darray);

    assert(1 == darray_count(darray));

    *insertedValue0 = value0;

    Value* item = (Value*)darray_item(darray, 0);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value0.array[i]);
    }

    assert(fabsf(item->d_variable - value0.d_variable) < 1e-10f);
    assert(NULL == darray_item(darray, 1));
    
    //Добавляем ВТОРОЙ элемент в динамический массив
    Value* insertedValue2 = (Value*)darray_add(&darray);

    *insertedValue2 = value2;

    item = (Value*)darray_item(darray, 1);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value2.array[i]);
    }

    assert(fabsf(item->d_variable - value2.d_variable) < 1e-10f);
    assert(NULL == darray_item(darray, 2));

    //Вставляем ТРЕТИЙ элемент в динамический массив между двумя имеющимися
    Value* insertedValue1 = (Value*)darray_insert(&darray, 1);

    *insertedValue1 = value1;

    item = (Value*)darray_item(darray, 1);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value1.array[i]);
    }

    assert(fabsf(item->d_variable - value1.d_variable) < 1e-10f);
    assert(NULL == darray_item(darray, 3));

    item = (Value*)darray_item(darray, 0);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value0.array[i]);
    }

    assert(fabsf(item->d_variable - value0.d_variable) < 1e-10f);

    item = (Value*)darray_item(darray, 2);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value2.array[i]);
    }

    assert(fabsf(item->d_variable - value2.d_variable) < 1e-10f);

    //проверка работоспособности синтаксиса массивов

    Value* Value_darray = (Value*)darray;
    
    for (size_t i = 0; 8 > i; ++i) {
        assert((1[Value_darray]).array[i] == value1.array[i]);
    }


    //Убираем центральный элемент

    darray_remove(&darray, 1, &destroy_Value);

    item = (Value*)darray_item(darray, 0);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value0.array[i]);
    }

    assert(fabsf(item->d_variable - value0.d_variable) < 1e-10f);
    assert(NULL == darray_item(darray, 2));

    item = (Value*)darray_item(darray, 1);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value2.array[i]);
    }

    assert(fabsf(item->d_variable - value2.d_variable) < 1e-10f);

    assert(2 == darray_count(darray));

    //Возвращаем центральный элемент

    insertedValue1 = (Value*)darray_insert(&darray, 1);

    *insertedValue1 = value1;

    //Убираем первый элемент

    darray_remove(&darray, 0, &destroy_Value);

    assert(2 == darray_count(darray));

    item = (Value*)darray_item(darray, 0);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value1.array[i]);
    }

    assert(fabsf(item->d_variable - value1.d_variable) < 1e-10f);
    assert(NULL == darray_item(darray, 2));

    item = (Value*)darray_item(darray, 1);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value2.array[i]);
    }

    assert(fabsf(item->d_variable - value2.d_variable) < 1e-10f);

    //Убираем последний элемент

    darray_remove(&darray, 1, &destroy_Value);

    item = (Value*)darray_item(darray, 0);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value1.array[i]);
    }

    assert(fabsf(item->d_variable - value1.d_variable) < 1e-10f);
    assert(NULL == darray_item(darray, 1));

    darray_destroy(darray, &destroy_Value);

    void* lulz = malloc(10);
 
    _CrtDumpMemoryLeaks();
    return 0;
}