#ifndef STR_VECTOR_T_
#define STR_VECTOR_T_ 1

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

// Retorna el elemento en la posición index del vector, si la
// posición index no existe retorna NULL.
#define str_vector_get(vector, index) (vector->str[index] != NULL) ? vector->str[index] : NULL

// Guarda el elemento en la posición index del vector, si el
// vector no tiene posiciones disponibles para tantos elementos,
// se lo debe agrandar para poder insertar el elemento.
#define str_vector_set(vector, index, elemento){\
	char *aux = malloc(strlen(elemento)+1);\
	if(aux == NULL){\
		output_error(fpin, -E_READ_ERROR);\
		exit(-E_READ_ERROR);\
	}\
	strcpy(aux, elemento);\
	if(index < vector->tam){\
		(vector->str[index] = aux);\
	}else{\
		printf("WARNING: El elemento se introducira al final de vector (%d), ya que no existe la posicion %d\n", vector->tam, index);\
		str_vector_append(vector, aux);\
	}\
}\

typedef struct{
	char ** str;
	unsigned int tam;
} str_vector_t;

enum sort_mode{ASC, DESC, ALEA};

/**
 * Retorna un vector vacío.
 */
str_vector_t * str_vector_new();

/**
 * Agrega un nuevo elemento al vector. La cadena no debe copiarse
 * sino que se almacena el puntero.
 * Si no hay espacio alocado para el nuevo elemento es necesario
 * agrandar el vector.
 */
void str_vector_append(str_vector_t *vector, char *string);

/**
 * Agrega un nuevo elemento al vector siguiendo el orden especificado
 * por `mode` (excepto el modo random o aleatorio). La cadena no debe
 * copiarse sino que se almacena el puntero.
 * Si no hay espacio alocado para el nuevo elemento es necesario
 * agrandar el vector.
 */
void str_vector_append_sorted(str_vector_t *vector, char *string, enum sort_mode mode);

/**
 * Redimensiona el vector para contener `elements` elementos.
 * Si el vector tiene más de `elements` elementos también
 * cambia el tamaño lógico del vector para que sea igual a
 * `elements`.
 */
void str_vector_resize(str_vector_t *vector, unsigned elements);

/**
 * Ordena el vector de acuerdo a el modo elegido.
 */
void str_vector_sort(str_vector_t *vector, enum sort_mode mode);

/**
 * Libera la memoria alocada para el vector.
 */
void str_vector_free(str_vector_t *vector);

#endif
