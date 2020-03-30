#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	printf("Main before fork()\n");
	int pid = fork();
	if (pid == 0) 
	{
		int pidb = fork(); 
		if (pidb == 0) 
		{
			printf("I am child after fork(), launching ps -ef\n");
			char *args[] = {"/bin/ps", "-ef", NULL};
			execvp("/bin/ps", args); 
			printf("--------------------------------------------------");
			printf("Finished launching ps -ef\n");
		}
		else {
			wait(NULL);
			printf("I am parent after fork(), child is %d\n", pidb);
		}
		printf("I am child after fork(), launching free -h\n");
		char *args[] = {"free", "-h", NULL};
		execvp("free", args); 
		printf("--------------------------------------------------");
		printf("Finished launching free -h\n");
	}
	else {
		wait(NULL);
		printf("I am parent after fork(), child is %d\n", pid);
	}
	return 0;
}
