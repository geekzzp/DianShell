# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define BUFFER_SIZE 16

static char buffer[BUFFER_SIZE+1] = {0};

static void sigint_handler(int signum) {
    write(1, buffer, BUFFER_SIZE);
    write(1, " get sigint\n", 12);
    raise(signum);
    signal(signum, sigint_handler);
}

static void sigcont_handler(int signum) {
    write(1, buffer, BUFFER_SIZE);
    write(1, " get sigcont\n", 13);
    raise(signum);
    signal(signum, sigcont_handler);
}

static void sigtstp_handler(int signum) {
    write(1, buffer, BUFFER_SIZE);
    write(1, " get sigtstp\n", 13);
    raise(signum);
    signal(signum, sigtstp_handler);
}

int main() {
    int pid = getpid();
    sprintf(buffer, "process %8d", pid);

    signal(SIGINT, sigint_handler);
    signal(SIGCONT, sigcont_handler);
    signal(SIGTSTP, sigtstp_handler);
    while(1);
    exit(0);
}