#include <sys/types.h>
#include <sys/wait.h> //for wait() function
#include <unistd.h> //UNIX system call library: fork(), getpid(), etc.
#include <signal.h> //signal handler library
#include <stdio.h> //standard I/O library

int main()
{
	pid_t myPid;
	int mySig;
	static int i=5;
	sigset_t sigSet;
	int childExitStatus;
	
	/* fork a child process */
	myPid = fork();
	
	if(myPid < 0)
	{
		/*Negative process id means there was an error */
		fprintf(stderr,"Error forking a process\n");
		return -1;
	}
	else if(myPid == 0)
	{
		/* process id is 0, this is the child process */
		printf("\nI am the child, pid:%d, my parent is pid:%d\n", getpid(),getppid());
		
		printf("child: i=%d\n", i);
		i = 200;
		printf("child: i=%d\n", i);
		
		/* Child will wait for the terminate signal */
		printf("Child (%d) waiting for a terminate signal ...",getpid());
		fflush(NULL);
		sigemptyset(&sigSet);
		sigaddset(&sigSet,SIGTERM);
		sigwait(&sigSet,&mySig);
		
		/*process termination message */
		printf("\nchild process: %d, terminating\n", getpid());
		
		return 0;	
	}
    else
	{
		/* process id is non-zero (i.e., the child id), this is the parent process */
		printf("\nI am the parent(pid=%d), child is pid:%d\n", getpid(), myPid);
		/* Parent will wait for child to terminate */
		printf("parent: i=%d\n", i);
		/* process termination message */
		printf("\nparent: The child (%d) has terminated by signal %d, parent process: %d, is now terminating\n",
		         myPid,WTERMSIG(childExitStatus),getpid());
				 
				 return 0;
	}

}
