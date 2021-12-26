#include <stdio.h>
#define INIT_NUM -999
#define ADD 1
#define SUB 2
#define MUL 3

// TODO: make a print msg
extern int add(int num, int num2);
extern int sub(int num, int num2);
extern int mul(int num, int num2);

const char *menu_msg = "<Calculater Menu>\n1. Add\n2. Sub\n3. Mul\nEnter : ";

int main(void){
	int menu =INIT_NUM;
	int num =INIT_NUM, num2 = INIT_NUM;
	
	printf("%s",menu_msg);
	scanf("%d",&menu);

	// Get Two Numbers from User
	printf("Enter two numbers : ");
	scanf ("%d %d", &num, &num2);
	
	// Print Results
	switch(menu){
		case ADD:
			printf("Result : %d + %d = %d\n",num,num2,add(num,num2));
			break;
		case SUB:
			printf("Result : %d - %d = %d\n",num,num2,sub(num,num2));
			break;
		case MUL:
			printf("Result: %d * %d = %d\n",num,num2,mul(num,num2));
			break;
		default :
			printf("Worng Selection\n");
	}

	return 0;
}
