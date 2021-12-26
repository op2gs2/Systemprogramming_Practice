#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	// Variable for store file name.
	char *src_filename="\0", *dst_filename="\0";
	// Variable for File description.
	int read_des=-1, write_des=-1;
	// Variable for buffer to move data.
	char buf[100];
	
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
	read_des = open(src_filename, O_RDONLY);
	if (read_des == -1){
		fprintf(stderr,"Open Fail");
		exit(1);
	}
	
	// Open Write file stream
	printf("%s\n",dst_filename);
	write_des = open(dst_filename, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if (write_des == -1){
		fprintf(stderr,"Write Fail");
		exit(1);
	}
	
	// if argc == 3, Copy to original file to new fiie.
	if (argc == 3){
		while(read(read_des,&buf,100) != 0){
			write(write_des,&buf, 100);
	 	}
	 	printf("Copy is done!\n");
	 }
	 // if argc == 5, Copy and Encrypt given number to new file.
	 else{
	 	if (getopt(argc, argv, "c:") !=-1){
	 		while(read(read_des,&buf,1) != 0){
	 			buf[0] += (char) atoi(argv[2]);
				write(write_des,&buf, 1);
	 		}
	 		printf("Copy and Encryption is done!\n");
	 	}
	 	else {
	 		fprintf(stderr,"Wrong argument!");
	 		exit(1);
	 	}
	 }
	
	close(read_des);
	close(write_des);
 	return 0;
 }
	
