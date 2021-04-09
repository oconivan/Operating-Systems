//
// Pthread example
// Author: Michael McGarry
// Date: 02/05/2012
//

#include <stdio.h>			// Standard I/O library
#include <unistd.h>			// UNIX system call library
#include <stdlib.h>			// Standard library: atol()
#include <signal.h>         // Signal handler library
#include <pthread.h>		// pthreads library

int fibNum = 0;
pthread_t tid1, tid2;
pthread_attr_t attr;

/*
 * Thread 1 generates the Fibonacci sequence written to fibonacci.dat
 * The argument specifies the number of Fibonacci numbers to generate
 */
void *computeFib(void *param)
{
	FILE *fibFile;
	unsigned long fib1, fib2, temp;
	
	fibFile = fopen("fibonacci.dat","w");
	
    fibNum = 1;
    fib1 = 1;
    fprintf(fibFile, "%lu\n", fib1);
    fibNum = 2;
    fib2 = 1;
    fprintf(fibFile, "%lu\n", fib2);
	for(fibNum=3; fibNum <= (long int) param; fibNum++)
	{
        temp = fib2;
        fib2 = fib2 + fib1;
        fib1 = temp;
		fprintf(fibFile, "%lu\n", fib2);
	}
	
	fclose(fibFile);
	
	pthread_exit(0);

}

/*
 * Thread 2 provides a mini-shell to provide interactivity with the user
 * The argument is ignored
 */
void *mini_shell(void *param)
{
	int inputSize;
	char buff[128];		// Character buffer

	while(1)
	{
		// Request a line of input
		printf("--> ");
		fflush(NULL);
		// Read the line
		inputSize = read(0, buff, 128);
		// Strip off carriage return
		buff[inputSize-1] = '\0';
		
		if(buff[0] == 's')
		{
			printf("Fibonacci progress: %d\n", fibNum);
		}
		else if(buff[0] == 'k')
        {
            pthread_kill(tid1, SIGKILL);
        }
		else
		{
			printf("Available commands - (s)how Fibonacci generation "
					"progress, (k)ill Fibonacci thread\n");
		}
		printf("\n");
		fflush(NULL);

	}

	pthread_exit(0);

}

int main(int argc, char **argv)
{

    if(argc < 2)
    {
        printf("Usage: pthreadExample num\n");
        return -1;
    }

    /* Set pthread attributes to defaults */
    pthread_attr_init(&attr);

    /* Setup a thread to compute the Fibonacci numbers */
    pthread_create(&tid1,&attr,computeFib,(void *)atol(argv[1]));

    /* Setup a mini shell thread to provide interactivity with the user */
    pthread_create(&tid2,&attr,mini_shell,NULL);

    /* Wait for the fibonacci thread to complete */
    pthread_join(tid1,NULL);

    /* Lastly, kill the interaction thread */
    pthread_kill(tid2, SIGKILL);

    /* exit program */
    return 0;

}
