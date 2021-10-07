#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUF_SIZE 1024

bool is_vowel(char ch) {
    if (ch =='a' || ch =='e' || ch =='i' || ch == 'o' || ch == 'u')
		return true;
    if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
		return true;

	 return false;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    int counter = 0;
    for(int i = 0; i < num_chars; i++){
    	if(is_vowel(in_buf[i]) == false){
		out_buf[counter] = in_buf[i];
		counter++;
	}
    }
    return counter;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    char* inputBuffer = (char*) calloc(BUF_SIZE,sizeof(char));
    char* outputBuffer = (char*) calloc(BUF_SIZE,sizeof(char));
    int count_nonvowels;
    int chunk_size = 1;
    while (chunk_size != 0) {
	 chunk_size = fread(inputBuffer,sizeof(char),BUF_SIZE,inputFile);
	 // printf("Chunk size = %d.\n", chunk_size);
	 count_nonvowels = copy_non_vowels(chunk_size,inputBuffer,outputBuffer);
 	 fwrite(outputBuffer,sizeof(char),count_nonvowels,outputFile);
	}
}
int main(int argc, char *argv[]) {
	FILE *inputFile = stdin;
        FILE *outputFile = stdout;
	if(argc == 1){
		disemvowel(inputFile, outputFile);
	}
	if(argc == 2){
		inputFile = fopen(argv[1],"r+");
		disemvowel(inputFile, outputFile);
		fclose(inputFile);
	}
	if(argc == 3){
		inputFile = fopen(argv[1],"r+");
		outputFile = fopen(argv[2], "r+");
    		disemvowel(inputFile, outputFile);
		fclose(inputFile);
		fclose(outputFile);
	}
    	return 0;
}
