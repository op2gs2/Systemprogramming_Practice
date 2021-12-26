#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>

int main(int argc, char* argv[]){
	// Variable for store file name.
	char *src_filename="\0", *dst_filename="\0";
	// Variable for File pointer.
	FILE *fread, *fwrite;
	// Variable for buffer to move data.
	char buf[100]; int c;
	int select;
	
	// Get file name, name is different depending on argument numbers.
	if(argc == 3){
		src_filename = argv[1];
		dst_filename = argv[2];
	}
	
	else if(argc==5){
		src_filename = argv[3];
		dst_filename = argv[4];
	}
	
	else {
		fprintf(stderr,"Wrong argument number!");
	 	exit(1);
	}
	
	// Check filename is stored.
	if(src_filename == "\0" || dst_filename == "\0"){
		fprintf(stderr, "Filename is not in variable.");
		exit(1);
	}
	
	// Open read file stream
	printf("%s\n",src_filename);
	if((fread = fopen(src_filename, "r"))==NULL){
		fprintf(stderr,"Read Fail");
		exit(1);
	}
	
	// Open Write file stream
	printf("%s\n",dst_filename);
	if((fwrite = fopen(dst_filename, "w")) == NULL){
		fprintf(stderr,"Write Fail");
		exit(1);
	}
	
	// if argc == 3, Copy to original file to new fiie.
	if (argc == 3){
		while(fgets(buf,100,fread) != NULL){
			fputs(buf, fwrite);
	 	}
	 	printf("Copy is done!\n");
	 }
	 // if argc == 5, Copy and Encrypt given number to new file.
	 else{
	 	if ((select = getopt(argc, argv, "cd:")) !=-1){
	 		switch(select){
	 			case 'c':
	 				while((c = fgetc(fread))>0){
	 					//printf("Original: %d\n",c);
	 					c += (char) atoi(argv[2]);
	 					//printf("New: %d\n",c);
	 					fputc(c, fwrite);
	 				}
	 				printf("Copy and Encryption is done!\n");
	 				break;
	 			case 'd':
	 				while((c = fgetc(fread))>0){
	 					//printf("Original: %d\n",c);
	 					c -= (char) atoi(argv[2]);
	 					//printf("New: %d\n",c);
	 					fputc(c, fwrite);
	 				}
	 				printf("Copy and Decryption is done!\n");
	 				break;
	 		}
	 		
	 		
	 	}
	 	
	 	else {
	 		fprintf(stderr,"Wrong argument!");
	 		exit(1);
	 	}
	 }
	
	fclose(fread);
	fclose(fwrite);
	
	return 0;
}
