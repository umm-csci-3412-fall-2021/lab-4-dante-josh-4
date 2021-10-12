#include <ftw.h>
#include <stdio.h>

static int num_dirs, num_regular;

static int callback(const char *fpath, const struct stat *sb, int typeflag) {
	// check if file is a directory
	if(typeflag == FTW_D) {
		num_dirs++;
		return 0;
	}
	// check if file is a standard file
	if(typeflag == FTW_F) {
		num_regular++;
		return 0;
	}
	return 0;
}

#define MAX_FTW_DEPTH 16

int main(int argc, char** argv) {
	num_dirs = 0;
	num_regular = 0;
	
	// if no additional arguments are provided, then call ftw on current directory
	if (argc == 1) {
		ftw(".", callback, MAX_FTW_DEPTH);
	}

	// else call ftw on the path provided as an argument
	else{
		ftw(argv[1], callback, MAX_FTW_DEPTH);
	}
	printf("There were %d directories.\n", num_dirs);
  	printf("There were %d regular files.\n", num_regular);
	return 0;
}

