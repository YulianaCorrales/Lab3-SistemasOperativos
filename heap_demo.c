// heap_demo.c
2 #include <stdio.h>
3 #include <stdlib.h>
4
5 int main() {
6 int n = 10;
7 int *arr = (int *) malloc(n * sizeof(int));
8 if (arr == NULL) { perror("malloc"); return 1; }
9
10 for (int i = 0; i < n; i++) arr[i] = i * i;
11 printf("Arreglo original: ");
12 for (int i = 0; i < n; i++) printf("%d ", arr[i]);
13 printf("\n");
14
15 /* Redimensionar a 20 enteros */
16 arr = (int *) realloc(arr, 20 * sizeof(int));
17 if (arr == NULL) { perror("realloc"); return 1; }
18 for (int i = n; i < 20; i++) arr[i] = i * i;
19
20 printf("Arreglo ampliado: ");
21 for (int i = 0; i < 20; i++) printf("%d ", arr[i]);
22 printf("\n");
23
24 free(arr);
25 return 0;
26
