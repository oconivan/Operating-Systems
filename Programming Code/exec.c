#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
  pid_t firstPid, secondPid;

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
	firstPid = fork();
	if(firstPid == 0)
	{
		execlp("echo", "echo", "Hello", NULL);
	}
	else
	{
		/* this is the first child process, run "ls -l" */
		execlp("ls","ls","-l", NULL);
	}
  }
  else
  {
	/* this is the parent process, create another child process */
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
	  execlp("cat","cat","forkExample.c", NULL);
    }
    else
    {
    	/* this is the parent, wait for the children to exit */
      	waitpid(firstPid,NULL,0);	/* don't read exit code */
    	waitpid(secondPid,NULL,0);	/* don't read exit code */
    }
  }
  
  printf("Parent process exiting\n");

  return 0; /* this will invoke an exit() system call */
}
