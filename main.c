#include "sortlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "error-sort.h"

void help(){
    puts("Este programa se utiliza mediante los siguientes argumentos:");
    puts("-r o --reverse\nInvierte la condición de ordenación.");
    puts("-s o --shuffle\nOrdena de forma aleatoria(no imprime repetidos).");
    puts("Si se omiten -r o -s se ordenara el archivo en el orden dado por los ASCII de sus elementos.");
    puts("-i <archivo> o --input <archivo>\nLee las líneas desde el archivo indicado.\nSi se omite se leen desde stdin.");
    puts("-o <archivo> o --output <archivo>\nEscribe los resultados en el archivo indicado.\nSi se omite se escriben en stdout.");
    puts("-c o --count\nCuenta la cantidad de líneas en el archivo de entrada e imprime el resultado en la salida estándar.");
}

int args_validate(
        int argc,
        char *argv[],
        char **arg_i,
        char **arg_o,
        int *reverse,
        int *shuffle,
        int *count
) {
    *arg_i = NULL; *arg_o = NULL; 
    for(int i = 1; i < argc; i++){
        if((!strcmp(argv[i], "-r")) || (!strcmp(argv[i], "--reverse"))){
            *reverse = 1;
        }else if((!strcmp(argv[i], "-s")) || (!strcmp(argv[i], "--shuffle"))){
            *shuffle = 1;
        }else if((!strcmp(argv[i], "-i")) || (!strcmp(argv[i], "--input"))){
            if((i + 1) < argc){
                *arg_i = argv[i+1];
                i++;
            }else{
                puts("Error: No se ingreso nombre del archivo.");
                return 3;
            }
        }else if((!strcmp(argv[i], "-o")) || (!strcmp(argv[i], "--output"))){
            if((i + 1) < argc){
                *arg_o = argv[i+1];
                i++;
            }else{
                puts("Error: No se ingreso nombre del archivo.");
                return 3;
            }
        }else if(!strcmp(argv[i], "-c") || (!strcmp(argv[i], "--count"))){
            *count = 1;
        }else if(!strcmp(argv[i], "--help")){
            help();
            exit(0);
        }else{
            printf("Argumento invalido \"%s\"\n", argv[i]);
            return 4;
        }
    }
    return 0;
}

int main(int argc, char *argv[]){
    
    int reverse, shuffle, count;
    FILE *input, *output;
    char *arg_i; char *arg_o;
    reverse = shuffle = count = 0;
    input = output = NULL;

    int error = args_validate(argc, argv, &arg_i, &arg_o ,&reverse, &shuffle, &count);

    if (error) {
        help();
        return 1;
    }

    if ((reverse) && (shuffle)) {
        puts("Error: no se puede usar -r --reverse y -s --shuffle a la vez.");
        help();
        return 2;
    }
    
    if(arg_i == NULL){
		input = stdin;
	}else{
		input = fopen(arg_i,"r");
		if(input == NULL){
			output_error(stderr, -E_FILE_ERROR);
			perror(" ");
			return -E_FILE_ERROR;
		}
	}

	if(arg_o == NULL){
		output = stdout;
	}else{
		output = fopen(arg_o,"w");
		if(output == NULL){
			output_error(stderr, -E_FILE_ERROR);
			perror(" ");
			if(input != stdin) fclose(input);
			return -E_FILE_ERROR;
		}
	}
    
    if(count){
        if((shuffle) || (reverse) || (output != NULL)){
            puts("Warning: se ignorarán los argumentos: \"-o , --output <archivo>, -s, --shuffle, -r, --reverse\".");
        } 
        sort_file(input, output, 0, 0, count);
        exit(0);
    }else{
		sort_file(input, output, reverse, shuffle, count);
	}
	
    fclose(input); fclose(output);
    
    return 0;
}
