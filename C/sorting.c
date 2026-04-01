#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef int (*Comparador)(const void* a, const void* b);

void selection_sort(void*, int, size_t, Comparador);
void insertion_sort(void*, int, size_t, Comparador);
void bubble_sort(void*, int, size_t, Comparador);

void merge_sort(void*, int, size_t);
void merge(void*, void*, void*, int, size_t, Comparador);

void quick_sort(void*, size_t, int, int);
int partition(void*, size_t, int, int, Comparador);

int cmp(const void* a, const void* b) {
    return *(const int*)a - *(const int*)b;
}

int main(void) {return 0;}

void selection_sort(void* arr, int arr_len, size_t arr_size, Comparador cmp) {
    void* temp = malloc(arr_size);
    for (int i = 0; i < arr_len-1; i++) {
        int min_index = i;
        for (int j = i+1; j < arr_len; j++) {
            if (cmp((char*)arr+j*arr_size, (char*)arr+min_index*arr_size) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            memcpy(temp, (char*)arr+i*arr_size, arr_size);
            memcpy((char*)arr+i*arr_size, (char*)arr+min_index*arr_size, arr_size);
            memcpy((char*)arr+min_index*arr_size, temp, arr_size); 
        }
    }
    free(temp);
}

void insertion_sort(void* arr, int arr_len, size_t arr_size, Comparador cmp) {
    void* key = malloc(arr_size);
    for (int i = 1; i < arr_len; i++) {
        memcpy(key, (char*)arr+i*arr_size, arr_size);
        int j = i-1;
        while (j >= 0 && cmp((char*)arr+(j*arr_size), key) > 0) {
            memcpy((char*)arr+(j+1)*arr_size, (char*)arr+j*arr_size, arr_size);
            j--;
        }
        memcpy((char*)arr+(j+1)*arr_size, key, arr_size);
    }
    free(key);
}

void bubble_sort(void* arr, int arr_len, size_t arr_size, Comparador cmp) {
    void* temp = malloc(arr_size);
    for (int i = 0; i < arr_len-1; i++) {
        bool swap = false;
        for (int j = 0; j < arr_len - i - 1; j++) {
            if (cmp((char*)arr+j*arr_size, (char*)arr+(j+1)*arr_size) > 0) {
                memcpy(temp, (char*)arr+j*arr_size, arr_size);
                memcpy((char*)arr+j*arr_size, (char*)arr+(j+1)*arr_size, arr_size);
                memcpy((char*)arr+(j+1)*arr_size, temp, arr_size);
                swap = true;
            }
        }
        if (!swap) {
            break;
        }
    }
    free(temp);
}

void merge_sort(void* arr, int arr_len, size_t arr_size) {
    if (arr_len <= 1) {
        return;
    }

    int middle = arr_len / 2;
    void* left = malloc(middle * arr_size);
    void* right = malloc((arr_len - middle) * arr_size);

    int i = 0;
    int j = 0;

    for (; i < arr_len; i++) {
        if (i < middle) { // copia para a metade esquerda
            memcpy((char*)left+i*arr_size, (char*)arr+i*arr_size, arr_size);
        }
        else { // copia pra metade da direita
            memcpy((char*)right+j*arr_size, (char*)arr+i*arr_size, arr_size);
            j++;
        }
    }

    merge_sort(left, middle, arr_size);
    merge_sort(right, arr_len-middle, arr_size);
    merge(left, right, arr, arr_len, arr_size, cmp);

    free(left);
    free(right);
}

void merge(void* left, void* right, void* arr, int arr_len, size_t arr_size, Comparador cmp) {
    int left_len = arr_len / 2;
    int right_len = arr_len - left_len;

    int i = 0; // indice arr
    int l = 0; // indice left
    int r = 0; // indice right

    // enquanto tiver pelo menos um elemento em cada array pra comparacao
    while (l < left_len && r < right_len) {
        if (cmp((char*)left+l*arr_size, (char*)right+r*arr_size) <= 0) {
            memcpy((char*)arr+i*arr_size, (char*)left+l*arr_size, arr_size);
            l++;
        }
        else {
            memcpy((char*)arr+i*arr_size, (char*)right+r*arr_size, arr_size);
            r++;
        }
        i++;
    }

    // quando sobrar elemento em pelo menos um dos lados
    while (l < left_len) {
        memcpy((char*)arr+i*arr_size, (char*)left+l*arr_size, arr_size);
        l++;
    }
    while (r < right_len) {
        memcpy((char*)arr+i*arr_size, (char*)right+r*arr_size, arr_size);
        r++;
    }
}

void quick_sort(void* arr, size_t arr_size, int start, int end) {
    if (end <= start) {
        return;
    }

    int pivot = partition(arr, arr_size, start, end, cmp);
    quick_sort(arr, arr_size, start, pivot-1);
    quick_sort(arr, arr_size, pivot+1, end);
}

// no fim de cada chamada pra partition, os numeros menores que o pivot vao estar 
// a sua esquerda e os maiores a sua direita;
// a funcao retorna o indice do pivot no array;
int partition(void* arr, size_t arr_size, int start, int end, Comparador cmp) {
    int i = start-1;
    void* pivot = (char*)arr+end*arr_size;
    void* temp = malloc(arr_size);

    for (int j = start; j < end; j++) {
        if (cmp(pivot, (char*)arr+j*arr_size) > 0) {
            i++;
            memcpy(temp, (char*)arr+i*arr_size, arr_size);
            memcpy((char*)arr+i*arr_size, (char*)arr+j*arr_size, arr_size);
            memcpy((char*)arr+j*arr_size, temp, arr_size);
        }
    }
    i++;

    memcpy(temp, pivot, arr_size);
    memcpy(pivot, (char*)arr+i*arr_size, arr_size);
    memcpy((char*)arr+i*arr_size, temp, arr_size);

    free(temp);

    return i;
}
