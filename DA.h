#ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_

#define INITIAL_CAPACITY 1024
#define DSA static inline

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    void *data;
    size_t element_size;
    size_t len;
    size_t capacity;
} DA;

DSA void DA_init(DA *array, size_t element_size);
DSA void DA_resize(DA *array, size_t new_capacity);
DSA void DA_append(DA *array, const void *element);
DSA void *DA_at(const DA *array, size_t index);
DSA void DA_insert_at(DA *array, size_t index, const void *element);
DSA void DA_free(DA *array);
DSA void DA_sort(DA *array, int(*compare)(const void *, const void *));

#ifdef DA_IMPLEMENTATION

DSA void DA_init(DA *array, size_t element_size)
{
    array->data = malloc(INITIAL_CAPACITY * element_size);
    if (!array->data) {
        fprintf(stderr, "ERROR: Couldn't allocate memory for dynamic\
                array\n");
        return;
    }

    array->element_size = element_size;
    array->len = 0;
    array->capacity = INITIAL_CAPACITY;
}

DSA void DA_resize(DA *array, size_t new_capacity)
{
    void *new_data = realloc(array->data, new_capacity * array->element_size);
    if (new_data) {
        array->data = new_data;
        array->capacity = new_capacity;
    } else {
        fprintf(stderr, "ERROR: Couldn't resize dynamic array");
    }
}

DSA void DA_append(DA *array, const void *element)
{
    if (array->len >= array->capacity) 
        DA_resize(array, array->capacity * 2);

    memcpy((char *)array->data + (array->len * array->element_size),
            element, array->element_size);
    array->len++;
}

DSA void *DA_at(const DA *array, size_t index) 
{
    if (index < array->len) {
        return (char *)array->data + (index * array->element_size);
    }
    return NULL;
}

DSA void DA_insert_at(DA *array, size_t index, const void *element)
{
    if (index < array->len)
        memcpy((char *)array->data + (index * array->element_size),
                element, array->element_size);
}

DSA void DA_free(DA *array)
{
    free(array->data);
    array->data = NULL;
}

DSA void DA_sort(DA *array, int(*compare)(const void *, const void *))
{
    qsort(array->data, array->len, array->element_size, compare);
}

#endif // DA_IMPLEMENTATION

#endif // _DYNAMIC_ARRAY_
