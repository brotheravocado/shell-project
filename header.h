#include <unistd.h>
	pid_t pid;

int status;
void fatal(char *errlog);
int redir_out(char **cmdvector);
int redir_in(char **cmdvector);
void signal_sigint();
void signal_sigtstp();
void cmd_cd(int argc,char* argv[]);
//int Do_pipe(char **cmdvector);
void pipe_launch(int narg, char **argv) ;


