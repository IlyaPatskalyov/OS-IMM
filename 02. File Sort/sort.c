#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

struct Pair
{
	int	key;
	unsigned int value;
};

struct Pair data[MAX];

void quit(int exitCode, char * message){
	printf("%s", message);
	exit(exitCode);
}


unsigned int n;

int increment(int key){
	int i;
	for(i = 0; i < n; i++)
		if (data[i].key == key){
			data[i].value++;
			if (data[i].value == 0)
				return 2;
			return 0;
		}
	if (n >= MAX)
		return 1;
	data[n].key = key;
	data[n].value = 1;
	n++;
	return 0;
}

int compare (const void * a, const void * b)
{
	return ( (*(struct Pair*)a).key - (*(struct Pair*)b).key );
}


int main(int argc, char** argv) {
	int i,j,t, code;

	if (argc < 2)
		quit(1, "Usage: sort [input-file-1] [input-file-n] [output-file]");
	
	for(i = 1; i < argc-1; i++){	
		FILE * f = fopen(argv[i], "r");
		if (!f)
			quit(2, "Could not open file");
		while (!feof(f)){
			code = fscanf(f, "%d", &t);
			if (!code){
				fclose(f);
				quit(10, "In file not integer");
			}
			code = increment(t);
			switch(code){
				case 1:
				case 2:
					 quit(20, "Not enought buffer");
			}
		}
		code = fclose(f);
		if (code)
			quit(3, "Could not close file");
	}	


	qsort (data, n, sizeof(struct Pair), compare);

	FILE * fout = fopen(argv[argc-1], "w");
	if (!fout)
		quit(2, "Could not open file for write");
	for(i = 0; i < n; i++){
		for(j = 0; j < data[i].value; j++){
			code = fprintf(fout, "%d\n", data[i].key);
			if (code < 0){
				fclose(fout);
				quit(11,"Could not write file");
			}
		}			
	}
	fclose(fout);
	return 0;
}
