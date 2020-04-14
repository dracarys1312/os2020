#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

void* PrimeNum(void *args){
	printf("\nPrime numbers from 2 to 1000000:\n");

	int i,j;
	for (i=2;i<=1000000;i++){
		for (j=2;j<=i;j++){
			if (j==i){
			       	pthread_mutex_lock(&lock);
				printf("%d ",i);
				pthread_mutex_unlock(&lock);
			}
			else if (i%j==0) break;	
		}
	}
}

void *FiboSeq(void *args){
	printf("\nFibonacci sequence from 2 to 1000000:\n");
	
	long int f[1000000];
	f[0]=0;
	f[1]=1;
	
	int k=2;	
	while (1){
		f[k]=f[k-1]+f[k-2];
		
		if (f[k]<1000000){
			pthread_mutex_lock(&lock);
			printf("%ld ",f[k]);
			pthread_mutex_unlock(&lock);
			k++;
		}
		else break;
	}
}

void main(){
	pthread_t tid1;
	pthread_t tid2;

	pthread_mutex_init(&lock,NULL);
	pthread_create(&tid1,NULL,PrimeNum,NULL);
	pthread_create(&tid2,NULL,FiboSeq,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	printf("Created new threads (%lu) and (%lu)\n",tid1,tid2);
		
	pthread_exit(NULL);
	pthread_mutex_destroy(&lock);
}

