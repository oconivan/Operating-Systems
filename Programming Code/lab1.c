#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
  pid_t firstPid, secondPid, thirdPid, fourPid;

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
		execlp("echo", "echo", "cat /proc/cpuinfo", NULL);
		exit(0);
	}
	else
	{
		wait(NULL);
		/* process id is non-zero (i.e., the child id), this is the parent process */
		printf("I am the parent1(pid=%d)\n", getpid());
	}
  
  secondPid = fork();

    if(secondPid < 0)
    {
  	  /* Negative process id means there was an error */
      fprintf(stderr,"Error forking a process\n");
      return -1;
    }
    else if(secondPid == 0)
    {
	  /* this is the second child process, run "cat forkExample.c" */
	  execlp("echo","echo","echo Hello World", NULL);
	  exit(0);
    }
    else
    {
		wait(NULL);
		/* process id is non-zero (i.e., the child id), this is the parent process */
		printf("I am the parent2(pid=%d)\n", getpid());
    }

	/* this is the parent process, create another child process */
	thirdPid = fork();
    if(thirdPid < 0)
    {
  	  /* Negative process id means there was an error */
      fprintf(stderr,"Error forking a process\n");
      return -1;
    }
    else if(thirdPid == 0)
    {
	  /* this is the second child process, run "cat forkExample.c" */
	  //execlp("echo","echo","uname -a", NULL);
	  execlp("uname","uname","-a",NULL);
	  exit(0); 
    }
    else
    {
    	wait(NULL);
		/* process id is non-zero (i.e., the child id), this is the parent process */
		printf("I am the parent3(pid=%d)\n", getpid());
    }
	
	wait(NULL);
	wait(NULL);
	wait(NULL);
	
	fourPid = fork();
    if(fourPid < 0)
    {
  	  /* Negative process id means there was an error */
      fprintf(stderr,"Error forking a process\n");
      return -1;
    }
    else if(fourPid == 0)
    {
	  /* this is the second child process, run "cat forkExample.c" */
	  //execlp("echo","echo","uname -a", NULL);
	  execlp("ls","ls","-l", NULL);
	  exit(0); 
    }
    else
    {
    	wait(NULL);
		printf("Good bye\n");
		/* process id is non-zero (i.e., the child id), this is the parent process */
		//printf("I am the parent4(pid=%d)\n", getpid());
    }
  
  //printf("Good bye\n");
  //execlp("ls","ls","-l", NULL);
  
  return 0; /* this will invoke an exit() system call */
}
