#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

// check if file is a directory or otherwise
bool is_dir(const char* path) {
	struct stat buffer;
	if(stat(path,&buffer)==0){
		if(S_ISDIR(buffer.st_mode)){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}
void process_path(const char*);


void process_directory(const char* path) {
	DIR *folder;
	struct dirent *dir;
	// cd into path
	chdir(path);
	// open current directory
	folder = opendir(".");
	// check if it exists
	if(folder == NULL) {
		return;
	}
	// increment number of directories
	num_dirs++;

	// go through every file in that directory
	while( (dir=readdir(folder)) != NULL) {
		// check to make sure we do not process . and ..
		if( strcmp(dir -> d_name, ".") && strcmp( dir -> d_name, "..") != 0) {
			// call process path on the current file 
			process_path(dir -> d_name);
		}
	}
	// close folder
	closedir(folder);
	// cd into previous directory
	chdir("..");
}

void process_file(const char* path) {
  num_regular++;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
