// buggy_mem.c -- NO ejecutar sin Valgrind
2 #include <stdio.h>
3 #include <stdlib.h>
4 #include <string.h>
5
6 int main() {
7 /* ERROR 1: buffer overflow */
8 int *p = malloc(5 * sizeof(int));
9 for (int i = 0; i <= 5; i++) /* <= en vez de < */
10 p[i] = i;
11
12 /* ERROR 2: memory leak (nunca se llama free(q)) */
13 char *q = malloc(100);
14 strcpy(q, "hola mundo");
15 printf("%s\n", q);
16
17 /* ERROR 3: use-after-free */
18 free(p);
19 printf("p[0] = %d\n", p[0]); /* acceso ilegal */
20
21 return 0;
22 }
