#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

void printHelp() {
	printf("This program transpiles sendodoLang to C.\n");
}

void outputCProg(char * filename, char * outputname) {
	// open file
	FILE *fptr;

	printf("#include <stdio.h>\n#include <stdlib.h>\n");
	printf("int main() {\n");

	printf("}\n");
}

int main(int argc, char * argv[]) {
	int opt;
	int verbose = 0;
	char inName[50];
	char outName[50];

	int inputsOK = 0;

	while((opt = getopt(argc, argv, "vhHtw:o:")) != -1)
	{
		switch(opt)
		{
			case 'h':
			case 'H':
				printHelp();
				return 1;
			case 'v':
				verbose = 1;
				printf("verbose mode on\n");
				break;
			case 't':
				strcpy(inName, optarg);
				if (verbose) printf("filename: %s\n", inName);
				inputsOK |= 1;
				break;
			case 'o':
				strcpy(outName, optarg);
				if (verbose) printf("filename: %s\n", outName);
				inputsOK |= 2;
				break;
		}
	}

	if (inputsOK && 3)
		outputCProg(inName, outName);
	else
	{
		if (inputsOK && 1 == 0) printf("input filename missing\n");
		if (inputsOK && 2 == 0) printf("output filename missing\n");
	}

	return 1;
}
