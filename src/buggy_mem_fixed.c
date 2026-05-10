// buggy_mem_fixed.c -- version corregida
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    /* CORRECCIÓN 1: cambiar <= por < para evitar buffer overflow */
    int *p = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++)
        p[i] = i;

    /* CORRECCIÓN 2: agregar free(q) para evitar memory leak */
    char *q = malloc(100);
    strcpy(q, "hola mundo");
    printf("%s\n", q);
    free(q);

    /* CORRECCIÓN 3: no usar p después de free, asignar NULL */
    free(p);
    p = NULL;

    return 0;
}