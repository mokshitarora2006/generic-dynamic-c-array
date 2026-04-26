#include "dynamic_arrays.h"
void *vector_create(size_t el_size) {
  size_t initial_size = 10;
  metadata *header = malloc(sizeof(metadata) + initial_size * el_size);
  if (header == NULL) {
    printf("Issues in allocation of memory\n");
    exit(1);
  }
  header->size = 0;
  header->capacity = initial_size;
  header->element_size = el_size;
  return (void *)(header + 1);
}
void *vector_create_with_pre_allocation(size_t el_size, size_t num) {
  size_t initial_size = num;
  metadata *header = malloc(sizeof(metadata) + initial_size * el_size);
  if (header == NULL) {
    printf("Issues in allocation of memory\n");
    exit(1);
  }
  header->size = 0;
  header->capacity = initial_size;
  header->element_size = el_size;
  return (void *)(header + 1);
}
void increase_size_push_back(void **arr) {
  metadata *header = (metadata *)(*arr) - 1;
  if (header->capacity == header->size) {
    header->capacity *= 2;
    header = realloc(header, header->capacity * header->element_size +
                                 sizeof(metadata));
    if (header == NULL) {
      printf("Issues in reallocation of storage\n");
      exit(1);
    }
    (*arr) = (void *)(header + 1);
  }
}
