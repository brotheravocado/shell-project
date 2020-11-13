/* simplesh.c */
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
	char buf[256];
	char *argv[50];
	int narg;

	pid_t pid;

	while (1) {
		printf("shell> ");
		gets(buf);
		narg = getargs(buf, argv);

		pid = fork();
		if (pid == 0){
			redir_in(argv);
			redir_out(argv);

			execvp(argv[0], argv);}
		else if (pid > 0)
			wait((int *) 0);
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
		if (*cmd == ' ' || *cmd == '\t')
			*cmd++ = '\0';
		

		else {
			argv[narg++] = cmd++;
				while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
					cmd++;
		}
		
	}
	
	argv[narg] = NULL;
	return narg;
}

/*int redir_out(char **cmdvector){
	int i;
	int fd;
	for(i=0;cmdvector[i]!=NULL;i++){
		if(!strcmp(cmdvector[i],">")){
			break;
		}
	}
	if(cmdvector[i]){
		if(!cmdvector[i+1]){return -1;}
		else{
			if((fd=open(cmdvector[i+1], O_RDWR|O_CREAT,0644))==-1){
			perror(cmdvector[i+1]);
			return -1;
			}
		}	
		dup2(fd,1);
		close(fd);
		for(i=i;cmdvector[i]!=NULL;i++){
			cmdvector[i]=cmdvector[i+2];
		}
		cmdvector[i]=NULL;
	}
	return 0;
}

int redir_in(char **cmdvector){
	int i;
	int fd;
	for(i=0;cmdvector[i]!=NULL;i++){
		if(!strcmp(cmdvector[i],"<")){
			break;
		}
	}
	if(cmdvector[i]){
		if(!cmdvector[i+1]){return -1;}
		else{
			if((fd=open(cmdvector[i+1], O_RDONLY))==-1){
			perror(cmdvector[i+1]);
			return -1;
			}
		}	
		dup2(fd,0);
		close(fd);
		for(i=i;cmdvector[i]!=NULL;i++){
			cmdvector[i]=cmdvector[i+2];
		}
		cmdvector[i]=NULL;
	}
	return 0;
}

*/






