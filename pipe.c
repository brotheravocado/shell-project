#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
int Do_pipe(char **cmdvector); // cmdvector cmd
int Do_pipe(char **cmdvector){
	int i;
	int k=0;
	pid_t pid1, pid2;
	int fd[2];
	char *cmdvectorPipe1;		
	char *cmdvectorPipe2;
	
	for(i=0;cmdvector[i]!=NULL;i++){
		if(!strcmp(cmdvector[i], "|")){
			cmdvectorPipe1[i]=NULL;
			break;
		}
		cmdvectorPipe1[i]=cmdvector[i];
	}
	
	for (i=i+1; cmdvector[i]!=NULL;i++){
		cmdvectorPipe2[k]=cmdvector[i];
		k++;
	}
	pipe(fd);
	
	pid1=fork();
	switch(pid1) 
	{
		case -1: perror("fork error");
				break;
		case 0:
				redir_in(cmdvectorPipe1);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
				execvp(cmdvectorPipe1[0], cmdvectorPipe1);
				exit(1);
	
	}

	pid2=fork();
	switch(pid2)
	{
		case -1: perror("fork");
				break;
		case 0:

				redir_out(cmdvectorPipe2);
				dup2(fd[0], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
					execvp(cmdvectorPipe2[0], cmdvectorPipe2);
				exit(1);
	
	}

}
