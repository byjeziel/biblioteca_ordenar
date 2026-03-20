# BibliotecaOrdenar
Proyecto integrador realizado durante la cursada de la materia "Seminario de C" de mi facultad.

Contiene el proyecto integrador y la consigna del proyecto realizado.

## Correcciones aplicadas

- **Colisión de responsabilidades malloc/free:** `str_vector_append` ahora hace `strdup` internamente, siendo la estructura dueña de sus strings. Se eliminó el `malloc`/`strcpy` manual en `sort_file`.
- **Doble `fopen` con leak de descriptor:** Se fusionaron los dos bloques de apertura de archivo en uno solo con manejo de error integrado.
- **`exit(0)` sin `fclose` en la rama `--count`:** Reemplazado por flujo normal que garantiza el cierre de los descriptores.
- **Conteo incorrecto de líneas:** Variable `char c` cambiada a `int c` para detectar EOF correctamente. Se agregó lógica para contar la última línea cuando el archivo no termina en `\n`.
- **Off-by-one en macro `str_vector_set`:** La guarda `index <= tam` fue corregida a `index < tam`.

