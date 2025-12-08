/* Functions only unsed internally by cVector. */

#ifndef CVEC_INTERNAL_H
#define CVEC_INTERNAL_H


#include "cvec.h" 

CvecError push_back(Cvec *v, void *element, CvecType expected_type);
CvecError get_copy(const Cvec *v, size_t index, void *dest);
CvecError replace(Cvec *v, size_t index, void *element, CvecType expected_type);
CvecError insert(Cvec *v, size_t index, void *element, CvecType expected_type);
CvecError insert_range(Cvec *v, size_t index, size_t count, void *arr, CvecType expected_type);

#endif

