#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]){
	FILE *fp;
	long cur; // 오프셋의 위치를 저장하는 변수
	char buf[BUFSIZ] = {}, new_buf[BUFSIZ] = {}; // fread()에 의해, 읽은 내용을 임시 저장하는 변수
	char *file_name = argv[1]; // 명령행 인자로 받은 파일 이름을 저장하는 변수
	char *start_pos_char = argv[2]; // 명령행 인자로 받은 시작 위치를 저장하는 변수
	int start_pos_int = 0; //start_pos_char를 int형으로 변환했을 때, 저장할 변수
	int nbytes_to_read = atoi(argv[3]); // 명령행 인자로 받은, 이동할 위치를 저장하는 변수

	#ifdef DEBUG
	printf("파일 이름: %s\n",file_name);
	#endif

	// 인자 수가 맞지 않을 때, 에러를 출력하고 종료
	if(argc != 4){
		fprintf(stderr,"Wrong Argument Numbers");
		exit(1);
	}
	
	// 파일 열기, 실패할 경우 에러메시지를 출력하고 종료
	if((fp = fopen(file_name,"r")) == NULL){
		fprintf(stderr,"File Open Failed!");
		exit(1);
	}
	
	// 초기 위치를 출력
	cur = ftell(fp);
	printf("Initial Position: %ld\n", (long)cur);
	
	// 시작위치가 숫자로 지정되었을 때, 해당 위치에서 시작
	if(isdigit(start_pos_char[0]) > 0){
		start_pos_int = atoi(start_pos_char);

		#ifdef DEBUG
		printf("***시작 위치가 숫자로 지정됐을 때***\n");
		printf("시작지점: %d\n",start_pos_int);
		printf("이동지점: %d\n",nbytes_to_read);
		#endif

		// 시작위치가 음수가 아니면 그 자리에서 시작
		if (start_pos_int >= 0){
			int temp = fseek(fp, start_pos_int, SEEK_CUR);
			
			#ifdef DEBUG
			printf("시작위치가 양수: %d\n",temp);
			#endif

		} else { // 시작 위치가 음수라면 끝에서 시작
			int temp =fseek(fp, start_pos_int, SEEK_END);

			#ifdef DEBUG
			printf("시작위치가 음수: %d\n",temp);
			#endif
		}
	}
	// 시작위치가 문자열로 지정되었을 때, 문자열에 따라 위치를 지정
	else{
		if (strcmp(start_pos_char,"begin") == 0){
			rewind(fp);
		} else if(strcmp(start_pos_char,"mid") == 0){
			// 파일의 시작 지점 위치 값을 구한다.
			int start_point = fseek(fp, 0L, SEEK_SET);
			// 파일의 끝 지점 위치를 구하기 위해, offset을 이동
			fseek(fp, 0, SEEK_END);
			// 그리고, 그곳의 위치를 구한다.
			long end_point = ftell(fp);
			// 중간 지점의 위치값을 구한다.
			long mid_point = (end_point - start_point) / 2;
			
			#ifdef DEBUG
			printf("***시작지점이 중간일 때***\n");
			printf("시작위치: %d\n",start_point);
			printf("중간위치: %d\n",mid_point);
			printf("끝 위치: %d\n", end_point);
			#endif

			// 오프셋을 중간 지점의 위치값으로 설정한다.
			fsetpos(fp, (fpos_t *)&mid_point);
		} else if(strcmp(start_pos_char,"end") == 0){
			// 파일의 끝 지점 위치를 구하기 위해, offset을 이동
			fseek(fp, 0, SEEK_END);
			// 그리고, 그곳의 위치를 구한다.
			long end_point = ftell(fp);
			// 오프셋을 중간 지점의 위치값으로 설정한다.
			fsetpos(fp, (fpos_t *)&end_point);
		} else{
			fprintf(stderr,"Wrong Argument!");
			exit(1);
		}
	}

	#ifdef DEBUG
	printf("남은 읽기 수: %d\n", nbytes_to_read);
	#endif

	// 위에서 지정한 위치를 기반으로, 파일을 읽어들이는 과정
	int n = fread(buf, sizeof(char), nbytes_to_read, fp);

	#ifdef DEBUG
	printf("파일 읽기 성공: %d\n",n);
	printf("남은 읽기 수: %d\n", (nbytes_to_read-n));
	#endif

	buf[n] = '\0';
	if( n < nbytes_to_read){
		int m = 0;
		rewind(fp);
		m = fread(new_buf, sizeof(char), nbytes_to_read-n, fp);
		new_buf[m] = '\0';
		strcat(buf, new_buf);
	}
	// 마지막 위치를 출력하고, 결과를 출력
	#ifdef DEBUG
	printf("마지막 출력 과정\n",start_pos_int);
	#endif
	cur = ftell(fp);
	printf("Final Position: %ld\n", (long)cur);
	printf("Read Str: %s\n",buf);

	return 0;
}