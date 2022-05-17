#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <sys/types.h>
#include <string.h>
#include <error.h>

int icecreamremaining=3;

sem_t s;
void salesman(void *num);

int main(){
pthread_t t[icecreamremaining];
sem_init(&s,0,1);
int i;
int a[icecreamremaining];
printf("\n Number of ice creams are : %d\n\n", icecreamremaining);
for (i=0; i<icecreamremaining ; i++){
a[i]=i;
pthread_create(&t[i],NULL,(void*)&salesman,(void*)&a[icecreamremaining]);
}
for (i=0; i<icecreamremaining ; i++)
pthread_join(t[i],NULL);

if(!icecreamremaining)
printf("\n No icecream left\n");

sem_destroy(&s);
return 0;}

void salesman(void* num){
int i= *(int*)num;
sem_wait(&s);
printf("customer %d buying \n",i+1);
icecreamremaining--;
printf("remaining icecream %d \n\n",icecreamremaining);
sem_post(&s);
pthread_exit(0);
}
