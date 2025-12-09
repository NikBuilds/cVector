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

The '_Generic' keyword is used to implement type-generic code that automatically selects the appropriate function based on the argument’s type.
This allows users to call vector operations without explicitly specifying the underlying data type.  
By initilaising a vector

When initializing a vector, the intended type must be specified. Afterwards, the desired generic macro function can simply be called.  

```C
// Creating a int vector
Cvec viInt;
cvec_init(&viInt, int);

// Creating a string vector
Cvec viStr;
cvec_init(&viStr, int);

cvec_push_back(&viInt, 1);
cvec_push_back(&vsStr, "first");
```
