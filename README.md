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
cvec_push_back(&vsStr, "first");
```

The only exception is the `cvec_get()` function. Here, the desired type must be specified with each call.

## Usage
