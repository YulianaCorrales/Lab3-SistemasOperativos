# Laboratorio de Sistemas Operativos — Gestión de Memoria — Práctica No. 3

**Universidad de Antioquia — Facultad de Ingeniería — Ingeniería de Sistemas**

---

## a) Integrantes

| Nombre | Correo | Documento |
|---|---|---|
| Yuliana Corrales Castaño | yuliana.corralesc@udea.edu.co | 39193015 |
| Hellen Jakeline Rubio Casas | hellen.rubio@udea.edu.co | 1001686406 |

---

## b) Documentación de funciones desarrolladas

### `mem_map.c`
- **`main()`**: Imprime el PID del proceso y las direcciones virtuales de cuatro variables representativas: `main` (segmento de código), `global_var` (segmento de datos), `local_var` (stack) y `heap_var` (heap). Queda en pausa con `getchar()` para permitir inspeccionar `/proc/[pid]/maps` desde otra terminal mientras el proceso está activo.

### `heap_demo.c`
- **`main()`**: Demuestra el uso correcto de `malloc`, `realloc` y `free`. Asigna un arreglo de 10 enteros, lo llena con cuadrados, lo redimensiona a 20 enteros con `realloc`, lo llena completamente y lo libera. Sirve como referencia de manejo correcto de memoria dinámica sin fugas ni errores.

### `buggy_mem.c`
- **`main()`**: Contiene tres errores de memoria intencionales para demostración con Valgrind:
  - **ERROR 1:** buffer overflow — bucle con `<=` en lugar de `<`
  - **ERROR 2:** memory leak — bloque `q` nunca liberado
  - **ERROR 3:** use-after-free — acceso a `p[0]` después de `free(p)`

### `buggy_mem_fixed.c`
- **`main()`**: Versión corregida de `buggy_mem.c`:
  - **Corrección 1:** cambio de `<=` a `<` en el bucle
  - **Corrección 2:** se agrega `free(q)` antes de terminar
  - **Corrección 3:** se asigna `p = NULL` después de `free(p)`
  - Verificado con Valgrind sin errores ni fugas.

### `base_bounds.c`
- **`traducir(Registro r, int va)`**: Recibe un registro con campos `base` y `bounds` y una dirección virtual `va`. Verifica si `va` está dentro del rango `[0, bounds)`. Si es válida retorna `PA = base + va`. Si viola el bounds imprime excepción y retorna `-1`.
- **`main()`**: Define tres procesos (A, B y C) con distintos valores de base y bounds, y traduce un conjunto de VAs para cada uno mostrando resultados o excepciones.

### `paging_sim.c`
- **`traducir(int va)`**: Extrae el VPN (4 bits superiores) y el offset (4 bits inferiores) de la VA. Consulta la tabla de páginas: si la entrada es `-1` reporta PAGE FAULT; si es válida calcula `PA = (PFN << PAGE_BITS) | offset`.
- **`main()`**: Define un conjunto de VAs de prueba y llama a `traducir()` para cada una mostrando la tabla completa de traducciones.

### `fragmentation.c`
- **`main()`**: Asigna 10 bloques de memoria de tamaños variados, imprime sus direcciones para observar el patrón de separación de glibc, libera los bloques en índices pares para crear huecos e intenta asignar un bloque grande de 1500 bytes para observar el comportamiento del allocator ante la fragmentación.

### `tlb_locality.c`
- **`ms(struct timespec a, struct timespec b)`**: Calcula la diferencia en milisegundos entre dos marcas de tiempo. Retorna un `double`.
- **`main()`**: Asigna un arreglo de 4M enteros (16 MB). Mide el tiempo de acceso secuencial (alta localidad espacial) y el tiempo de acceso aleatorio usando un índice permutado con Fisher-Yates (baja localidad). Imprime ambos tiempos para comparar el impacto del TLB.

---

## c) Problemas presentados y soluciones

| Problema | Solución |
|---|---|
| Al compilar desde CMD de Windows, `./mem_map` no era reconocido | Se identificó que la terminal activa era CMD en lugar de WSL. Se ejecutó `wsl` para cambiar al entorno Linux |
| `paging_sim.c` se creó con el comando `cat` dentro del código | Se optó por crear todos los archivos directamente desde VS Code para evitar que comandos de shell quedaran dentro del código fuente |
| `perf` no disponible en WSL para medir contadores de TLB | Se documentó como limitación de WSL y se justificó la hipótesis con los resultados de tiempo obtenidos |
| `buggy_mem_fixed.c` quedó vacío en el primer intento | Se verificó el contenido antes de compilar y se usó Ctrl+S explícitamente para asegurar el guardado |
| GitHub no aceptó contraseña para hacer push desde WSL | Se generó un token de acceso personal desde GitHub Settings para autenticar correctamente |

---

## d) Pruebas realizadas

| Programa | Prueba | Resultado |
|---|---|---|
| `mem_map` | Lectura de `/proc/[pid]/maps` y `pmap -x` en segunda terminal | Direcciones impresas coincidieron con los rangos del mapa ✅ |
| `mem_map` | Ejecución simultánea de dos instancias comparando direcciones | Direcciones distintas en ambos procesos, confirma ASLR y aislamiento ✅ |
| `heap_demo` | Ejecución con `valgrind --leak-check=full --track-origins=yes` | 0 errores, 0 fugas, 3 allocs y 3 frees ✅ |
| `buggy_mem` | Ejecución con Valgrind | Detectó los 3 errores: buffer overflow, memory leak y use-after-free ✅ |
| `buggy_mem_fixed` | Ejecución con Valgrind tras correcciones | 0 errores, 0 fugas. `ERROR SUMMARY: 0 errors from 0 contexts` ✅ |
| `base_bounds` | Ejecución con VAs válidas e inválidas para procesos A, B y C | Traducciones correctas y excepciones generadas correctamente ✅ |
| `paging_sim` | Ejecución con 8 VAs distintas | Traducciones correctas y PAGE FAULTs detectados para VPN=1 y VPN=15 ✅ |
| `fragmentation` | Observación de direcciones y resultado de `malloc(1500)` | Patrón de 16 bytes confirmado; `malloc(1500)` exitoso por extensión del heap ✅ |
| `tlb_locality` | 3 ejecuciones midiendo acceso secuencial vs aleatorio | Factor promedio de ~12x más lento en acceso aleatorio ✅ |

---

## e) Video de sustentación

> **Enlace:** *(pendiente — agregar enlace al video una vez grabado)*

---

## f) Manifiesto de transparencia — Uso de IA generativa

Durante el desarrollo de esta práctica se utilizó **Claude (Anthropic)** como apoyo en los siguientes puntos:

| Sección | Uso de IA |
|---|---|
| Configuración del entorno | Orientación para resolver errores de compilación en WSL y creación de archivos desde VS Code |
| Secciones 1 a 7 | Apoyo en la redacción y estructuración de las respuestas conceptuales a partir de los resultados reales obtenidos en la terminal |
| Cálculos manuales (secciones 4 y 5) | Verificación de los cálculos de traducción de direcciones virtuales y tamaños de tabla de páginas |
| Diagramas | Generación del diagrama visual de fragmentación externa |
| Organización del informe | Estructuración y unificación del formato del informe completo |

Todos los programas fueron ejecutados por las estudiantes en su propio entorno y las salidas transcritas son reales. La IA no ejecutó ningún programa ni generó resultados inventados.

---

## g) Conclusiones

1. **El espacio de direcciones virtual es una abstracción fundamental del SO.** Cada proceso opera bajo la ilusión de tener toda la memoria para sí solo. Esto se comprobó empíricamente al observar que las direcciones virtuales de `mem_map` caen exactamente en los rangos de `/proc/maps`, y que dos instancias del mismo programa tienen direcciones virtuales completamente distintas gracias a ASLR, sin interferirse mutuamente.

2. **El manejo correcto de memoria dinámica es crítico en C.** Valgrind demostró que errores como buffer overflow, memory leak y use-after-free son silenciosos en tiempo de ejecución pero pueden tener consecuencias catastróficas en seguridad y estabilidad. La disciplina de verificar el retorno de `malloc` y liberar toda memoria asignada es indispensable en cualquier programa C de producción.

3. **La traducción de direcciones evoluciona para resolver limitaciones sucesivas.** Base & Bounds es simple pero desperdicia memoria al tratar el espacio como un bloque contiguo. La segmentación mejora la utilización pero genera fragmentación externa. La paginación elimina la fragmentación externa usando bloques de tamaño fijo, a costa de fragmentación interna acotada. Cada mecanismo surge como respuesta a las limitaciones del anterior.

4. **El TLB es esencial para que la paginación sea práctica.** Sin TLB cada acceso a memoria requeriría dos accesos físicos, duplicando el tiempo efectivo. Los resultados de `tlb_locality` confirmaron esto experimentalmente: el acceso aleatorio fue aproximadamente 12 veces más lento que el secuencial, confirmando el impacto directo del hit rate del TLB en el rendimiento.

5. **La gestión de memoria opera en dos niveles complementarios.** El allocator de usuario (glibc/malloc) minimiza las syscalls al kernel reutilizando memoria en espacio de usuario, mientras que el kernel gestiona la memoria física real con buddy system y slab allocator. Esta separación es fundamental para el rendimiento: si cada `malloc` requiriera una syscall los programas serían órdenes de magnitud más lentos.

6. **WSL impone limitaciones reales al análisis de bajo nivel.** La imposibilidad de usar `perf` para medir contadores de TLB directamente evidencia que la virtualización de WSL no expone completamente el hardware subyacente. En un entorno Linux nativo, herramientas como `perf stat` permitirían confirmar cuantitativamente los TLB misses y validar con precisión las hipótesis sobre localidad de memoria.
