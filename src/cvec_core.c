#include "cvec_internals.h"

// Adds a copy of an element at the end of the vector.
// If the vector's capacity is 0, then set it to 1. Else doueble the capacity and reallocate new space on the heap.
// When adding the first element, the length is 0, so the first element ist at index 0. Only after a element ist added, vector->length in increased by 1.
CvecError push_back(Cvec *v, void *element, CvecType expected_type)
{
    if (v->datatype != expected_type) {
        return CVEC_ERR_TYPE;
    }

	if(v->length == v->capacity) 
	{
		size_t new_capacity = v->capacity ? v->capacity * 2 : 1;
		void *temp = realloc(v->data, new_capacity * v->element_size);
		
		if(temp == NULL) {
			return CVEC_ERR_ALLOC;
		} else {
			v->data = temp;
			v->capacity = new_capacity;
		}

	}
	// Copies the new element into the memory location at the calculated offset (target) in 'v->data'.
	void *target = (char*)v->data + v->length * v->element_size;
	memcpy(target, element, v->element_size);

	v->length++;
	return CVEC_OK;
}

// Copies the element at the given index from the vector into the memory pointed to by 'dest'.
// This ensures the caller receives a standalone copy of the element, rather than a pointer into the vector's internal storae.
CvecError get_copy(const Cvec *v, size_t index, void *dest) 
{
	if (index >= v->length) {
		return CVEC_ERR_INDEX_OUT_OF_BOUNDS;
	}
	memcpy(dest, (char*)v->data + index * v->element_size, v->element_size);
	return CVEC_OK;
}

// Insert's a value at the given index
CvecError insert(Cvec *v, size_t index, void *element, CvecType expected_type) 
{
    if (v->datatype != expected_type) {
        return CVEC_ERR_TYPE;
    }

	if(index <= v->length) 
	{
		void *dest = (char*)v->data + index * v->element_size;
		memcpy(dest, element, v->element_size);

		return CVEC_OK;

	}
	return CVEC_ERR_INDEX_OUT_OF_BOUNDS;
}

// Inserts a range of values into the vector at a specific index
/*
 * 
 * */
CvecError insert_range(Cvec *v, size_t index, size_t count, void *arr, CvecType expected_type) 
{
    if (v->datatype != expected_type) {
        return CVEC_ERR_TYPE;
    }

	if(index > v->length) {
		return CVEC_ERR_INDEX_OUT_OF_BOUNDS;
	}
	
	size_t new_length = v->length + count;
	if (new_length > v->capacity) 
	{
        size_t new_capacity = v->capacity ? v->capacity * 2 : 1;
        while (new_capacity < new_length) {
            new_capacity *= 2;
        }

		void *new_data = realloc(v->data, new_capacity * v->element_size);
		if (!new_data) {
            return CVEC_ERR_ALLOC;
        }

        v->data = new_data;
        v->capacity = new_capacity;
	}

    // 2. Verschiebe existierende Elemente nach hinten
    void *dest = (char*)v->data + (index + count) * v->element_size;
    void *src  = (char*)v->data + index * v->element_size;
    size_t bytes_to_move = (v->length - index) * v->element_size;
    memmove(dest, src, bytes_to_move);  // sicher für überlappende Bereiche

    // 3. Kopiere die neuen Elemente rein
    void *insert_pos = (char*)v->data + index * v->element_size;
    memcpy(insert_pos, arr, count * v->element_size);

    // 4. Aktualisiere Länge
    v->length += count;

    return CVEC_OK;
}

// Deletes n element
/*
 * To delete an element that is not the last element, you have to move all the other right elements to the left
 *	Index:     0     1     2     3
 *	Data:     [A]   [B]   [C]   [D]
 *
 *	erase(v, 1); // Wants to delete B
 *
 *	Result:   [A]   [C]   [D]   [?]
 * When erasing an element, the last 'cell' continues to exsist, but the length is decreasd by 1.
 * So you cant reach it anymore. 
 *
 * Local var's:
 *		*dest			=	Memory address where you are moving (i.e. the location to be deleted)
 *		*src			=	Address of the next (right) element to be placed in the position of 'dest'
 *		bytes_to_move	=	The size that has to be moved. E.g erase 2 (C): vector.length(4) - index_pos(2) = 2 then - 1 because you don’t want to copy the element itself – 
 *							only those after (Array starts at 0)
 */
CvecError erase(Cvec *v, size_t index_pos) 
{
	if(v->length > 0) // Checks if Cvec is empty
	{
		if(index_pos >= v->length) {
			return CVEC_ERR_INDEX_OUT_OF_BOUNDS;
		}
		void *dest = (char*)v->data + index_pos * v->element_size;
		void *src  = (char*)v->data + (index_pos + 1) * v->element_size;
		size_t bytes_to_move = (v->length - index_pos - 1) * v->element_size;
		
		memmove(dest, src, bytes_to_move); // moves the content of src to dest
		v->length--;
		
		return CVEC_OK;
	}
	return CVEC_ERR_EMPTY;
}

// Deletes n... m elements
/*
 * Same like erase() but with more elements.
 */
CvecError erase_range(Cvec *v, size_t begin, size_t end)
{
    if (v->length == 0)
        return CVEC_ERR_EMPTY;

    if (begin > end || end >= v->length)
        return CVEC_ERR_INVALID_RANGE;

    size_t count = end - begin + 1;

    void *dest = (char*)v->data + begin * v->element_size;
    void *src  = (char*)v->data + (end + 1) * v->element_size;
    size_t bytes_to_move = (v->length - end - 1) * v->element_size;

    memmove(dest, src, bytes_to_move);

    v->length -= count;

    return CVEC_OK;
}

CvecError shrink_to_fit(Cvec *v)
{
	void *temp = realloc(v->data, v->length * v->element_size);
	if(temp == NULL) {
		return CVEC_ERR_ALLOC;
	}
	v->data = temp;
	v->capacity = v->length;

	return CVEC_OK;
}

void cvec_free(Cvec *v) 
{
    if (v->datatype == CVEC_STRING) {
        for (size_t i = 0; i < v->length; ++i) {
            char **ptr = (char**)v->data;		// char** because the vector is a array of char arrays. 
            free(ptr[i]);
        }
    }

    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
}
