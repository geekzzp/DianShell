#include "pwd.h"

int main(int argc, char* argv[]) {
    exit(0);
}
void cd(char *path){
    chdir(path);
}
void pwd(){
    char buf[MAX_SIZE];
	getcwd(buf, sizeof(buf));
}