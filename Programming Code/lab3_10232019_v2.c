//
// Lab 3
// Author: Ivan Ocon
// Date: 10/23/2019
//

#include <stdio.h>			// Standard I/O library
#include <unistd.h>			// UNIX system call library
#include <stdlib.h>			// Standard library: atol()
#include <signal.h>         // Signal handler library
#include <pthread.h>		// pthreads library
#include <string.h>
//#define THREAD 100


long double * catalanArray = NULL;
pthread_t * threadArray = NULL;
//pthread_t tid1, tid2, tid3, tid4;
//pthread_t threadArray[THREAD];
pthread_attr_t attr;
long double c=1;
//long int count = 1;
long int previous;
long int catalan_numbers;
long int thread_numbers;
int p;

void *catalan(void *n)
{
    FILE *catalanFile;
    char str[50];
	sprintf(str, "Catalan_%d.dat", p);
		
	catalanFile = fopen(str,"wb");

	int i;
		
	printf("This is thread: %d\n", p);
	 
    for(i=previous;i< (long int)n;i+=thread_numbers)
    {
        c=(2*(2*i-1)*c)/(i+1);
	    fprintf(catalanFile, "%lu = %Lf\n", i, c);
		/* Call the catalan numbers to print out in the screen*/
		catalanArray[i] = c; 
		printf("%d = %Lf\n",i, c);
    }
	    fclose(catalanFile);
		pthread_exit(0);
}


int main(int argc, char **argv)
{
	pid_t firstPid;
	int how_many_numbers_per_thread;
	int how_many_numbers_per_remainder;
	catalan_numbers = atol(argv[1]);
	thread_numbers = atol(argv[2]);
	double test;
	
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
		previous = p;
		//count = count + (long int) how_many_numbers_per_thread;
		
		pthread_create(&threadArray[p],&attr,catalan,(void *)catalan_numbers));
		//pthread_join(threadArray[p],NULL);
		
	}
	
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
	
	// Open the files to be merged 
   FILE *fp1 = fopen("Catalan_1.dat", "rb"); 
   FILE *fp2 = fopen("Catalan_2.dat", "rb"); 
   FILE *fp3 = fopen("Catalan_3.dat", "rb"); 
   FILE *fp4 = fopen("Catalan_4.dat", "rb"); 
  
  
   // Open file to store the result 
   FILE *fp5 = fopen("Concatenation.dat", "wb"); 
   char ch; 
   //char *ch[20]; 
  
   if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL) 
   { 
         puts("Could not open files"); 
         exit(0); 
   } 
  
   // Copy contents of first file to file5.txt 
   while ((ch = fgetc(fp1)) != EOF) 
      fputc(ch, fp5);  
      ch = fgetc(fp1);
      //printf("%c",ch);	  
      //fprintf(fp5,"%Lf",&fp1);
  
   // Copy contents of second file to file5.txt 
   while ((ch = fgetc(fp2)) != EOF) 
      fputc(ch, fp5); 
      ch = fgetc(fp2);
      //fprintf(fp5,"%Lf",&fp2);
    
     // Copy contents of third file to file5.txt 
   while ((ch = fgetc(fp3)) != EOF) 
      fputc(ch, fp5);
      ch = fgetc(fp3);  
      //fprintf(fp5,"%Lf",&fp3);
    
     // Copy contents of fourth file to file5.txt 
   while ((ch = fgetc(fp4)) != EOF) 
      fputc(ch, fp5); 
      ch = fgetc(fp4);
      //fprintf(fp5,"%Lf",&fp4);
   
  
   printf("Concatenatenated files done\n"); 
  
   fclose(fp1); 
   fclose(fp2); 
   fclose(fp3);
   fclose(fp4);
   fclose(fp5);
	
	/*
	int i=1;
	for(i=1; i<=catalan_numbers; i++)
	{
		printf("%d = %Lf\n",i, catalanArray[i]);
	}*/
	
    /* exit program */
    return 0;

}
