#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "header.h"
void signal_sigint();
void signal_sigtstp();
void signal_handler();
void sigstp_handler();
void signal_sigint(){
    struct sigaction act;
    act.sa_handler = signal_handler;
    sigfillset(&(act.sa_mask));
    sigaction(SIGINT,&act,NULL);
}
void signal_sigtstp(){
    struct sigaction act2;
    act2.sa_handler = sigstp_handler;
    sigfillset(&(act2.sa_mask));
    sigaction(SIGTSTP,&act2,NULL);
}
    void signal_handler(int signo){
      if (pid != 0){
            printf("\nSIGINT handler -Ctrl+c\n");
            pid_t ppid = getppid();
            kill (ppid, SIGINT);
      }
    }
     void sigstp_handler(int signo){
         if (pid != 0){
            printf("\nSIGQUIT handler -Ctrl+z\nQuit (Core dump)\n");
            pid_t ppid = getppid();
            kill (ppid, SIGQUIT);
         }
    }
    