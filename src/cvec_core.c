#include "cvec_internals.h"


// Adds a copy of an element at the end of the vector.
// If the vector's capacity is 0, then set it to 1. Else double the capacity
// and reallocate new space on the heap. When adding the first element, the
// length is 0, so the first element ist at index 0. Only after an element is
// added, vector->length is increased by 1.
CvecError push_back(Cvec *v, void *element, CvecType expected_type) 
{
	if (v == NULL) return CVEC_ERR_NULL;
	if (element == NULL) return CVEC_ERR_NULL;
    if (v->datatype != expected_type) return CVEC_ERR_TYPE;

    if (v->length == v->capacity) 
	{
		if (v->capacity > SIZE_MAX / 2) 
			return CVEC_ERR_OVERFLOW;

        size_t new_capacity = v->capacity ? v->capacity * 2 : 1;

		if(new_capacity > SIZE_MAX / v->element_size) 
			return CVEC_ERR_OVERFLOW;	// Byte-overflow (new_capacity * element_size)

        void *tmp = realloc(v->data, new_capacity * v->element_size);

		if (!tmp) return CVEC_ERR_ALLOC;
        
		v->data = tmp;
		v->capacity = new_capacity;
    }

    // Copies the new element into the memory location at the calculated offset
    void *target = (char *)v->data + v->length * v->element_size;
    memcpy(target, element, v->element_size);

    v->length++;
    return CVEC_OK;
	}


// Copies the element at the given index from the vector into the memory pointed
// to by 'dest'. This ensures the caller receives a standalone copy.
CvecError get_copy(const Cvec *v, size_t index, void *dest) 
{

	if (v == NULL) return CVEC_ERR_NULL;
	if (v->length == 0) return CVEC_ERR_EMPTY;
	if (dest == NULL) return CVEC_ERR_NULL;
    if (index >= v->length) return CVEC_ERR_INDEX_OUT_OF_BOUNDS;

    memcpy(dest, (char *)v->data + index * v->element_size, v->element_size);
    return CVEC_OK;
}


// This function replaceses an element at the given index
// It can only replace values if the vector is not empty.
CvecError replace(Cvec *v, size_t index, void *element, CvecType expected_type) 
{
	if (v == NULL) return CVEC_ERR_NULL;
	if (element == NULL) return CVEC_ERR_NULL;
	if (v->length == 0) return CVEC_ERR_EMPTY;
	if (index >= v->length) return CVEC_ERR_INDEX_OUT_OF_BOUNDS;
	if (v->datatype != expected_type) return CVEC_ERR_TYPE;
	
	if(v->length == v->capacity) 
	{
		if(v->capacity > SIZE_MAX / 2) 
			return CVEC_ERR_OVERFLOW;

		size_t new_capacity = v->capacity ? v->capacity * 2 : 1;

		if(new_capacity > SIZE_MAX / v->element_size)
			return CVEC_ERR_OVERFLOW;	// Byte-overflow (new_capacity * element_size)

		void *tmp = realloc(v->data, new_capacity * v->element_size);
	
		if (!tmp) return CVEC_ERR_ALLOC;
        
		v->data = tmp;
		v->capacity = new_capacity;
	}

    void *insert_pos = (char*)v->data + index * v->element_size;
    memcpy(insert_pos, element, v->element_size);
    
	return CVEC_OK;
}


// Inserts a value at the given index.
// By adding a new element, all next elements are moved to the right.
// It can only insert values if the vctor is not empty.
CvecError insert(Cvec *v, size_t index, void *element, CvecType expected_type) 
{
	if (v == NULL) return CVEC_ERR_NULL;
	if (element == NULL) return CVEC_ERR_NULL;
	if (v->length == 0) return CVEC_ERR_EMPTY;
	if (index >= v->length) return CVEC_ERR_INDEX_OUT_OF_BOUNDS;
	if (v->capacity > SIZE_MAX / 2) return CVEC_ERR_OVERFLOW;
	if (v->datatype != expected_type) return CVEC_ERR_TYPE;

    if (v->length == v->capacity) 
	{
		if(v->capacity > SIZE_MAX / 2) 
			return CVEC_ERR_OVERFLOW;

		size_t new_capacity = v->capacity ? v->capacity * 2 : 1;

		if(new_capacity > SIZE_MAX / v->element_size) 
			return CVEC_ERR_OVERFLOW;	// Byte-overflow (new_capacity * element_size)

		void *tmp = realloc(v->data, new_capacity * v->element_size);
        
		if (!tmp) return CVEC_ERR_ALLOC;
        
		v->data = tmp;
        v->capacity = new_capacity;
    }

    void *dest = (char*)v->data + (index + 1) * v->element_size;	// Pointer to the new position where the cvec elements will be moved (index + count)
    void *src  = (char*)v->data + index * v->element_size;			// Pointer to the first element in cvec to be moved (index position)
    size_t bytes_to_move = (v->length - index) * v->element_size;	// Calculated number of bytes that need to be moved

    if (bytes_to_move) memmove(dest, src, bytes_to_move);

    void *insert_pos = (char*)v->data + index * v->element_size;	// Position where the new elements are inserted
    memcpy(insert_pos, element, v->element_size);					// Copies count elements form arr into the vector
    
	v->length++;
	return CVEC_OK;
}


// Inserts an array of 'count' elements into the vector at the given index.
CvecError insert_range(Cvec *v, size_t index, size_t count, void *arr, CvecType expected_type) 
{
	if (v == NULL) return CVEC_ERR_NULL;
	if (arr == NULL && count > 0) return CVEC_ERR_NULL_INPUT;
    if (index > v->length) return CVEC_ERR_INDEX_OUT_OF_BOUNDS;
	if (count > SIZE_MAX / v->element_size) return CVEC_ERR_OVERFLOW;
    if (v->datatype != expected_type) return CVEC_ERR_TYPE;

    size_t new_length = v->length + count;

    if (new_length > v->capacity) {
		size_t new_capacity = v->capacity;

		if (new_capacity == 0) new_capacity = 1;

		while (new_capacity < new_length) {
			if (new_capacity > SIZE_MAX / 2) 
				return CVEC_ERR_OVERFLOW;
			
			new_capacity *= 2;
		}

		if(new_capacity > SIZE_MAX / v->element_size) 
			return CVEC_ERR_OVERFLOW;	// Byte-overflow (new_capacity * element_size)

        void *new_data = realloc(v->data, new_capacity * v->element_size);
        
		if (!new_data) 
            return CVEC_ERR_ALLOC;

        v->data = new_data;
        v->capacity = new_capacity;
    }

    void *dest = (char *)v->data + (index + count) * v->element_size;	// Pointer to the new position where the cvec elements will be moved (index + count)
    void *src = (char *)v->data + index * v->element_size;				// Pointer to the first element in cvec to be moved (index position)
    size_t bytes_to_move = (v->length - index) * v->element_size;		// Calculated number of bytes that need to be moved
    
	if(bytes_to_move) memmove(dest, src, bytes_to_move);

    void *insert_pos = (char *)v->data + index * v->element_size;		// Position where the new elements are inserted
    memcpy(insert_pos, arr, count * v->element_size);					// Copies count elements form arr into the vector

    v->length += count;
    return CVEC_OK;
}


// Deletes one element
// To delete an element, all elements after index_pos are moved to the given index.
// This overwrites the element that has to be deleted.
// Vector cannot be empty.
CvecError erase(Cvec *v, size_t index_pos) 
{
	if (v == NULL) return CVEC_ERR_NULL;
    if (v->length == 0) return CVEC_ERR_EMPTY;
    if (index_pos >= v->length) return CVEC_ERR_INDEX_OUT_OF_BOUNDS;

    void *dest = (char *)v->data + index_pos * v->element_size;
    void *src = (char *)v->data + (index_pos + 1) * v->element_size;
    size_t bytes_to_move = (v->length - index_pos - 1) * v->element_size; // -1 because only the elements after index_pos has to be moved, and not the element itself.

    memmove(dest, src, bytes_to_move);
    v->length--;

    return CVEC_OK;
}


// Deletes a range of elements
// Vector cannot be empty.
CvecError erase_range(Cvec *v, size_t begin, size_t end) 
{
	if (v == NULL) return CVEC_ERR_NULL;
    if (v->length == 0) return CVEC_ERR_EMPTY;

    if (begin > end || end >= v->length) return CVEC_ERR_INVALID_RANGE;

    size_t count = end - begin + 1;

    void *dest = (char *)v->data + begin * v->element_size;
    void *src = (char *)v->data + (end + 1) * v->element_size;
    size_t bytes_to_move = (v->length - end - 1) * v->element_size;

    memmove(dest, src, bytes_to_move);

    v->length -= count;
    return CVEC_OK;
}


CvecError shrink_to_fit(Cvec *v) 
{
	if (v == NULL) return CVEC_ERR_NULL;
	if (v->length > SIZE_MAX / v->element_size) return CVEC_ERR_OVERFLOW;

    void *temp = realloc(v->data, v->length * v->element_size);
    
	if (temp == NULL) 
        return CVEC_ERR_ALLOC;

    v->data = temp;
    v->capacity = v->length;

    return CVEC_OK;
}


CvecError cvec_free(Cvec *v) 
{
	if (v == NULL) return CVEC_ERR_NULL;

    if (v->datatype == CVEC_STRING) {
        for (size_t i = 0; i < v->length; ++i) {
            char **ptr = (char **)v->data;
            free(ptr[i]);
        }
    }

    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;

	return CVEC_OK;
}
