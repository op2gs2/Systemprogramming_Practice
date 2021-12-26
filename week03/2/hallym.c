#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int arg = -999;
	
	// Check argument count
	if (argc < 2){
		printf("ERROR: Please Provide at Lease one Option\n");
		exit(0);
	}

	// Execute code by argument
	while((arg = getopt(argc, argv, "ahu:")) !=-1 ){
		switch(arg){
			case 'a':
				printf("Welcome to System Programming (2021-2)\n");
				break;
			case 'u':
				printf("Nice to meet you, %s\n", optarg);
				break;
			case 'h':
				printf("-a: prints welcome message\n-u: prints argument\n");
				break;
		}
	}
	return 0;
}
