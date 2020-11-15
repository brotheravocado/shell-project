/* avoshell.c */
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#define BUF_SIZE 256
char pwd[BUF_SIZE];
int background = 0;
int is_pipe = 0;

int main()
{
	char buf[256];
	char *argv[50];
	int narg;
	pid_t pid;

    signal_sigint();
	signal_sigtstp();
    
	while (1) {
		getcwd(pwd,BUF_SIZE);
		printf("%s$ ", pwd);
		gets(buf);
		narg = getargs(buf, argv);
	    if(strcmp("exit", argv[0]) == 0){
      		exit(1);
    	}
		pid = fork();
		if (pid == 0){
			redir_in(argv);
			redir_out(argv);
			if (!background){
				if (execvp(argv[0], argv) == -1)
					printf("\n");
			}
			else{
				execvp(argv[0], argv);	
			}
			exit(1);
			}
		else if (pid > 0){
			if(!background){
				pid = wait(&status);
			}
		}
		else
			perror("fork failed");
		}
}

int getargs(char *cmd, char **argv)
{
	int i;
	int fd;
	int narg = 0;
	while (*cmd) {
		if (*cmd == ' ' || *cmd == '\t'|| *cmd == '&'){
			*cmd++ = '\0';
	 
		if(*cmd == '&'){ // background
			background = 1;
		}
		}
	
		else {
			argv[narg++] = cmd++;
				while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
					cmd++;
		}

	}
	
	for (int i=0; i <narg; i++){
		if(strcmp("|", argv[i]) == 0){
      		is_pipe = 1;
			  break;
    	}
	}
			if (is_pipe){
				Do_pipe(cmd);
				is_pipe = 0;
			}

	
		if(strcmp("cd", argv[0]) == 0){
      		cmd_cd(narg,argv);
    	}
		
	argv[narg] = NULL;
	return narg;
}





