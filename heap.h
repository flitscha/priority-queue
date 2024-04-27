#ifndef HEAP_H
#define HEAP_H


typedef struct heap_element {
    void* key;
    void* value;
} heap_element_t;

typedef struct heap {
    int (*comperator)(void*, void*);
    int num_elements;
    int allocated_memory;
    heap_element_t* elements;
} heap_t;


// creates a new heap and allocates memory for 'initial_size' elements
heap_t* heap_create(int initial_size, int (*comperator)(void*, void*));


// converts a list of heap_values ​​into a heap
heap_t* heapify(heap_element_t* elements, int num_elements, int (*comperator)(void*, void*));


// creates an entry with key 'key' and value 'value'
void heap_insert(heap_t* heap, void* value, void* key);


// returns the element in the heap with the smallest key
// if the heap is empty, NULL gets written into key and value.
void heap_min(heap_t* heap, void** value, void** key);


// returns the element with the smallest key, such as heap_min(), but removes it from the heap
void heap_remove_min(heap_t* heap, void** value, void** key);


// returns the number of elements in the heap
int heap_size(heap_t* heap);


// returns 1, if the heap is empty
int heap_is_empty(heap_t* heap);


#endif // HEAP_H

