////////////////////////////////////////////
////  Team:Monica Heim
////	Machine: Linux-18
////	Programming Assignment 2
////	CSCE 321 - Operating Systems
////	10/7/19
////	Fall 2019
////	C. Lauter
////////////////////////////////////////////

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/uio.h>
#include <stdlib.h>
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

/*
  Program: pipeobserver
  Description: This program starts by checking if the first argument
    it receives is a filename to open a corresponding file for write
    access. It then parses its own arguments, separating them into a
    first and second executable's name with corresponding arguments.
  Execution: This program calls pipe to obtain a new process pipe. It
    continues by creating a first and second child processes of itself.
    The children then replaces themselves by a process corresponding
    to the first and second executables to run and then passes on the
    appropriate arguments.
    
*/

char *first_executable[8192];
char *second_executable[8192];

int error = 0;
char open_bracket = '[';
char close_bracket = ']';
char *cbracket = &close_bracket;
char *obracket = &open_bracket;

int args_size_total(int start, int finish, int limit)
{
  if(finish - start < limit)
    {
      return 0;
    }
  else
    {return 1;
    }
}

int copy_elements(char *ptr[],char **argv, int start, int end)
{
	int xelement = 0;

	for(int i = start; i < end; i++)
	{
		if(*argv[i] == *cbracket || *argv[i] == *obracket)
		{
			//Nothing
		}
		else
		{
			ptr[xelement] = argv[i];
			xelement++;
		}
	}
	return xelement;
}

void compose(char a[])
{
	int length = 0;
	while(a[length] != '\0')
	{
		length++;
	}
	write(1, a, length);
}

void implement(int argc, char **argv)
{
	int i = 0;
  int error = 0;
	int finilizing_a = 0;
	int midpoint = 0;
	int finilizing_b = 0 ;

  for(i=2;i<argc;i++)
	{
	   if( (*argv[2] == *obracket) && (*argv[argc-1] == *cbracket))
	   {
	      if((*argv[i] == *cbracket) && (i+1<argc) && (*argv[i+1] == *obracket))
	      {
	        midpoint = i;
	      }
	      else
	      {
		      //	error = 1;
	      }
	    }
	    else
	    {
	      error = 1;
				break;
	    }
	 }

	if(error == 1)
  {
    compose("unsupported argumets.\n");
    compose(" EX: filename [ first_executable ] [ second_executable ] \n");
		error= 1;
		exit(1);
  }
	else
  {
    int pars_one =  args_size_total(2, midpoint+1, 8192);
    int pars_two = args_size_total(midpoint+1, midpoint-1, 8192);
    if (pars_one == 1 || pars_two == 1)
    {
      compose("The number of arguments passed the limit of 8192 arguments. Pelase TRY AGAIN!!!!!!!! \n");
			error = 1;
			exit(1);
    }
    else
    {
    }
    finilizing_a = copy_elements(first_executable,argv,2, midpoint+1 );
    finilizing_b = copy_elements(second_executable,argv, midpoint+1, argc);
  }
}
void regpipe(char **argv)
{
  int counter;
  int in, out;
  int fd;
  int pipefds[2];
  int closed;
  int executed;
  int dupped;
  int i; 
  int x = 0;

  if(pipe(pipefds) != 0)
  {
  	perror(argv[0]);
  }
  in = pipefds[0];
  out = open(argv[1], O_WRONLY|O_CREAT, S_IRWXU);
	if(out == -1)
	{
		compose("error opening and creating the filename. Please enter a valid input\n");
		exit(1);
	}

  if(fork() == 0)
  {
    closed = close(in);
    if(closed != -1)
    {
    	if(dupped != -1)
    	{
         dup2(out, STDOUT_FILENO);
         if( executed != -1)
         {
           execvp(first_executable[0], first_executable);
         }
         else
         {
        	 	compose("error while closing child 1.\n");
        		exit(1);
         }
      }
    	else
    	{
    		 compose("error with child 1.\n");
    		 exit(1);
    	}
    }
    else
    {
   		 compose("not able to produce executable of child 1.\n");
  		 exit(1);
     }
   }

  if(fork() == 0)
  {
   // printf()'child 2'
  	closed = close(out);

  	if(closed != -1)
  	{
  		if(dupped != -1)
  		{
  	     dupped = dup2(in, STDIN_FILENO);

      	if(fork()==0)
      	{
      		closed = close(in);
     // printf("fist grandchild")
      		if(closed != -1)
      		{
		         dupped = dup2(out, STDOUT_FILENO);
		      }
  	    }

      	if(fork() == 0)
      	{
      		closed = close(out);
      //printf("second grandchild")
      		if(closed != -1)
      		{
        		dupped = dup2(in, STDIN_FILENO);
        		if(dupped != -1)
        		{
      		      executed = execvp(second_executable[0],second_executable);
    		    }
      		}
      	}
	    }
    }
  }
//printf("parent"
  close(in);
  close(out);
  wait(NULL);
  counter;
}

int main(int argc, char **argv)
{
  int i = 0;
  implement(argc, argv);
	if(error == 1)
	{

	}
	else
  {
    regpipe(argv);
  }

  return 0;
}
