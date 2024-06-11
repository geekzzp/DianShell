#include<stdio.h>  
#include<limits.h>  
#include<sys/types.h>  
#include<string.h>  
#include<stdlib.h>
#include<unistd.h>
  
void err_quit(char *err) {  
    printf("%s\n",err);
    exit(-1);
}  
void task(int i, int n, int* fd1, int* fd2, int* result)
{
    pid_t pid1, pid2;
    int status;
    if ((pid1 = fork()) < 0) {  
        err_quit("fork error");  
    }
    if(pid1 == 0) {
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);
        write(fd1[1], &result, sizeof(result));
        close(fd1[1]);
        exit(0);
    }  
    if ((pid2 = fork()) < 0) {  
        err_quit("fork error");  
    }
    if(pid2 == 0) {
        close(fd2[0]);
        int value1;
        read(fd1[0], &value1, sizeof(value1));
        int value2 = value1 + *result;
        write(fd2[1], &value2, sizeof(value2));
        close(fd2[1]);
        exit(0);
    }
    close(fd1[0]);
    close(fd2[0]);
    close(fd1[1]);
    read(fd2[0], result, sizeof(int));
    printf("process_id:%d, layer:%d, method:%d\n",pid2, i, *result);
    close(fd2[0]);
}  
int main(int argc, const char* argv[])  
{
    int n = atoi(argv[1]);
    int fd1[2],fd2[2];  
    int result1=0, result2=1;
    printf("layer:1, method:1\n");
    for(int i=2;i<=n;i++)
    {
        if (pipe(fd1) < 0) {  
        err_quit("pipe error");  
        }
        if (pipe(fd2) < 0) {  
            err_quit("pipe error");  
        }
        task(i, n, fd1, fd2, &result2);
        result1=result2-result1;
        result2=result1+result2;
    }
}
