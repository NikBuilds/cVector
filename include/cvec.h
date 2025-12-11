#ifndef CVEC_H
#define CVEC_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>  /* SIZE_MAX */

// Type-generic macros.
// Provide a convenient, type-safe interface for working with vectors 
// of different data types without manually calling the type-specific functions.
#define cvec_init(v, type) \
    _Generic((type)0, \
		char: init_char, \
		unsigned char: init_uchar, \
		char*: init_string, \
		bool: init_bool, \
		short: init_short, \
        int: init_int, \
		unsigned int: init_uint, \
		long: init_long, \
		long long: init_llong, \
		unsigned long: init_ulong, \
		unsigned long long: init_ullong, \
		float: init_float, \
		double: init_double, \
		long double: init_ldouble \
    )(v)

#define cvec_push_back(v, val) \
    _Generic((val), \
		char: cvec_push_char, \
		unsigned char: cvec_push_uchar, \
		char*: cvec_push_string, \
		bool: cvec_push_bool, \
		short: cvec_push_short, \
        int: cvec_push_int, \
		unsigned int: cvec_push_uint, \
		long: cvec_push_long, \
		long long: cvec_push_llong, \
		unsigned long: cvec_push_ulong, \
		unsigned long long: cvec_push_ullong, \
        float: cvec_push_float, \
        double: cvec_push_double, \
		long double: cvec_push_ldouble \
    )(v, val)

#define cvec_get(v, index, type) \
    _Generic((type)0, \
        char: get_char, \
        unsigned char: get_uchar, \
        char*: get_string, \
        bool: get_bool, \
        short: get_short, \
        int: get_int, \
        unsigned int: get_uint, \
        long: get_long, \
        long long: get_llong, \
        unsigned long: get_ulong, \
        unsigned long long: get_ullong, \
        float: get_float, \
        double: get_double, \
        long double: get_ldouble \
    )(v, index)

#define cvec_replace(v, index, val) \
    _Generic((val), \
        char: replace_char, \
        unsigned char: replace_uchar, \
        char*: replace_string, \
        short: replace_short, \
        int: replace_int, \
        unsigned int: replace_uint, \
        long: replace_long, \
        long long: replace_llong, \
        unsigned long: replace_ulong, \
        unsigned long long: replace_ullong, \
        float: replace_float, \
        double: replace_double, \
        long double: replace_ldouble \
    )(v, index, val)

#define cvec_insert(v, index, val) \
    _Generic((val), \
		char: insert_char, \
		unsigned char: insert_uchar, \
		char*: insert_string, \
		short: insert_short, \
        int: insert_int, \
		unsigned int: insert_uint, \
		long: insert_long, \
		long long: insert_llong, \
		unsigned long: insert_ulong, \
		unsigned long long: insert_ullong, \
        float: insert_float, \
        double: insert_double, \
		long double: insert_ldouble \
    )(v, index, val)

#define cvec_insert_range(v, index, arr) \
    _Generic((arr), \
		char*: insert_range_char, \
		unsigned char*: insert_range_uchar, \
		char**: insert_range_string, \
		short*: insert_range_short, \
        int*: insert_range_int, \
		unsigned int: insert_range_uint, \
		long*: insert_range_long, \
		long long*: insert_range_llong, \
		unsigned long*: insert_range_ulong, \
		unsigned long long*: insert_range_ullong, \
		float*: insert_range_float, \
		double*: insert_range_double, \
		long double*: insert_range_ldouble \
    )((v), (index), (arr), sizeof(arr)/sizeof((arr)[0]))

#define cvec_emplace_back(v, type, slot) \
    cvec_emplace_back_generic((v), sizeof(type), (void**)&(slot))


// Supported error types
typedef enum error_msg {
	CVEC_OK,
	CVEC_ERR_ALLOC,
	CVEC_ERR_INDEX_OUT_OF_BOUNDS,
	CVEC_ERR_INVALID_RANGE,
	CVEC_ERR_EMPTY,
	CVEC_ERR_TYPE,
	CVEC_ERR_NULL_INPUT,
	CVEC_ERR_OVERFLOW,
	CVEC_ERR_NULL
} CvecError;

// Accepted datatype's for cvec
typedef enum cvec_types {
	CVEC_CHAR,
	CVEC_UCHAR,
	CVEC_STRING,
	CVEC_BOOL,
	CVEC_SHORT,
	CVEC_USHORT,
	CVEC_INTEGER,
	CVEC_UINTEGER,
	CVEC_LONG,
	CVEC_ULONG,
	CVEC_LONG_LONG,
	CVEC_ULONG_LONG,
	CVEC_FLOAT,
	CVEC_DOUBLE,
	CVEC_LONG_DOUBLE
} CvecType;

typedef struct {
    void *data;          // Pointer at the beginning of the Data-Array
    size_t element_size; // Size of the element (z.B. sizeof(int))
    size_t length;       // Number of the actual saved elements
    size_t capacity;     // Size of the allocated space
	CvecType datatype;	 // Datatype of the vector
} Cvec;

// Return types for the get() functions's
typedef struct {
    char value;			
    CvecError err;		
} GetValueChar;

typedef struct {
    char value;			
    CvecError err;		
} GetValueUchar;

typedef struct {
    char* value;
    CvecError err;
} GetValueString;

typedef struct {
    bool value;
    CvecError err;
} GetValueBool;

typedef struct {
    short value;			
    CvecError err;		
} GetValueShort;

typedef struct {
    unsigned short value;			
    CvecError err;		
} GetValueUshort;

typedef struct {
    int value;			
    CvecError err;		
} GetValueInt;

typedef struct {
    unsigned int value;			
    CvecError err;		
} GetValueUint;

typedef struct {
    long value;			
    CvecError err;		
} GetValueLong;

typedef struct {
    unsigned long value;			
    CvecError err;		
} GetValueUlong;

typedef struct {
    long long value;			
    CvecError err;		
} GetValueLlong;

typedef struct {
    unsigned long long value;			
    CvecError err;		
} GetValueUllong;

typedef struct {
    float value;		
    CvecError err;		
} GetValueFloat;

typedef struct {
    double value;
    CvecError err;
} GetValueDouble;

typedef struct {
    long double value;
    CvecError err;
} GetValueLdouble;


void init_char(Cvec *v);
void init_uchar(Cvec *v);
void init_string(Cvec *v);
void init_bool(Cvec *v);
void init_short(Cvec *v);
void init_int(Cvec *v);
void init_uint(Cvec *v);
void init_long(Cvec *v);
void init_llong(Cvec *v);
void init_ulong(Cvec *v);
void init_ullong(Cvec *v);
void init_float(Cvec *v);
void init_double(Cvec *v);
void init_ldouble(Cvec *v);

CvecError cvec_push_char(Cvec *v, char value);
CvecError cvec_push_uchar(Cvec *v, unsigned char value);
CvecError cvec_push_string(Cvec *V, const char* str);
CvecError cvec_push_bool(Cvec *v, bool value);
CvecError cvec_push_short(Cvec *v, short value);
CvecError cvec_push_int(Cvec *v, int value);
CvecError cvec_push_uint(Cvec *v, unsigned int value);
CvecError cvec_push_long(Cvec *v, long value);
CvecError cvec_push_ulong(Cvec *v, unsigned long value);
CvecError cvec_push_llong(Cvec *v, long long value);
CvecError cvec_push_ullong(Cvec *v, unsigned long long value);
CvecError cvec_push_float(Cvec *v, float value);
CvecError cvec_push_double(Cvec *v, double value);
CvecError cvec_push_ldouble(Cvec *v, long double value);

GetValueChar get_char(Cvec *v, size_t index);
GetValueUchar get_uchar(Cvec *v, size_t index);
GetValueString get_string(Cvec *v, size_t index);
GetValueBool get_bool(Cvec *v, size_t index);
GetValueShort get_short(Cvec *v, size_t index);
GetValueInt get_int(Cvec *v, size_t index);
GetValueUint get_uint(Cvec *v, size_t index);
GetValueLong get_long(Cvec *v, size_t index);
GetValueLlong get_llong(Cvec *v, size_t index);
GetValueUlong get_ulong(Cvec *v, size_t index);
GetValueUllong get_ullong(Cvec *v, size_t index);
GetValueFloat get_float(Cvec *v, size_t index);
GetValueDouble get_double(Cvec *v, size_t index);
GetValueLdouble get_ldouble(Cvec *v, size_t index);

CvecError erase(Cvec *v, size_t index);
CvecError erase_range(Cvec *v, size_t begin, size_t end);

CvecError replace_char(Cvec *v, size_t index, char element);
CvecError replace_uchar(Cvec *v, size_t index, unsigned char element);
CvecError replace_string(Cvec *v, size_t index, const char* str);
CvecError replace_short(Cvec *v, size_t index, short element);
CvecError replace_int(Cvec *v, size_t index, int element);
CvecError replace_uint(Cvec *v, size_t index, unsigned int element);
CvecError replace_long(Cvec *v, size_t index, long element);
CvecError replace_llong(Cvec *v, size_t index, long long element);
CvecError replace_ulong(Cvec *v, size_t index, unsigned long element);
CvecError replace_ullong(Cvec *v, size_t index, unsigned long long element);
CvecError replace_float(Cvec *v, size_t index, float element);
CvecError replace_double(Cvec *v, size_t index, double element);
CvecError replace_ldouble(Cvec *v, size_t index, long double element);

CvecError insert_char(Cvec *v, size_t index, char element);
CvecError insert_uchar(Cvec *v, size_t index, unsigned char element);
CvecError insert_string(Cvec *v, size_t index, const char* str);
CvecError insert_short(Cvec *v, size_t index, short element);
CvecError insert_int(Cvec *v, size_t index, int element);
CvecError insert_uint(Cvec *v, size_t index, unsigned int element);
CvecError insert_long(Cvec *v, size_t index, long element);
CvecError insert_ulong(Cvec *v, size_t index, unsigned long);
CvecError insert_llong(Cvec *v, size_t index, long long element);
CvecError insert_ullong(Cvec *v, size_t index, unsigned long long element);
CvecError insert_float(Cvec *v, size_t index, float element);
CvecError insert_double(Cvec *v, size_t index, double element);
CvecError insert_ldouble(Cvec *v, size_t index, long double element);

CvecError insert_range_char(Cvec *v, size_t index, char *arr, size_t arr_length);
CvecError insert_range_uchar(Cvec *v, size_t index, unsigned char *arr, size_t arr_length);
CvecError insert_range_string(Cvec *v, size_t index, char **arr, size_t arr_length);
CvecError insert_range_short(Cvec *v, size_t index, short *arr, size_t arr_length);
CvecError insert_range_int(Cvec *v, size_t index, int *arr, size_t arr_length);
CvecError insert_range_uint(Cvec *v, size_t index, unsigned int *arr, size_t arr_length);
CvecError insert_range_long(Cvec *v, size_t index, long *arr, size_t arr_length);
CvecError insert_range_llong(Cvec *v, size_t index, long long *arr, size_t arr_length);
CvecError insert_range_ulong(Cvec *v, size_t index, unsigned long *arr, size_t arr_length);
CvecError insert_range_ullong(Cvec *v, size_t index, unsigned long long *arr, size_t arr_length);
CvecError insert_range_float(Cvec *v, size_t index, float *arr, size_t arr_length);
CvecError insert_range_double(Cvec *v, size_t index, double *arr, size_t arr_length);
CvecError insert_range_ldouble(Cvec *v, size_t index, long double *arr, size_t arr_length);

CvecError cvec_emplace_back_generic(Cvec *v, size_t element_size, void **slot);

CvecError shrink_to_fit(Cvec *v);
CvecError cvec_free(Cvec *v);

#endif
