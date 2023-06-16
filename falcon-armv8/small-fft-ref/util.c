#include "inner.h"
#include <stdio.h>

void print_farray(fpr *r, unsigned logn, const char *string)
{
    printf("%s:\n", string);
    const unsigned n = 1 << logn;
    for (unsigned i = 0; i < n; i++)
    {
        // printf("[%3d]:%.20f\n", i, r[i]);
        // printf("[%3d]:%f\n", i, r[i].v);
        printf("%.10f, ", i, r[i].v);
    }
    printf("\n");
    fflush(stdout); 
}

void print_iarray(int8_t *a, const char* string)
{
    printf("%s:\n", string);
    for (int i =0; i < 512; i++)
    {
        printf("%d, ", a[i] & 0xff);
    }
    printf("\n");
    fflush(stdout);
}
