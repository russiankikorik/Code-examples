#include <stdbool.h> // bool
#include <stddef.h>  // size_t

static const size_t INVALID = ~((size_t)0);

void* darray_create(size_t itemSize); //������ ������ ������ � �������� �������� itemSize.
void darray_destroy(void* darray, void(*destroy)(void*)); //���������� ������, ���� ������� ������� ���������� ��� �������� - ��������������� ��������� ����� ���������.

size_t darray_count(const void* darray); //���������� ����� ��������� � �������, ��� ���������� ��������� ���������� INVALID.
void* darray_item(void* darray, size_t i); //���������� ��������� �� ������� �� ������� ��������, �� ��������� ������� ���������� NULL. ��� ���������� ��������� ���������� NULL.
//��������� ������� ���������� darray_ptr -> darray � ����� ���������� �������������� darray ��� ������� ����������
void* darray_add(void** darray_ptr); //��������� ������� � ����� �������, ���������� ��������� �� ����������� �������. ��� ���������� ��������� ���������� NULL.
void* darray_insert(void** darray_ptr, size_t i); //��������� ������� � ��������/������ �������, ��� �������� ������� �� ��������� ������� ���������� NULL. ��� ���������� ��������� ���������� NULL.
void darray_remove(void** darray_ptr, size_t i, void(*destroy)(void*)); //������� ������� �� �������. ��� ���������� ��������� ���������� NULL.
