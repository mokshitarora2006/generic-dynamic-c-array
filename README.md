
# dynamic-c-array

This library provides support for dynamic arrays in C using `malloc`, `realloc`, and macros.

It works by storing metadata directly before the array in memory. The library is generic and can be used with any data type.

To reduce frequent `realloc` calls, the array grows dynamically when full and shrinks when usage falls below 25% of the allocated capacity.

---

## Features

* Generic dynamic arrays for any data type
* Automatic resizing using `realloc`
* Metadata stored internally
* Simple macro-based API
* Pre-allocation support
* Contiguous memory layout

---

## Building

Compile using GCC:

```bash id="j8okd0"
gcc main.c dynamic_arrays.c -o app
```

Run:

```bash id="z5ejdc"
./app
```

---

## Example

```c id="xeh70p"
#include "dynamic_arrays.h"

int main(void) {
    int *arr = vector_create(int);

    vector_push_back(arr, 10);
    vector_push_back(arr, 20);
    vector_push_back(arr, 30);

    vector_print(arr, "%d");

    vector_delete_element(arr, 1);

    vector_print(arr, "%d");

    vector_reuse(arr);

    vector_print(arr, "%d");

    vector_free(arr);

    return 0;
}
```

---

## API

* `vector_create()`

  Creates a dynamic array.

  * With default capacity:

    ```c
    vector_create(int)
    ```

  * With custom initial capacity:

    ```c
    vector_create(int, initial_size)
    ```

---

* `vector_push_back()`

  Appends an element to the dynamic array.

  * Syntax:

    ```c
    vector_push_back(arr, value)
    ```

---

* `vector_delete_element()`

  Deletes an element by index and shifts all subsequent elements one position back.

  * Syntax:

    ```c
    vector_delete_element(arr, index)
    ```

---

* `vector_print()`

  Prints the array using the supplied format specifier.

  * Syntax:

    ```c
    vector_print(arr, "%d")
    ```

---

* `vector_reuse()`

  Resets the vector size to `0` without freeing the allocated memory.

  This allows the same vector to be reused while avoiding repeated memory allocations.

  * Syntax:

    ```c
    vector_reuse(arr)
    ```

---

* `vector_free()`

  Frees the memory allocated for the dynamic array.

  * Syntax:

    ```c
    vector_free(arr)
    ```

---

## Internal Design

The vector internally stores metadata before the actual array memory.

The metadata contains:

* Current size
* Capacity
* Element size

This allows the library to expose a clean array-like interface while still supporting dynamic resizing internally.
