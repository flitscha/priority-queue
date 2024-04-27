#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


heap_t* heap_create(int initial_size, int (*comperator)(void*, void*)) {
    // allocate memory for the heap struct
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
    if (heap == NULL) {
        return NULL;
    }

    // allocate memory for the heap elements
    heap_element_t* elements = (heap_element_t*)malloc(sizeof(heap_element_t)*initial_size);
    if (elements == NULL) {
        free(heap);
        return NULL;
    }

    heap->allocated_memory = initial_size;
    heap->elements = elements;
    heap->num_elements = 0;
    heap->comperator = comperator;
    return heap;
}


int heap_size(heap_t* heap) {
    return heap->num_elements;
}

int heap_is_empty(heap_t* heap) {
    return heap->num_elements > 0 ? 1 : 0;
}


void upheap(heap_t* heap, int index) {
    while (index >= 1) {
        heap_element_t e1 = heap->elements[index];
        // the element in the tree above index, is index / 2 (int division)
        heap_element_t e2 = heap->elements[index / 2];

        // compare the two keys, and swap if necessary
        if (heap->comperator(e1.key, e2.key) > 0) {
            heap->elements[index] = e2;
            heap->elements[index / 2] = e1;
        }
        index = index / 2;
    }
}


void heap_insert(heap_t* heap, void* value, void* key) {
    // double the heap capacity, if the heap is full
    if (heap_size(heap) >= heap->allocated_memory) {
        heap_element_t* new_elements = (heap_element_t*)malloc(sizeof(heap_element_t)*heap_size(heap)*2);
        if (new_elements == NULL) {
            fprintf(stderr, "malloc error in heap_insert()\n");
            return;
        }
        // copy
        for (int i = 0; i < heap_size(heap); i++) {
            new_elements[i] = heap->elements[i];
        }
        free(heap->elements);
        heap->elements = new_elements;
        heap->allocated_memory *= 2;
    }

    // insert the new element at the end
    heap_element_t* elements = heap->elements;
    int index = heap->num_elements;
    elements[index].value = value;
    elements[index].key = key;
    heap->num_elements += 1;

    // reconstruct the heap-structure
    upheap(heap, index);
}


void downheap(heap_t* heap, int index) {
    while (index*2+1 <= heap->num_elements) {
        // if the current element has a larger key than one of its children, we need to swap it
        // with the child that has the smaller key

        // get the children
        heap_element_t child1 = heap->elements[index*2];
        heap_element_t child2 = child1; // child2 = child1, if the node has no child2
        if (index*2+1 <= heap->num_elements) { // we have to check, if the node has a right child
            child2 = heap->elements[index*2+1];
        }

        // check, if the current element is bigger than one of the children
        if (heap->elements[index].key >= child1.key || heap->elements[index].key >= child2.key) {
            if (heap->comperator(child2.key, child1.key) > 0) {
                // swap with child2
                heap->elements[index*2+1] = heap->elements[index];
                heap->elements[index] = child2;
                index = index*2+2;
            } else {
                // swap with child1
                heap->elements[index*2] = heap->elements[index];
                heap->elements[index] = child1;
                index = index*2+1;
            }   
        } else {
            // nothing to swap. We finished the downheap
            return;
        }
    }
}


void heap_min(heap_t* heap, void** value, void** key) {
    // if the heap is empty, or something is not correct, write NULL into value and key
    if (heap == NULL || heap->num_elements <= 0 || heap->elements == NULL) {
        if (value != NULL) *value = NULL;
        if (key != NULL) *key = NULL;
        return;
    }

    // otherwise get the value and key of the first element
    if (value != NULL) *value = heap->elements[0].value;
    if (key != NULL) *key = heap->elements[0].key;
}


void heap_remove_min(heap_t* heap, void** value, void** key) {
    // call heap_min to get the value and key
    heap_min(heap, value, key);

    // return if the heap is empty
    if (heap == NULL || heap->num_elements <= 0 || heap->elements == NULL) {
        return;
    }

    // otherwise remove the first element by swapping it with the last element
    heap_element_t* elements = heap->elements;
    elements[0] = elements[heap->num_elements-1];
    heap->num_elements -= 1;
    downheap(heap, 0);

    // free some memory, if the heap gets small
    if (heap->num_elements <= heap->allocated_memory / 4) {
        heap_element_t* new_elements = (heap_element_t*)malloc(sizeof(heap_element_t)*(heap->allocated_memory)/2);
        if (new_elements == NULL) {
            fprintf(stderr, "malloc error in heap_remove_min\n");
            return;
        }
        // copy
        for (int i = 0; i < heap_size(heap); i++) {
            new_elements[i] = heap->elements[i];
        }
        free(heap->elements);
        heap->elements = new_elements;
        heap->allocated_memory /= 2;
    }
}


heap_t* heapify(heap_element_t* elements, int num_elements, int (*comperator)(void*, void*)) {
    if (elements == NULL || num_elements <= 0 || comperator == NULL) {
        return NULL;
    }

    // create the heap struct
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
    if (heap == NULL) {
        return NULL;
    }
    heap->allocated_memory = num_elements;
    heap->num_elements = num_elements;
    heap->comperator = comperator;
    heap->elements = elements;

    // bottom up heap construction
    for (int i = heap->num_elements / 2; i >= 0; i--) {
        downheap(heap, i);
    }
    return heap;
}


