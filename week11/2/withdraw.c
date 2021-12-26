#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct account{
    int saving; // 계좌에 있는 실제 잔액
    int balance; // 통장에 찍힌 잔액 숫자
    int amount; // 인출할 금액
}Account;

int disburse_money(Account *account){
    // 계좌의 실제 잔액을 업데이트
    account->saving = account->balance;
    printf("실제 잔액: %d\n",account->saving);

    // 정상 종료
    return 0;
}

void *withdraw(void *acc){
    sleep(1);
    Account *this_account = (Account *) acc;
    
    // 잔액 확인 (우선은, balance를 업데이트)
    const int balance = this_account->balance;
    const int amount = this_account->amount;

    // 인출이 가능한지 확인
    if(balance < amount){
        printf("인출 불가\n"); // 인출이 안되면, 비정상 종료
        //exit(1);
    }
        
    // 통장 잔고를 업데이트
    this_account->balance = balance - amount;
    printf("통장 잔고: %d\n",this_account->balance);
    sleep(1);

    // 돈을 인출함 (saving값을 업데이트)
    disburse_money(this_account);

}

int main(void){
    struct account my_account1 = {1000,1000,10};
    struct account my_account2 = {2000,2000,10};
    pthread_t thing1, thing2; 

   while(1){
        pthread_create(&thing1, NULL, withdraw, (void *) &my_account1);
        pthread_create(&thing2, NULL, withdraw, (void *) &my_account2);
   }

    pthread_join(thing1, NULL);
    pthread_join(thing2, NULL);
}