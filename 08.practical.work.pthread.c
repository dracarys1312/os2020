#include <stdio.h>
#include <pthread.h>

void* PrimeNum(void *args){
	pthread_detach(pthread_self());
	printf("\nPrime numbers from 2 to 1000000:\n");

	int i,j;
	for (i=2;i<=1000000;i++){
		for (j=2;j<=i;j++){
			if (j==i) printf("%d ",i);
			else if (i%j==0) break;	
		}
	}

	pthread_exit(NULL);
}

void *FiboSeq(void *args){
	pthread_detach(pthread_self());
	printf("\nFibonacci sequence from 2 to 1000000:\n");
	
	long int f[1000000];
	f[0]=0;
	f[1]=1;
	
	int k=2;	
	while (1){
		f[k]=f[k-1]+f[k-2];
		
		if (f[k]<1000000){
			printf("%ld ",f[k]);
			k++;
		}
		else break;
	}
	
	pthread_exit(NULL);
}

void main(){
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1,NULL,PrimeNum,NULL);
	pthread_create(&tid2,NULL,FiboSeq,NULL);

	printf("Created new threads (%lu) and (%lu)\n",tid1,tid2);
	
	pthread_exit(NULL);
}

