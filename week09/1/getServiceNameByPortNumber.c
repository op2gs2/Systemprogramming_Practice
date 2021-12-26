#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
// Print Error, If argc is 1.
	if(argc == 1){
		fprintf(stderr,"Argument Number Error!\n");
		exit(2);
	}

    printf("--- Port Service Name List ---\n");
    
    for(int i=1; i < argc; i++){
        #ifdef DEBUG
            printf("1. Call GetPort()\n");
        #endif

	    GetPort(atoi(argv[i]));
    }

    return 0;
}

int GetPort(int port){

    struct servent *sp;

    #ifdef DEBUG
        printf("2. Search Port Service. Port is %d.\n",port);
    #endif

// Get Port Information.
    sp = getservbyport(htons(port), NULL);

// Print Port Service Name
    if(sp){
        #ifdef DEBUG
            printf("3. Print Port Service Name.\n");
        #endif

        printf("%s\n", sp->s_name);
    }
}