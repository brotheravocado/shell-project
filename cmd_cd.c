#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void cmd_cd(int argc,char* argv[]){
    if(argc == 1){
        chdir(getenv("HOME"));
    }
    else if (argc == 2){
        if (chdir(argv[1]))
            printf("No direcotry\n");
    }
    else
    {
        printf("USAGE: cd [dir] \n");
    }
    
    
}