#include <stdio.h>
#include "circular_buffer.h"


int main() {
    int size = 0;
    struct circular_buffer_t* c_buf;
    int code;
    int action = 0;
    int num = 0;
    int retVal = 0;
    int break_while = 0;

    printf("Podaj rozmiar bufora: ");
    
    if (scanf("%d", &size) == 0) { //walidacja zczytywanej wartości bufora
        printf("Incorrect input");
        return 1;
    }
    
    if (size <= 0) { //sprawdzanie wprowadzonego typu danych
        printf("Incorrect input data");
        return 2;
    }
    
    if (circular_buffer_create_struct(&c_buf, size) == 2) { //sprawdznie poprawności alokacji pamięci
        printf("Failed to allocate memory");
        return 8;
    }
   
    while(1) {
        printf("Co chcesz zrobic? ");
        
        if (scanf("%d", &action) == 0) {//walidacja zczytywanej wartości bufora
            printf("Incorrect input");
            circular_buffer_destroy_struct(&c_buf); //uwalnianie pamięci niszczenie zalokowanej struktury
            return 1;
        }
        switch (action) {
        case 0: //zakończenie działania programu
            break_while = 1;
            break;
            
        case 1: //Dodanie elementu do tablicy
            printf("Podaj liczbe ");

            if (scanf("%d", &num) == 0) {
                printf("Incorrect input");
                circular_buffer_destroy_struct(&c_buf); //uwalnianie pamięci niszczenie zalokowanej struktury
                return 1;
            }

            circular_buffer_push_back(c_buf, num);
            break;
        case 2: //Pobranie ostatnio dodanego elementu do bufora
            if (circular_buffer_empty(c_buf) == 1) {
                printf("Buffer is empty\n");
                
            }
            else {
                retVal = circular_buffer_pop_back(c_buf, &code);
                printf("%d \n", retVal);
                
            }
            break;
        case 3: //Pobranie najwcześniej dodanego elementu do bufora
            if (circular_buffer_empty(c_buf) == 1) {
                printf("Buffer is empty\n");
                
            }
            else {
                retVal = circular_buffer_pop_front(c_buf, &code);
                printf("%d \n", retVal);
            }

            
            break;
        case 4: //Wyświetlanie całej zawartości bufora
            if (circular_buffer_empty(c_buf) == 1) {
                printf("Buffer is empty\n");
                
            }
            else {
                circular_buffer_display(c_buf);
                printf("\n");
            }
            break;
        case 5: //sprawdzanie czy bufor jest pusty
            retVal = circular_buffer_empty(c_buf);

            if (retVal == 1) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }
            break;
        case 6: //sprawdzanie czy bufor jest pełny
            retVal = circular_buffer_full(c_buf);

            if (retVal == 1) {
                printf("1\n");
            }
            else {
                printf("0\n");
            }
            break;
        default: //nieprawidłowa opcja
            printf("Incorrect input data\n");
        }
        if (break_while == 1) {
            break;
        }
    } 
    
    circular_buffer_destroy_struct(&c_buf); //uwalnianie pamięci niszczenie zalokowanej struktury
    return 0;
}