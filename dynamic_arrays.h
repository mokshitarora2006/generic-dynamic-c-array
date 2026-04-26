#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  size_t capacity;
  size_t size;
  size_t element_size;
} metadata;
#define header(s) ((metadata *)((char *)(s) - sizeof(metadata)))
#define push_back(arr, v)                                                      \
  do {                                                                         \
    if (is_full(arr)) {                                                        \
      increase_size_push_back((void **)&(arr));                                \
    }                                                                          \
    (arr)[get_vector_size(arr)] = v;                                           \
    metadata *header = (metadata *)((char *)(arr) - sizeof(metadata));         \
    header->size++;                                                            \
  } while (0)

#define is_full(s) (((header(s))->size == (header(s))->capacity) ? 1 : 0)
#define generate_vector(s) (vector_create(sizeof(s)))
#define get_vector_size(s) ((header(s))->size)
#define get_vector_capacity(s) ((header(s))->capacity)
#define pre_allocation_vector_generation(type, num)                            \
  (vector_create_with_pre_allocation(sizeof(type), num))
#define remove_element(arr, index)                                             \
  do {                                                                         \
    metadata *header = (metadata *)((char *)(arr) - sizeof(metadata));         \
    if ((index) >= header->size) {                                             \
      printf("index out of bounds\n");                                         \
    } else {                                                                   \
      for (int i = index; i < header->size - 1; i++) {                         \
        arr[i] = arr[i + 1];                                                   \
      }                                                                        \
      header->size--;                                                          \
      if (header->size < (header->capacity) / 4 && header->size > 10) {        \
        (header->capacity) /= 2;                                               \
        header = realloc(header, header->capacity * header->element_size +     \
                                     sizeof(metadata));                        \
        if (header == NULL) {                                                  \
          printf("Issues in reallocation of storage\n");                       \
          exit(1);                                                             \
        }                                                                      \
      }                                                                        \
    }                                                                          \
    arr = (void *)(header + 1);                                                \
  } while (0)
#define GET_MACRO(a, b, NAME, ...) NAME
#define create_vector(...)                                                     \
  GET_MACRO(__VA_ARGS__, pre_allocation_vector_generation,                     \
            generate_vector)(__VA_ARGS__)
void *vector_create(size_t el_size);
void increase_size_push_back(void **arr);
void *vector_create_with_pre_allocation(size_t el_size, size_t num);
