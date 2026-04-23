#pragma once
#include <stdio.h>
#include <stdlib.h>
#define header(s) ((metadata *)((char *)(s) - sizeof(metadata)))
#define is_full(s) (((header(s))->size == (header(s))->capacity) ? 1 : 0)
#define generate_vector(s) (create_vector(sizeof(s)))
#define get_vector_size(s) ((header(s))->size)
#define get_vector_capacity(s) ((header(s))->capacity)
#define push_back(arr, v)                                                      \
  do {                                                                         \
    if (is_full(arr)) {                                                        \
      increase_size_push_back((void **)&(arr));                                \
    }                                                                          \
    (arr)[get_vector_size(arr)] = v;                                           \
    metadata *header = (metadata *)((char *)(arr) - sizeof(metadata));         \
    header->size++;                                                            \
  } while (0)

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
  } while (0)
typedef struct {
  size_t capacity;
  size_t size;
  size_t element_size;
} metadata;
void *create_vector(size_t el_size);
void increase_size_push_back(void **arr);
