#include "cvec.h"


void printCvecValue(Cvec *v, int index) 
{
	GetValueInt result = cvec_get(v, index, int);
	if(result.err == CVEC_OK) {
		printf("Value of index %i: %i\n", index, result.value);
	}
}

void printCvecValueString(Cvec *v, int index) 
{
	GetValueString result = cvec_get(v, index, char*);
	if(result.err == CVEC_OK) {
		printf("Value of index %i: %s\n", index, result.value);
	}
}


int main() {
    // Run a comprehensive cvec test suite for 'int' and 'char*' (string).
    // Each test prints which function is being tested.

    // Test with int
    printf("\n--- Testing cvec with type: int ---\n");
    Cvec vi;
    cvec_init(&vi, int);
    printf("Testing: init (int) -> length=%zu capacity=%zu\n", vi.length, vi.capacity);

    printf("Testing: push_back (int)\n");
    cvec_push_back(&vi, 1);
    cvec_push_back(&vi, 2);
    cvec_push_back(&vi, 3);
    for (size_t i = 0; i < vi.length; ++i) printCvecValue(&vi, i);
	printf("\n");

    printf("Testing: insert_range (int)\n");
    int ins_arr[] = {10, 11, 12};
    cvec_insert_range(&vi, 1, ins_arr);
    for (size_t i = 0; i < vi.length; ++i) printCvecValue(&vi, i);
	printf("\n");

    printf("Testing: insert (int) at index 2\n");
    cvec_insert(&vi, 2, 99);
    for (size_t i = 0; i < vi.length; ++i) printCvecValue(&vi, i);
	printf("\n");

    printf("Testing: get (int) at index 2\n");
    GetValueInt gvi = cvec_get(&vi, 2, int);
    if (gvi.err == CVEC_OK) printf("get returned: %d\n", gvi.value);
	printf("\n");

    printf("Testing: replace (int) at index 2 -> 42\n");
    cvec_replace(&vi, 2, 42);
    for (size_t i = 0; i < vi.length; ++i) printCvecValue(&vi, i);
	printf("\n");

    printf("Testing: erase (int) at index 1\n");
    erase(&vi, 1);
    for (size_t i = 0; i < vi.length; ++i) printCvecValue(&vi, i);
	printf("\n");

    printf("Testing: erase_range (int) from 1 to 2\n");
    if (vi.length > 2) erase_range(&vi, 1, 2);
    for (size_t i = 0; i < vi.length; ++i) printCvecValue(&vi, i);
	printf("\n");

    printf("Testing: shrink_to_fit (int)\n");
    shrink_to_fit(&vi);
    printf("After shrink: length=%zu capacity=%zu\n", vi.length, vi.capacity);
	printf("\n");

    printf("Testing: cvec_free (int)\n");
    cvec_free(&vi);
    printf("Freed int vector.\n");
	printf("\n\n");

    // Test with string
    printf("\n--- Testing cvec with type: string (char*) ---\n");
    Cvec vs;
    cvec_init(&vs, char*);
    printf("Testing: init (string) -> length=%zu capacity=%zu\n", vs.length, vs.capacity);
	printf("\n");

    printf("Testing: push_back (string)\n");
    cvec_push_back(&vs, "first");
    cvec_push_back(&vs, "second");
    char tmp_str[] = "temp";
    cvec_push_back(&vs, tmp_str);
    for (size_t i = 0; i < vs.length; ++i) printCvecValueString(&vs, i);
	printf("\n");

    printf("Testing: insert_range (string)\n");
    char *sarr[] = {"a", "b", "c"};
    cvec_insert_range(&vs, 1, sarr);
    for (size_t i = 0; i < vs.length; ++i) printCvecValueString(&vs, i);
	printf("\n");

    printf("Testing: insert (string) at index 2\n");
    cvec_insert(&vs, 2, "inserted");
    for (size_t i = 0; i < vs.length; ++i) printCvecValueString(&vs, i);
	printf("\n");

    printf("Testing: get (string) at index 2\n");
    GetValueString gvs = cvec_get(&vs, 2, char*);
    if (gvs.err == CVEC_OK) printf("get returned: %s\n", gvs.value);
	printf("\n");

    printf("Testing: replace (string) at index 2 -> 'replaced'\n");
    cvec_replace(&vs, 2, "replaced");
    for (size_t i = 0; i < vs.length; ++i) printCvecValueString(&vs, i);
	printf("\n");

    printf("Testing: erase (string) at index 1\n");
    if (vs.length > 1) erase(&vs, 1);
    for (size_t i = 0; i < vs.length; ++i) printCvecValueString(&vs, i);
	printf("\n");

    printf("Testing: erase_range (string) from 0 to 1\n");
    if (vs.length > 2) erase_range(&vs, 0, 1);
    for (size_t i = 0; i < vs.length; ++i) printCvecValueString(&vs, i);
	printf("\n");

    printf("Testing: shrink_to_fit (string)\n");
    shrink_to_fit(&vs);
    printf("After shrink: length=%zu capacity=%zu\n", vs.length, vs.capacity);
	printf("\n");

    printf("Testing: cvec_free (string)\n");
    cvec_free(&vs);
    printf("Freed string vector.\n");

    return 0;
}
