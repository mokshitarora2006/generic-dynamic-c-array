#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  size_t capacity;
  size_t size;
  size_t element_size;
} metadata;
#define _header(s) (_get_header(&s))
#define _get_header(s) ((metadata *)(*s) - 1)
#define vector_push_back(arr, v)                                               \
  do {                                                                         \
    if (_is_full(arr)) {                                                       \
      _increase_size_push_back((void **)&(arr));                               \
    }                                                                          \
    (arr)[_get_vector_size(arr)] = v;                                          \
    metadata *header = (metadata *)((char *)(arr) - sizeof(metadata));         \
    header->size++;                                                            \
  } while (0)
#define _is_full(s) ((_header(s)->size == _header(s)->capacity ? 1 : 0))
#define vector_print(s, id)                                                    \
  do {                                                                         \
    metadata *header = _header(s);                                             \
    if (header->size == 0) {                                                   \
      printf("{}\n");                                                          \
    } else {                                                                   \
      printf("{");                                                             \
      for (int i = 0; i < header->size - 1; i++) {                             \
        printf(id, s[i]);                                                      \
        printf(",");                                                           \
      }                                                                        \
      printf(id, s[header->size - 1]);                                         \
      printf("}\n");                                                           \
    }                                                                          \
  } while (0)
#define _generate_vector(s) (_vector_create(sizeof(s)))
#define _get_vector_size(s) ((_header(s))->size)
#define _get_vector_capacity(s) ((header(s))->capacity)
#define vector_free(s) (_free_vector(&s))
#define vector_reuse(s) (_reuse_vector((void **)&s))
#define _pre_allocation_vector_generation(type, num)                           \
  (vector_create_with_pre_allocation(sizeof(type), num))
#define vector_delete_element(arr, index)                                      \
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
    (arr) = (void *)(header + 1);                                              \
  } while (0)
#define GET_MACRO(a, b, NAME, ...) NAME
#define vector_create(...)                                                     \
  GET_MACRO(__VA_ARGS__, _pre_allocation_vector_generation,                    \
            _generate_vector)(__VA_ARGS__)
void *_vector_create(size_t el_size);
void _increase_size_push_back(void **arr);
void *vector_create_with_pre_allocation(size_t el_size, size_t num);
void _free_vector(void **arr);
void _reuse_vector(void **arr);
