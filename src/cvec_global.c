/* Wrapper implementations for the core cvec functions to support 
 * different data types. */

#include "cvec_internals.h"


// Wrapper for push_back().
// Each wrapper passes the address of the local variable 'value' into the push_back() function.
// The value stored at that address is then copied by caling push_back() into the vector's memory.
CvecError cvec_push_char(Cvec *v, char value) { return push_back(v, &value, CVEC_INTEGER); }
CvecError cvec_push_uchar(Cvec *v, unsigned char value) { return push_back(v, &value, CVEC_INTEGER); }
CvecError cvec_push_string(Cvec *v, const char* str) 
{
	// Create's a heap-allocated copy of the passed string.
	// strdup() uses malloc() internally and is freed by calling cvec_free().
	// The copy is important because the original string may reside on the stack (e.g., as a local or temporary variable) rather than being a string literal
	// and push_back() saves the pointer of the string and not the string itself.

	char *copy_str = strdup(str);
	if (!copy_str) {
		return CVEC_ERR_ALLOC;
	}
	return push_back(v, &copy_str, CVEC_STRING);
}

CvecError cvec_push_bool(Cvec *v, bool value) { return push_back(v, &value, CVEC_INTEGER); }

CvecError cvec_push_short(Cvec *v, short value) { return push_back(v, &value, CVEC_SHORT); }
CvecError cvec_push_int(Cvec *v, int value) { return push_back(v, &value, CVEC_INTEGER); }
CvecError cvec_push_uint(Cvec *v, unsigned int value) { return push_back(v, &value, CVEC_UINTEGER); }
CvecError cvec_push_long(Cvec *v, long value) { return push_back(v, &value, CVEC_LONG); }
CvecError cvec_push_ulong(Cvec *v, unsigned long value) { return push_back(v, &value, CVEC_ULONG); }
CvecError cvec_push_llong(Cvec *v, long long value) { return push_back(v, &value, CVEC_LONG_LONG); }
CvecError cvec_push_ullong(Cvec *v, unsigned long long value) { return push_back(v, &value, CVEC_ULONG_LONG); }

CvecError cvec_push_float(Cvec *v, float value) { return push_back(v, &value, CVEC_FLOAT); }
CvecError cvec_push_double(Cvec *v, double value) { return push_back(v, &value, CVEC_DOUBLE); }
CvecError cvec_push_ldouble(Cvec *v, long double value) { return push_back(v, &value, CVEC_LONG_DOUBLE); }


// Wrapper for get_copy().
// The value and the error-type is passed to the appropriate GetValue struct.
GetValueChar get_char(Cvec *v, size_t index) 
{
	char val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueChar) { .value = val, .err = CVEC_OK };
	}
	return (GetValueChar) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueUchar get_uchar(Cvec *v, size_t index) 
{
	unsigned char val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueUchar) { .value = val, .err = CVEC_OK };
	}
	return (GetValueUchar) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueString get_string(Cvec *v, size_t index) 
{
	char* val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueString) { .value = val, .err = CVEC_OK };
	}
	return (GetValueString) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueBool get_bool(Cvec *v, size_t index) 
{
	bool val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueBool) { .value = val, .err = CVEC_OK };
	}
	return (GetValueBool) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueShort get_short(Cvec *v, size_t index) 
{
	short val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueShort) { .value = val, .err = CVEC_OK };
	}
	return (GetValueShort) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueInt get_int(Cvec *v, size_t index) 
{
	int val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueInt) { .value = val, .err = CVEC_OK };
	}
	return (GetValueInt) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueUint get_uint(Cvec *v, size_t index) 
{
	unsigned int val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueUint) { .value = val, .err = CVEC_OK };
	}
	return (GetValueUint) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueLong get_long(Cvec *v, size_t index) 
{
	long val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueLong) { .value = val, .err = CVEC_OK };
	}
	return (GetValueLong) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueUlong get_ulong(Cvec *v, size_t index) 
{
	unsigned long val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueUlong) { .value = val, .err = CVEC_OK };
	}
	return (GetValueUlong) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueLlong get_llong(Cvec *v, size_t index) 
{
	long long val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueLlong) { .value = val, .err = CVEC_OK };
	}
	return (GetValueLlong) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueUllong get_ullong(Cvec *v, size_t index) 
{
	unsigned long long val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueUllong) { .value = val, .err = CVEC_OK };
	}
	return (GetValueUllong) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}


GetValueFloat get_float(Cvec *v, size_t index) 
{
	float val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueFloat) { .value = val, .err = CVEC_OK };
	}
	return (GetValueFloat) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueDouble get_double(Cvec *v, size_t index) 
{
	double val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueDouble) { .value = val, .err = CVEC_OK };
	}
	return (GetValueDouble) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}

GetValueLdouble get_ldouble(Cvec *v, size_t index) 
{
	long double val;
	CvecError getVal = get_copy(v, index, &val);
	if(getVal == CVEC_OK) {
		return (GetValueLdouble) { .value = val, .err = CVEC_OK };
	}
	return (GetValueLdouble) { .err = CVEC_ERR_INDEX_OUT_OF_BOUNDS };
}


// Wrapper for replace().
// Each wrapper passes the address of a local variable 'value' and the index at which the
// value should replace the element in the vector. The stored value is copied via replace().
CvecError replace_char(Cvec *v, size_t index, char value) { return replace(v, index, &value, CVEC_CHAR); }
CvecError replace_uchar(Cvec *v, size_t index, unsigned char value) { return replace(v, index, &value, CVEC_UCHAR); }
CvecError replace_string(Cvec *v, size_t index, const char* str) {
    char *copy_str = strdup(str);
    if (!copy_str) {
        return CVEC_ERR_ALLOC;
    }
    return replace(v, index, &copy_str, CVEC_STRING);
}

CvecError replace_short(Cvec *v, size_t index, short value) { return replace(v, index, &value, CVEC_SHORT);}
CvecError replace_int(Cvec *v, size_t index, int value) { return replace(v, index, &value, CVEC_INTEGER); }
CvecError replace_uint(Cvec *v, size_t index, unsigned int value) { return replace(v, index, &value, CVEC_UINTEGER); }
CvecError replace_long(Cvec *v, size_t index, long value) { return replace(v, index, &value, CVEC_LONG); }
CvecError replace_llong(Cvec *v, size_t index, long long value) { return replace(v, index, &value, CVEC_LONG_LONG); }
CvecError replace_ulong(Cvec *v, size_t index, unsigned long value) { return replace(v, index, &value, CVEC_ULONG); }
CvecError replace_ullong(Cvec *v, size_t index, unsigned long long value) { return replace(v, index, &value, CVEC_ULONG_LONG); }

CvecError replace_float(Cvec *v, size_t index, float value) { return replace(v, index, &value, CVEC_FLOAT); }
CvecError replace_double(Cvec *v, size_t index, double value) { return replace(v, index, &value, CVEC_DOUBLE); }
CvecError replace_ldouble(Cvec *v, size_t index, long double value) { return replace(v, index, &value, CVEC_LONG_DOUBLE); }


// Wrapper for insert().
// Each wrapper passes the address of a local variable 'value' and the index at wich the value should be inserted.
// The value stored at that address is then copied by calling insert() into the vector's memory at the given index.
CvecError insert_char(Cvec *v, size_t index, char value) { return insert(v, index, &value, CVEC_CHAR); }
CvecError insert_uchar(Cvec *v, size_t index, unsigned char value) { return insert(v, index, &value, CVEC_UCHAR); }
CvecError insert_string(Cvec *v, size_t index, const char* str) 
{
	char *copy_str = strdup(str);
	if (!copy_str) {
		return CVEC_ERR_ALLOC;
	}
    return insert(v, index, &copy_str, CVEC_STRING);
}

CvecError insert_bool(Cvec *v, size_t index, int value) { return insert(v, index, &value, CVEC_BOOL); }

CvecError insert_short(Cvec *v, size_t index, short value) { return insert(v, index, &value, CVEC_SHORT); }
CvecError insert_int(Cvec *v, size_t index, int value) { return insert(v, index, &value, CVEC_INTEGER); }
CvecError insert_uint(Cvec *v, size_t index, unsigned int value) { return insert(v, index, &value, CVEC_UINTEGER); }
CvecError insert_long(Cvec *v, size_t index, long value) { return insert(v, index, &value, CVEC_LONG); }
CvecError insert_llong(Cvec *v, size_t index, long long value) { return insert(v, index, &value, CVEC_LONG_LONG); }
CvecError insert_ulong(Cvec *v, size_t index, unsigned long value) { return insert(v, index, &value, CVEC_ULONG); }
CvecError insert_ullong(Cvec *v, size_t index, unsigned long long value) { return insert(v, index, &value, CVEC_ULONG_LONG); }

CvecError insert_float(Cvec *v, size_t index, float value) { return insert(v, index, &value, CVEC_FLOAT); }
CvecError insert_double(Cvec *v, size_t index, double value) { return insert(v, index, &value, CVEC_DOUBLE); }
CvecError insert_ldouble(Cvec *v, size_t index, long double value) { return insert(v, index, &value, CVEC_LONG_DOUBLE); }


// Wrapper for insert_range().
// Passes the array pointer, the target index and the array length.
// insert_range() then copies the values into the vector.
CvecError insert_range_char(Cvec *v, size_t index, char *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_uchar(Cvec *v, size_t index, unsigned char *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_string(Cvec *v, size_t index, char **arr, size_t arr_length) 
{
    // Local array of string pointers allocated on the heap
    char **str_arr_copy = malloc(arr_length * sizeof(char*));
    if (!str_arr_copy) {
		return CVEC_ERR_ALLOC;
	}

    for (size_t i = 0; i < arr_length; i++) 
	{
		// Copies each string from the passed array into the local array
		str_arr_copy[i] = strdup(arr[i]);

        if (!str_arr_copy[i]) {
            // Cleaning, if strdup fails
            for (size_t j = 0; j < i; j++) free(str_arr_copy[j]);
            free(str_arr_copy);
            return CVEC_ERR_ALLOC;
        }
    }

    CvecError err = insert_range(v, index, arr_length, str_arr_copy, CVEC_STRING);
    free(str_arr_copy);

    return err;
}

CvecError insert_range_short(Cvec *v, size_t index, short *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_int(Cvec *v, size_t index, int *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_uint(Cvec *v, size_t index, unsigned int *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_long(Cvec *v, size_t index, long *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_llong(Cvec *v, size_t index, long long *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_ulong(Cvec *v, size_t index, unsigned long *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_ullong(Cvec *v, size_t index, unsigned long long *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }

CvecError insert_range_float(Cvec *v, size_t index, float *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_double(Cvec *v, size_t index, double *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
CvecError insert_range_ldouble(Cvec *v, size_t index, long double *arr, size_t arr_length) { return insert_range(v, index, arr_length, arr, CVEC_INTEGER); }
