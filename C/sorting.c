#include "sorting.h"

int main(void) {return 0;}

void selection_sort(void* arr, int arr_len, size_t arr_size, Comparador cmp) {
    void* temp = malloc(arr_size);
    for (int i = 0; i < arr_len-1; i++) {
        int min_index = i;
        for (int j = i+1; j < arr_len; j++) {
            if (cmp((char*)arr+(j*arr_size), (char*)arr+(min_index*arr_size)) < 0) {
                min_index = j;
            }
        }
        memcpy(temp, ((char*)arr+i*arr_size), arr_size);
        memcpy(((char*)arr+i*arr_size), ((char*)arr+min_index*arr_size), arr_size);
        memcpy(((char*)arr+min_index*arr_size), temp, arr_size); 
    }
    free(temp);
}

void insertion_sort(void* arr, int arr_len, size_t arr_size, Comparador cmp) {
    for (int i = 1; i < arr_len; i++) {
        void* key = malloc(arr_size);
        memcpy(key, (char*)(arr+(i*arr_size)), arr_size);
        int j = i-1;
        while (j >= 0 && cmp((char*)(arr+(j*arr_size)), key) > 0) {
            memcpy((char*)(arr+((j+1)*arr_size)), (char*)(arr+(j*arr_size)), arr_size);
            j--;
        }
        if ((char*)(arr+((j+1)*arr_size)) != key) {
            memcpy((char*)(arr+((j+1)*arr_size)), key, arr_size);
        }
    }
}
