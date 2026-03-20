#include "str_vector_t.h"

str_vector_t * str_vector_new(){
	str_vector_t *vector;
	vector = (str_vector_t *) malloc(sizeof(str_vector_t));
	vector->str = NULL;
	vector->tam = 0;
	return vector;
};

void str_vector_append(str_vector_t *vector, char *string){
	char *copy = strdup(string);
	vector->tam++;
	vector->str = (char **) realloc(vector->str, (vector->tam) * sizeof(char **));
	vector->str[vector->tam-1] = copy;
};

void str_vector_append_sorted(str_vector_t *vector, char *string, enum sort_mode mode){
	if(vector->tam == 0){
		str_vector_append(vector, string);
	}else if(mode == ASC || mode == DESC){
		vector->tam++;
		vector->str = (char **) realloc(vector->str, (vector->tam) * sizeof(char **));
		int i = 0;
		if(mode == ASC){
			while((i < (vector->tam-1)) && (strcmp(string, vector->str[i]) > 0)){
				i++;
			}
		}else{
			while((i < (vector->tam-1)) && (strcmp(string, vector->str[i]) < 0)){
				i++;
			}
		}
		for(int j = vector->tam-1; j>i; j--){
			vector->str[j] = vector->str[j-1];
		}
		vector->str[i] = string;
	}else{
		str_vector_append(vector, string);
	}
};

void str_vector_resize(str_vector_t *vector, unsigned elements){
	for(int i = elements; i < vector->tam; i++)
		free(vector->str[i]);
	vector->tam = elements;
	vector->str = (char **) realloc(vector->str, (vector->tam) * sizeof(char **));
};

int compare_asc(const void *str1, const void *str2){
	return strcmp(*(char **)str1, *(char **)str2);
};

int compare_desc(const void *str1, const void *str2){
	return strcmp(*(char **)str2, *(char **)str1);
};

void swap(char **str1, char **str2){
	char * temp = *str2;
	*str2 = *str1;
	*str1 = temp;
};

void str_vector_sort(str_vector_t *vector, enum sort_mode mode){
	switch(mode){
		case ASC:
			qsort(vector->str, vector->tam, sizeof(*(vector->str)), compare_asc);
			break;
		case DESC:
			qsort(vector->str, vector->tam, sizeof(*(vector->str)), compare_desc);
			break;
		case ALEA:{
			srand(time(NULL));
			for(int i = 0; i < vector->tam; i++){
				int j = rand() % ((vector->tam));
				swap(&vector->str[i], &vector->str[j]);
			}
			break;
		}
		default:
			printf("El modo no es valido\n");
			exit(7);
			break;
	}
};

void str_vector_free(str_vector_t *vector){
	for(int i = 0; i < vector->tam; i++)
		free(vector->str[i]);
	free(vector->str);
	free(vector);
};
