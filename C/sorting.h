#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int (*Comparador)(const void* a, const void* b);

void selection_sort(void*, int, size_t, Comparador);
void insertion_sort(void*, int, size_t, Comparador);

#endif
