#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

int verbose = 0;

void printHelp() {
	printf("This program transpiles sendodoLang (suggested file format: .dldl) to C.\n");
}

// returns the index of the first matched word
int match(char * bigStr, char * subStr) {
	int count = 0;
	int currentPosCnt = -1;
	int lenSubStr = strlen(subStr);
	int lenBigStr = strlen(bigStr);

	for (int i = 0; i < lenBigStr; i++)
	{
		if (count == 0)
		{
			if (bigStr[i] == subStr[0])
			{
				currentPosCnt = i;
				count ++;
			}
		}
		else 
		{
			count ++;
			if (bigStr[i] != subStr[count])
			{
				count = 0;
			}
			if (count == (lenSubStr - 1))
			{
				return currentPosCnt;
			}
		}
	}

	return currentPosCnt;
}

void outputCProg(char * filename, char * outputname) {
	// open file
	FILE *inPtr = fopen(filename, "r");

	if (inPtr == NULL)
	{
		printf("Error: could not open file %s\n", filename);
		return;
	}

	FILE *outPtr = fopen(outputname, "w");
	
	if (outPtr == NULL)
	{
		printf("Error: could not open file %s\n", outputname);
		return;
	}

	if (verbose) printf("success opening both files\n");

	fprintf(outPtr, "#include <stdio.h>\n#include <stdlib.h>\n");
	fprintf(outPtr, "int main() {\n");

	if (verbose) printf("program header written");

	char line[60];
	while (fgets(line, 60, inPtr) != NULL) {
		int found = match(line, "print");

		if (found != -1)
		{
			int openBracket = match(line, "\"");
			char contentString[60];

			strcpy(contentString, &(line[openBracket]));
			contentString[strlen(contentString) - 1] = '\0';

			fprintf(outPtr, "printf(\"%%s\\n\",");
			fprintf(outPtr, "%s", contentString);
			fprintf(outPtr, ");\n");
		}
		else
		{
			printf("compilation error");
			return;
		}
	}

	fprintf(outPtr, "}\n");
}

int main(int argc, char * argv[]) {
	int opt;
	char inName[50];
	char outName[50];

	int inputsOK = 0;

	while((opt = getopt(argc, argv, "vhHw:o:")) != -1)
	{
		switch(opt)
		{
			case 'h':
			case 'H':
				printHelp();
				return 0;
			case 'v':
				verbose = 1;
				printf("verbose mode on\n");
				break;
			case 'w':
				if (verbose) printf("filename: ");
				strcpy(inName, optarg);
				if (verbose) printf("%s\n", inName);
				inputsOK |= 1;
				break;
			case 'o':
				if (verbose) printf("filename: ");
				strcpy(outName, optarg);
				if (verbose) printf("%s\n", outName);
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
		return 1;
	}

	return 0;
}
