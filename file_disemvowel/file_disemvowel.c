#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUF_SIZE 1024

// check if current character is a vowel
bool is_vowel(char ch) {
    if (ch =='a' || ch =='e' || ch =='i' || ch == 'o' || ch == 'u')
		return true;
    if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
		return true;

	 return false;
}


int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    int counter = 0;

    // copy the non-vowel characters from in buffer to out buffer
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

    // while there is still info to read
    while (chunk_size != 0) {
	 // read file up to buf size and store info in chunk_size
	 chunk_size = fread(inputBuffer,sizeof(char),BUF_SIZE,inputFile);
	 // call copy_non_vowels on chunk_size and store result in count_nonvowels
	 count_nonvowels = copy_non_vowels(chunk_size,inputBuffer,outputBuffer);
	 // write current sequence of  nonvowel characters in outputBuffer to outputFile
 	 fwrite(outputBuffer,sizeof(char),count_nonvowels,outputFile);
	}
    free(inputBuffer);
    free(outputBuffer);
}
int main(int argc, char *argv[]) {
	FILE *inputFile;
        FILE *outputFile;

	// if no additional arguments are called
	// set inputFile and outputFile to standard input and output
	if(argc == 1){
		inputFile = stdin;
		outputFile = stdout;
		disemvowel(inputFile, outputFile);
	}

	// if script called with one additional argument
	// set input file to argument given
	// set outputFile to standard output
	if(argc == 2){
		inputFile = fopen(argv[1],"r+");
		outputFile = stdout;
		disemvowel(inputFile, outputFile);
		fclose(inputFile);
	}

	// if script was called with two additional arguments
	// set inputFile to first argument given
	// set outputFile to second argument given
	if(argc == 3){
		inputFile = fopen(argv[1],"r+");
		outputFile = fopen(argv[2], "w+");
    		disemvowel(inputFile, outputFile);
		fclose(inputFile);
		fclose(outputFile);
	}
    	return 0;
}
