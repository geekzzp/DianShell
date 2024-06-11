# ifndef LS_H
# define LS_H
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define MAX_SIZE 255
#define MAX_PATHLEN 256

void listDir(char buf[], int flag);
void listFile(char buf[], struct dirent *entry, int flag);
void listdrf(char buf[], char **argv);
# endif