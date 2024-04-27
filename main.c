#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


// each customer has a category. business_customer have a higher priority than private_customer
enum customer_category {
    BUSINESS_CUSTOMER, PRIVATE_CUSTOMER
};

// each customer has a request
enum request {
    ELECTRICITY, WATER, WASTE, INTERNET
};


typedef struct customer_key {
    int customer_category;
    int request;
} customer_key_t;


// compare two customer-keys
int comperator(void* a, void* b) {
    customer_key_t* key1 = (customer_key_t*)a;
    customer_key_t* key2 = (customer_key_t*)b;

    // buissnes customer have higher priority than private customers
    if (key1->customer_category != key2->customer_category) {
        return (key2->customer_category - key1->customer_category);
    }
    else { // if the category is the same, the customer's request decides 
        return (key2->request - key1->request);
    }
}

// this function is used to print the heap
void print_key(heap_element_t element) {
    customer_key_t* key = (customer_key_t*)element.key;
    printf("key: ");
    switch (key->customer_category) {
        case BUSINESS_CUSTOMER:
        printf("business_customer, ");
        break;
        case PRIVATE_CUSTOMER:
        printf("private_customer, ");
        break;
    }

    switch (key->request) {
        case ELECTRICITY:
        printf("electricity");
        break;
        case WATER:
        printf("water");
        break;
        case WASTE:
        printf("waste");
        break;
        case INTERNET:
        printf("internet");
        break;
    }

}

// this function only works, if the element-value is a string, and the element-key is a customer_key_t
void print_heap(heap_t* heap) {
    printf("\nnum_elements: %d, allocated memory: %d\n", heap->num_elements, heap->allocated_memory);
    printf("elements:\n");
    for (int i = 0; i < heap->num_elements; i++) {
        printf("name: %-20s", (char*)heap->elements[i].value);
        print_key(heap->elements[i]);
        printf("\n");
    }
    printf("\n");
}


int main(void) {
    // example of using the priority queue, with printing the heap after each step
    heap_t* heap = heap_create(3, comperator);
    
    customer_key_t key1 = { BUSINESS_CUSTOMER, INTERNET };
    heap_insert(heap, "Anna", &key1);
    print_heap(heap);

    customer_key_t key2 = { PRIVATE_CUSTOMER, WASTE };
    heap_insert(heap, "Benjamin", &key2);
    print_heap(heap);

    customer_key_t key3 = { BUSINESS_CUSTOMER, WATER };
    heap_insert(heap, "Christopher", &key3);
    print_heap(heap);

    customer_key_t key4 = { PRIVATE_CUSTOMER, WASTE };
    heap_insert(heap, "Daniela", &key4);
    print_heap(heap);

    void* next_customer;
    heap_remove_min(heap, &next_customer, NULL);
    printf("next customer: %s\n", (char*)next_customer);
    heap_remove_min(heap, &next_customer, NULL);
    printf("next customer: %s\n", (char*)next_customer);
    heap_remove_min(heap, &next_customer, NULL);
    printf("next customer: %s\n", (char*)next_customer);

    customer_key_t key5 = { PRIVATE_CUSTOMER, ELECTRICITY };
    heap_insert(heap, "Fabio", &key5);
    print_heap(heap);

    customer_key_t key6 = { BUSINESS_CUSTOMER, WATER };
    heap_insert(heap, "Emma", &key6);
    print_heap(heap);

    heap_remove_min(heap, &next_customer, NULL);
    printf("next customer: %s\n", (char*)next_customer);
    heap_remove_min(heap, &next_customer, NULL);
    printf("next customer: %s\n", (char*)next_customer);
    heap_remove_min(heap, &next_customer, NULL);
    printf("next customer: %s\n", (char*)next_customer);
    

    return EXIT_SUCCESS;
}