#include "sortlib.h"

int sort_file (/*@ in @*/  FILE *fpin,
		/*@ in @*/  FILE *fpout,
		/*@ in @*/ int   flag_r, //reverse
		/*@ in @*/ int   flag_s, //shuffle
		/*@ in @*/ int   flag_c) //count
{
	str_vector_t * array = str_vector_new();
	enum sort_mode mode;
	char line[BUFSIZ];
	if(!flag_c){
		if(flag_r){
			mode = DESC;
		}else if(flag_s){
			mode = ALEA;
		}else{
			mode = ASC;
		}
		
		while(fgets(line, BUFSIZ, fpin) != NULL){
			str_vector_append(array, line);
		}

		str_vector_sort(array, mode);
		
		for(int i = 0; i < array->tam; i++){
			fputs(array->str[i], fpout);
		}
	}else{
		int count = 0;
		int last_was_newline = 1;
		int c;
		while((c = getc(fpin)) != EOF){
			last_was_newline = (c == '\n');
			if(last_was_newline) count++;
		}
		if(!last_was_newline) count++;
		printf("Total de lineas en el archivo: %d\n", count);
	}
	
	str_vector_free(array);
	return 0;
}
