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

---
 
### `cvec_init(v, type)`
 
Prepares an empty vector for elements of the given `type`.
 
```c
Cvec a; cvec_init(&a, int);
Cvec b; cvec_init(&b, char*);     // string vector
Cvec c; cvec_init(&c, Person);    // any struct
```
 
- `type` is written as a type, not as a value: `int`, `double`, `char*`, `Person`.
- No memory is allocated yet. `data` is `NULL` and `capacity` is `0`. The first `push_back` allocates.
- The macro passes `sizeof(type)` to the matching init function, which checks that it fits the type. Every type that is not in the list above is treated as a struct.
- A vector has a fixed type. Afterwards, functions with a different value type return `CVEC_ERR_TYPE`.
- Do not call `cvec_init` on a vector that already holds data, otherwise its memory is lost (call `cvec_free` first).
---
 
### `cvec_push_back(v, value)`
 
Appends a **copy** of `value` at the end.
 
```c
cvec_push_back(&v, 42);
cvec_push_back(&strings, "hello");
```
 
**How it works:** If `length == capacity`, the capacity doubles (`0 → 1 → 2 → 4 → 8 …`) and the block is enlarged with `realloc`. Then the value is copied to position `length`, and `length` goes up by one. Doubling keeps pushing cheap on average (amortized O(1)), because a reallocation only happens rarely.
 
**Watch out:**
- The literal's type decides which function is used: `1` is an `int`, `1L` a `long`, `1.0f` a `float`, `1.0` a `double`. If it doesn't match the vector, you get `CVEC_ERR_TYPE`. Use a cast (e.g. `(short)5`) when needed.
- **Strings:** the text is copied with `strdup`. The vector owns that copy, so you can pass literals, stack buffers or temporary strings. The copies are released by `cvec_free`.
- Pointers into the vector become invalid after a push (see [Known issues](#known-issues)).
---

### `cvec_get(v, index, type)`
 
Reads the element at `index` and returns it wrapped in a result struct (`GetValueInt`, `GetValueDouble`, `GetValueString`, …).
 
```c
GetValueInt r = cvec_get(&v, 2, int);
if (r.err == CVEC_OK)
    printf("%d\n", r.value);
 
GetValueString s = cvec_get(&strings, 0, char*);
```
 
- Unlike the other macros, the **type must be passed** here, because the return type depends on it.
- The struct has two members: `value` and `err`. **Check `err` before you use `value`**; on an error `value` is not meaningful.
- Errors: `CVEC_ERR_EMPTY`, `CVEC_ERR_INDEX_OUT_OF_BOUNDS`, `CVEC_ERR_NULL`. The wrappers currently report all of them as `CVEC_ERR_INDEX_OUT_OF_BOUNDS`.
- For numbers you get a copy. For strings, `value` is the **pointer to the vector's own string**, not a new copy. Do not `free` it and do not use it after the element was replaced, erased or the vector was freed. Copy it with `strdup` if you need it longer.
- Structs have no `cvec_get`. Use `cvec_emplace_back` to write and read them via `v.data` (see below).
---
 
### `cvec_replace(v, index, value)`
 
Overwrites the element at `index` with `value`. The length does not change.
 
```c
cvec_replace(&v, 2, 42);
cvec_replace(&strings, 0, "new text");
```
 
- Only works on existing elements: an empty vector returns `CVEC_ERR_EMPTY`, an index `>= length` returns `CVEC_ERR_INDEX_OUT_OF_BOUNDS`.
- Same rules for the value type as `cvec_push_back`. Strings are copied with `strdup`.
---
 
### `cvec_insert(v, index, value)`
 
Inserts `value` at `index` and shifts all following elements one place to the right. The length grows by one.
 
```c
// before: [1, 2, 3]
cvec_insert(&v, 1, 99);
// after:  [1, 99, 2, 3]
```
 
**How it works:** If the vector is full, the capacity doubles. Then `memmove` shifts the block from `index` to the end by one element, and the new value is copied into the gap. Shifting is O(n), so inserting in the middle gets slower with large vectors.
 
**Watch out:**
- `index` has to point to an **existing** element (`index < length`), and the vector must not be empty. To append at the end, use `cvec_push_back`.
- Strings are copied with `strdup`.
---
 
### `cvec_insert_range(v, index, arr)`
 
Inserts a whole array at `index` in one step.
 
```c
int nums[] = {10, 11, 12};
cvec_insert_range(&v, 1, nums);
// before: [1, 2, 3]  ->  after: [1, 10, 11, 12, 2, 3]
 
char *names[] = {"a", "b", "c"};
cvec_insert_range(&strings, 0, names);
```
 
**How it works:** The number of elements is calculated by the macro itself with `sizeof(arr) / sizeof((arr)[0])`, so you don't pass a length. The capacity is doubled until the new elements fit (so there is **one** `realloc` instead of many), the existing elements are shifted once with `memmove`, and the array is copied in with one `memcpy`.
 
**Watch out:**
- Pass a **real array** (like `nums` above). If you pass a pointer (a function parameter or `malloc`ed memory), `sizeof` returns the size of the pointer and the length is wrong.
- Here `index` may be equal to `length`, which appends the array at the end.
- For string arrays every string is copied with `strdup`.
---
 
### `erase(v, index)`
 
Removes the element at `index`. All following elements move one place to the left and the length shrinks by one.
 
```c
// before: [1, 2, 3, 4]
erase(&v, 1);
// after:  [1, 3, 4]
```
 
- Errors: `CVEC_ERR_EMPTY` on an empty vector, `CVEC_ERR_INDEX_OUT_OF_BOUNDS` if `index >= length`.
- The capacity stays the same. Use `shrink_to_fit` to give the memory back.
- Pointers to elements after `index` now point to the shifted data.
---
 
### `erase_range(v, begin, end)`
 
Removes all elements from `begin` to `end`, **both included**.
 
```c
// before: [1, 2, 3, 4, 5]
erase_range(&v, 1, 3);
// after:  [1, 5]
```
 
- Returns `CVEC_ERR_INVALID_RANGE` if `begin > end` or `end >= length`.
- The remaining elements are moved with a single `memmove`, which is faster than calling `erase` in a loop.
---
 
### `at(v, index, dest)`
 
Direct access to the element at `index` without copying.
 
- `dest` must not be `NULL`; the usual index and empty checks apply.
---
 
### `cvec_emplace_back(v, type, slot_ptr)`
 
Adds a new element at the end **without copying a value** and gives you a pointer to the new slot, so you can fill it in place. This is the way to work with `struct`s.
 
```c
typedef struct {
    char name[32];
    int  age;
} Person;
 
Cvec people;
cvec_init(&people, Person);
 
Person *p = NULL;
cvec_emplace_back(&people, Person, p);   // p now points to the new slot
strcpy(p->name, "Alice");
p->age = 30;
 
// read back element i
Person *q = (Person *)((char *)people.data + i * sizeof(Person));
```
 
It also works with the other types:
 
```c
int *ip = NULL;
cvec_emplace_back(&ints, int, ip);
*ip = 123;
 
char **sp = NULL;
cvec_emplace_back(&strs, char*, sp);
*sp = strdup("Alice");   // you create the string yourself
```
 
**How it works:** Like `push_back`, it doubles the capacity if needed. Then it sets your pointer to the address of the first free slot and increases `length` by one. Nothing is copied or initialized.
 
**Watch out:**
- The slot is **uninitialized**. Fill every field before you read it.
- The pointer is only valid until the next call that may grow the vector (`push_back`, `insert`, `emplace_back`, …). Use it right away and don't keep it.
- Use the same type as in `cvec_init` (the element size is compared; a mismatch returns `CVEC_ERR_TYPE`).
- For strings you must allocate the text yourself (`strdup`/`malloc`). `cvec_free` calls `free` on it later, so do **not** store string literals or stack buffers.
- Pass the pointer *variable*, not its address. The macro takes the address itself.
---
 
### `shrink_to_fit(v)`
 
Reduces the capacity to the current length and returns the unused memory with `realloc`.
 
```c
printf("%zu / %zu\n", v.length, v.capacity);   // 3 / 8
shrink_to_fit(&v);
printf("%zu / %zu\n", v.length, v.capacity);   // 3 / 3
```
 
Call it when you are done filling a vector that will stay around for a long time. The next `push_back` will have to grow the vector again. As with every reallocation, the data may move, so old pointers into the vector become invalid.
 
---
 
### `cvec_free(v)`
 
Releases all memory of the vector. **Call it exactly once for every initialized vector**, otherwise you leak memory.
 
```c
cvec_free(&v);
```
 
- For string vectors, every stored string is freed first, then the data block.
- Afterwards `data` is `NULL` and `length` and `capacity` are `0`. The vector keeps its type, so it can be filled again without a new `cvec_init`.
- The vector itself (`Cvec v`) is not freed, because it lives on your stack. The vector must not contain pointers you still need (e.g. strings from `cvec_get`).
---



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
