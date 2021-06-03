#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"


int circular_buffer_create(struct circular_buffer_t* a, int N)
{
    if (a == NULL || N <= 0) { //sprawdzenie czy nie przekazujemy pustej zniennej i mniejszego lub zerowego siza
        return 1;
    }
    
    int* temp_array = (int*)malloc(N * sizeof(int)); //alokowanie pami�ci zraz z uzgodnieniem typ�w
    
    if (temp_array == NULL) { // b��d alokacji pami�ci 
        return 2;
    }
    // przypisywanie zmiennych defultowymi warosciami:
    a->ptr = temp_array; 
    a->begin = 0;
    a->end = 0;
    a->capacity = N;
    a->full = 0;
    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t** cb, int N) {
    
    if (cb == NULL || N <= 0) { //sprawdzenie czy nie przekazujemy pustej zniennej i mniejszego lub zerowego siza
        return 1;
    }
    
    *cb = malloc(sizeof(struct circular_buffer_t)); //alokacja sterty
    
    if (*cb == NULL) { // b��d alokacji pami�ci 
        return 2;
    }
    
    int res = circular_buffer_create(*cb, N); //alokacja pami�ci na ptr
   
   if (res == 1 || res == 2) { //b��dne dane b�d� b��d alokacji pami�ci
        free(*cb); //zwalnianie pami�ci 
        return 2;
    }
    
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t* a) {
    
    if (a != NULL) {
        free(a->ptr); //zwalanianie zalokowanej pami�ci 
    }
}

void circular_buffer_destroy_struct(struct circular_buffer_t** a) {
    
    if (a != NULL) {
        circular_buffer_destroy(*a); //zwalanianie zalokowanej pami�ci dal ptr
        free(*a); //zwalnianie pami�ci sterty
    }
}

int circular_buffer_push_back(struct circular_buffer_t* cb, int value) {
    
    if (cb == NULL || cb->capacity < 1 || cb->end > cb->capacity || cb->begin < 0 || cb->begin > cb->capacity || cb->end < 0) {
        return 1;
    }
    
    *(cb->ptr + cb->end) = value;
    
    if (cb->full == 1) {
        cb->end+=1;
        cb->begin+=1;
        
        if (cb->end == cb->capacity) {
            cb->end = 0;
            cb->begin = 0;
        }
    }
    
    else {
        cb->end += 1;
    }
    
    if (cb->end == cb->capacity) {
        cb->end = 0;
    }
    
    if (cb->end == cb->begin) {
        cb->full = 1;
    }
    
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t* a, int* err_code) {
    
    if (a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin < 0 || a->begin > a->capacity || a->end < 0) {
        
        if (err_code != NULL) {
            *err_code = 1;
        }
        
        return 1;
    }
    
    if (circular_buffer_empty(a) == 1) {
        
        if (err_code != NULL) {
            *err_code = 2;
        }
        
        return 2;
    }
    
    if (err_code != NULL) {
        *err_code = 0;
    }
    
    
    int retVal = *(a->ptr + a->begin);
    
    a->begin += 1;
    
    if (a->begin == a->capacity) {
        a->begin = 0;
    }
    
    a->full = 0;
    
    return retVal;
}
int circular_buffer_pop_back(struct circular_buffer_t* a, int* err_code) {
    
    if (a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin > a->capacity || a->begin < 0 || a->end < 0) {
        
        if (err_code != NULL) {
            *err_code = 1;
        }
        
        return 1;
    }
    
    if (circular_buffer_empty(a) == 1) {
        
        if (err_code != NULL) {
            *err_code = 2;
        }
        
        return 2;
    }
    
    if (err_code != NULL) {
        *err_code = 0;
    }
    
    a->end -= 1;
    
    if (a->end < 0) {
        a->end = a->capacity - 1;
    }
    
    int retVal = *(a->ptr + a->end);
    a->full = 0;
    return retVal;
}

int circular_buffer_empty(const struct circular_buffer_t* a) {
    
    if (a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin < 0 || a->begin > a->capacity || a->end < 0) {
        return -1; //b��dne dane wej�ciowe
    }
    
    if (a->begin == a->end && a->full == 0) {
        return 1; // w wbuforze nie ma rzadnych danych
    }
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t* a) {
    
    if (a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin < 0 || a->begin > a->capacity || a->end < 0) {
        return -1; //b��dne dane wej�ciowe
    }
    
    if (a->begin == a->end && a->full == 1) {
        return 1; //bufor jest caly zape�niony
    }
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t* a) {
    
    if (a == NULL || a->capacity < 1 || a->end > a->capacity || a->begin < 0 || a->begin > a->capacity || a->end < 0) {
        return; //b��dne dane wej�ciowe
    }
    
    if (circular_buffer_empty(a) == 1) {
        return; //je�eli bufor jest pusty nic nie wy�wietla
    }

    int number = a->begin;
    
    if (circular_buffer_full(a) == 1) { // je�eli bufor jst pe�en
        printf("%d ", *(a->ptr + number)); // wy�wietl to co si� zanjduje w buforze na pocz�tku
        number = (number+1) % a->capacity;
    }

    for (; number != a->end; number = (number+1) % a->capacity) { //do puki pocz�tek nie jest r�wny ko�cowi
        printf("%d ", *(a->ptr + number)); 
    }

}
