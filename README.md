# cVector
A dynamic array implemented in C that emulates basic functionality of a C++ vector.  
This project was created to offer a fast and simple solution for dynamic arrays in C and focuses on user-friendliness.

## Features
It supports all basic datatypes:
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
cvec_init(&viStr, int);

// Push values using generic push_back macro
cvec_push_back(&viInt, 1);
cvec_push_back(&viStr, "first");
```

The only exception is the `cvec_get()` function. Here, the desired type must be specified with each call.

## Usage
This section explains all functions supported by cVector.  
A complete working test is included in **main**, demonstrating each function using the types `int` and `string`. 

### push_back()  
This function add's a copy of an element at the **end** of the vector.  
When the vector is full (i.e., `length == capacity`), the capacity is automatically doubled.  

### get_copy()  


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
