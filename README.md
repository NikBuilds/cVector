# cVector
A dynamic array implemented in C that emulates basic functionality of a C++ vector.  
This project was created to offer a fast and simple solution for dynamic arrays in C and focuses on user-friendliness.

## Build and include
cVector needs a C11 compiler because it relies on `_Generic`. Add `include/` to your include path, compile the three source files together with your own code and include the header:

```C
#include "cvec.h"
```
```Bash
gcc -std=c11 -Iinclude your_code.c src/cvec_core.c src/cvec_global.c src/cvec_init.c -o your_program
```

The included `Makefile` builds the demo in `src/main.c`: `make` builds it, `make run` builds and runs it, `make clean` removes the build folder.

## Features
The library supports all basic datatypes:
- char
- unsigned char
- bool
- short
- int
- unsigned int
- long
- long long
- unsigned long
- insigned long long
- float
- double
- long double
- struct

The `_Generic` keyword in C allows the implementation of type-generic macros that automatically select the correct function based on the argument’s type.
This enables users to call vector functions without manually specifying the underlying data type each time.

When initializing a vector, the desired element type must be explicitly provided.
After initialization, the user can simply call one of the generic macros, and _Generic will route the call to the correct typed wrapper function.

```C
// Creating a int vector
Cvec viInt;
cvec_init(&viInt, int);

// Creating a string vector
Cvec viStr;
cvec_init(&viStr, char*);

// Push values using generic push_back macro
cvec_push_back(&viInt, 1);
cvec_push_back(&viStr, "first");
```

The only exception's are the `cvec_get()` and `emplace_back()` function's. Here, the desired type must be specified with each call.

## Usage
A complete working test is included in **main**, demonstrating each function using the types `int` and `string`. 

### Basics
Every vector is a Cvec. You create it on your own (usually on the stack), initialize it, work with it and free it at the end:
```C
Cvec v;
cvec_init(&v, int);

cvec_push_back(&v, 10);
cvec_push_back(&v, 20);

GetValueInt r = cvec_get(&v, 1, int);
if (r.err == CVEC_OK)
    printf("%d\n", r.value);   // 20

cvec_free(&v);
```

Cvec stores the pointer to the data (`data`), the size of one element (`element_size`), the number of stored elements (`length`), the allocated space in elements (`capacity`) and the element type (`datatype`). You can read length and capacity directly, but don't write to any field yourself.

Almost every function returns a `CvecError`. Always compare it with `CVEC_OK`:
| Code | Meaning |
|---|---|
| `CVEC_OK` | Everything worked |
| `CVEC_ERR_ALLOC` | `malloc`/`realloc`/`strdup` failed |
| `CVEC_ERR_INDEX_OUT_OF_BOUNDS` | Index is outside of the valid range |
| `CVEC_ERR_INVALID_RANGE` | `begin > end` or `end` is outside of the vector |
| `CVEC_ERR_EMPTY` | The operation needs at least one element |
| `CVEC_ERR_TYPE` | Value type does not match the vector's type |
| `CVEC_ERR_NULL_INPUT` | An input array is `NULL` (with `count > 0`) |
| `CVEC_ERR_OVERFLOW` | The new size would overflow `size_t` |
| `CVEC_ERR_NULL` | A passed pointer (vector, value, destination) is `NULL` |
Indices always start at `0`. All functions check their arguments and return an error instead of crashing, so the vector is left unchanged when an error is returned.

## Known issues
When realloc is triggered by doubleling the capacity by adding a new element, the underlying memory block of the vector may move to a new location.
Any pointer previously obtained from v->data becomes dangling (invalid), because it still points to the old memory address which is no longer owned by the vector.

Trying to dereference such a pointer results in undefined behavior, which may lead to a crash, corrupted data, or silent memory errors.

```C
#include <stdio.h>
#include "cvec.h"

int main() 
{
    Cvec v;
    cvec_init(&v, int);

    // Push some values
    for (int i = 0; i < 4; i++) {
        cvec_push_back(&v, i);
    }

    // Store a pointer to an element IN the vector
    int* ptr = (int*)((char*)vi.data + 2 * sizeof(int)); // points to element with value 2

    // Vector is full – next push triggers realloc()
    cvec_push_back(&v, 99);

    // Now ptr is dangling (points to old freed memory)
    printf("ptr = %d\n", *ptr);  // Undefined behavior!

    return 0;
}
```
