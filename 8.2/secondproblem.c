#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
typedef void handler_t(int);

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

/** Modified Signal function copied from csapp.c. This differs from
    the original Signal in that the option to restart system calls
    is not automatically turned on. Instead, the caller has to say whether
    or not to restart system calls. **/
handler_t *Signal(int signum, handler_t *handler,int restart)
{
    struct sigaction action, old_action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask); /* Block sigs of type being handled */
    if(restart)
      action.sa_flags = SA_RESTART;
    else
      action.sa_flags = 0;

    if (sigaction(signum, &action, &old_action) < 0)
      unix_error("Signal error");
    return (old_action.sa_handler);
}

void  ALARMhandler(int sig)
{
  signal(SIGALRM, SIG_IGN);          
  printf("\nTime's up!\n");
  exit(0);    
}

//Define tfgets
void tfgets(){
    signal(SIGALRM, ALARMhandler);
    char name[20];
    alarm(5);
    fgets(name, 20, stdin);
    printf("Hello, %s", name);
}

int main(int argc, const char * argv[])
{
    printf(" Please enter your name: ");
    tfgets();
    return 0;
} 