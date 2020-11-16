#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
int redir_out(char **cmdvector);
int redir_in(char **cmdvector);
int redir_out(char **cmdvector){
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
