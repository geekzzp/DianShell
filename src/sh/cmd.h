# ifndef CMD_H
# define CMD_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define MAX_CMD_LEN 1024
void copy_string(char str1[],char str2[]);
int scan_cmd(char* cmd_buf);
int exec_cmd(char* cmd_buf);
struct table
{
    int tot;
    char name[20][20];
    char val[20][20];
};
struct table envt;

# endif