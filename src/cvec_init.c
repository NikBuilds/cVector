/* Wrapper implementations for the core init function to support 
 * different data types. */

#include "cvec.h"

CvecError init_char(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(char)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(char);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_CHAR;

    return CVEC_OK;
}

CvecError init_uchar(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(unsigned char)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(unsigned char);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_UCHAR;

    return CVEC_OK;
}

CvecError init_string(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(char*)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(char*);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_STRING;

    return CVEC_OK;
}

CvecError init_bool(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(bool)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(bool);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_BOOL;

    return CVEC_OK;
}

CvecError init_short(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(short)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(short);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_SHORT;

    return CVEC_OK;
}

CvecError init_int(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(int)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(int);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_INTEGER;

    return CVEC_OK;
}

CvecError init_uint(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(unsigned int)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(unsigned int);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_UINTEGER;

    return CVEC_OK;
}

CvecError init_long(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(long)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(long);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_LONG;

    return CVEC_OK;
}

CvecError init_llong(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(long long)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(long long);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_LONG_LONG;

    return CVEC_OK;
}


CvecError init_ulong(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(unsigned long)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(unsigned long);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_ULONG;

    return CVEC_OK;
}

CvecError init_ullong(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(unsigned long long)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(unsigned long long);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_ULONG_LONG;

    return CVEC_OK;
}

CvecError init_float(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(float)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(float);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_FLOAT;

    return CVEC_OK;
}

CvecError init_double(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(double)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(double);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_DOUBLE;

    return CVEC_OK;
}

CvecError init_ldouble(Cvec *v, size_t element_size)
{
    if (!v) return CVEC_ERR_NULL;
    if (element_size != sizeof(long double)) return CVEC_ERR_TYPE;

    v->data = NULL;
    v->element_size = sizeof(long double);
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_LONG_DOUBLE;

    return CVEC_OK;
}

CvecError cvec_init_struct(Cvec *v, size_t element_size)
{
    if (!v || element_size == 0)
        return CVEC_ERR_NULL;

    v->data = NULL;
    v->element_size = element_size;
    v->length = 0;
    v->capacity = 0;
    v->datatype = CVEC_STRUCT;

    return CVEC_OK;
}
