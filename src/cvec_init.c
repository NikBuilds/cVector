/* Wrapper implementations for the core init function to support 
 * different data types. */

#include "cvec.h"

void init_char(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(char);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_uchar(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(unsigned char);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_string(Cvec *v) {
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
    v->element_size = sizeof(char*);
    v->datatype = CVEC_STRING;
}

void init_bool(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(bool);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_short(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(short);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_int(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(int);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_uint(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(unsigned int);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_long(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(long);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_llong(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(long long);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_ulong(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(unsigned long);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_ullong(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(unsigned long long);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_float(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(float);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_double(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(double);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}

void init_ldouble(Cvec *v) {
	v->data = NULL,
	v->element_size = sizeof(long double);
	v->length = 0;
	v->capacity = 0;
	v->datatype = CVEC_INTEGER;
}
