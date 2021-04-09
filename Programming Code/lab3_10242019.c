//
// Lab 3
// Author: Ivan Ocon
// Date: 10/24/2019
//

#include <stdio.h>			// Standard I/O library
#include <unistd.h>			// UNIX system call library
#include <stdlib.h>			// Standard library: atol()
#include <signal.h>         // Signal handler library
#include <pthread.h>		// pthreads library
#include <string.h>


long double * catalanArray = NULL;
pthread_t * threadArray = NULL;
pthread_attr_t attr;


long int catalan_numbers;
long int thread_numbers;


void *catalan(void *n)
{
	long int *iPointer = (long int *) n;
	long int i = *iPointer;
	long int loop;
	long double c=1;
    FILE *catalanFile;
    char str[50];
	sprintf(str, "Catalan_%d.dat", i);
		
	catalanFile = fopen(str,"wb");

	
		
	printf("This is thread: %d\n", i);
	
    /*traverse the Catalan numbers indexing by numbers of threads */	
    for(loop=i;loop<=catalan_numbers;loop+=thread_numbers)
    {
        c=(2*(2*loop-1)*c)/(loop+1);
	    fprintf(catalanFile, "%lu = %Lf\n", loop, c);
		catalanArray[loop] = c; 
		printf("%d = %Lf\n",loop, c);
    }
	    fclose(catalanFile);
		pthread_exit(0);
}


int main(int argc, char **argv)
{
	int p;
	pid_t firstPid;
	int how_many_numbers_per_thread;
	int how_many_numbers_per_remainder;
	catalan_numbers = atol(argv[1]);
	thread_numbers = atol(argv[2]);
	double test;
	long int previous[thread_numbers];
	
	/* Using an array to dynamically-allocate the user's input*/
	catalanArray = malloc(catalan_numbers * sizeof(long double));
	threadArray = malloc(thread_numbers * sizeof(pthread_t));
	
    if(argc < 1)
    {
        printf("Usage: pthreadExample num\n");
        return -1;
    }

    /* Set pthread attributes to defaults */
    pthread_attr_init(&attr);
	how_many_numbers_per_thread = catalan_numbers / thread_numbers;
	how_many_numbers_per_remainder = catalan_numbers % thread_numbers;

	
    /* Setup a thread to compute the Catalan numbers */
	for (p=1; p <= thread_numbers; p++)
	{
		previous[p] = p;
		//count = count + (long int) how_many_numbers_per_thread;
		
		pthread_create(&threadArray[p],&attr,catalan,&previous[p]);
		//pthread_join(threadArray[p],NULL);
		
	}
	
	/* Correct thread creation/coordination */
	for (p=1; p <= thread_numbers; p++)
	{
		pthread_join(threadArray[p],NULL);		
	}
	
	/* fork a child process */
    firstPid = fork();

    if(firstPid < 0)
    {
		/* Negative process id means there was an error */
		fprintf(stderr,"Error forking a process\n");
		return -1;
	}
	else if(firstPid == 0)
	{
		execlp("echo", "echo", "concacatenation from Catalan files will be done in Concatenation.dat file:", NULL);
		exit(0);
	}
	else
	{
		wait(NULL);
		/* process id is non-zero (i.e., the child id), this is the parent process */
		printf("I am the parent1(pid=%d)\n", getpid());
	}
	

	// Open file to store the result
    FILE *fp5 = fopen("Concatenation.dat", "wb");

	int i;
	for (i=0; i < thread_numbers; i++)
	{
		int j = i+1;
		char str[50];
		char ch;
        sprintf(str, "Catalan_%d.dat", j);
		FILE *fp = fopen(str, "rb");

		if (fp == NULL)
		{
		      puts("Could not open files");
		      exit(0);
	    }

	    while ((ch = fgetc(fp)) != EOF)
	    {
	    	fputc(ch, fp5);
	    }

	    fclose(fp);

	}
  
   printf("Concatenatenated files done\n"); 
   
   
   free(catalanArray);
   free(threadArray);

    /* exit program */
    return 0;

}
