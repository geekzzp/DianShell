# include "cmd.h"
void copy_string(char str1[],char str2[]) {
	int i = 1;
	while(str2[i] != '\0') {
		str1[i-1] = str2[i];
		i++;
	}
	str1[i-1] = '\0';
}
void copy_without(char str1[],char str2[]) {
	int i = 0;
	while(str2[i] != '\0'&&str2[i] != '\n') {
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}
int scan_cmd(char* cmd_buf) {
    // TODO: write code to get commands here
    fgets(cmd_buf, 255, stdin);
    return 0;
}

int exec_cmd(char* cmd_buf) {
    // TODO: write code to execute commands here
    char ttt[100];
    copy_without(ttt, cmd_buf);
    int tot=0;
    char ins[30][30];
    char *tt = strtok(ttt, ";");
    while(tt!=NULL)
    {
        ++tot;
        strcpy(ins[tot], tt);
        tt = strtok(NULL, ";");
    }
    for(int j=1;j<=tot;j++)
    {
        char *token;
        char t[20];
        token = strtok(ins[j], " ");

        if(token[0]=='$')
        {
            copy_string(t,token);
            for(int i=1;i<=envt.tot;i++)
                if(!strcmp(envt.name[i], t))
                    token=envt.val[i];
        }

        if(!strcmp("hello", token))
        {
            token = strtok(NULL, " ");
            pid_t pid;
            int status;
            if((pid=fork()) < 0)
            {
                printf("vfork error!\n");
                exit(1);
            }
            else if(pid==0)
            {
                printf("Child process PID: %d.\n", getpid());
                char *argv[ ]={"./helloworld", token, NULL};
                // char *envp[ ]={"PATH=/bin", NULL};
                char *envp[ ]={NULL};
                int return_num = execve("./bin/helloworld", argv, envp);
                if(return_num < 0)
                {
                    printf("subprocess error");
                    exit(1);
                }
                // 子进程要么从 ls 命令中退出，要么从上面的 exit(1) 语句退出
                // 所以代码的执行路径永远也走不到这里，下面的 printf 语句不会被执行
                printf("You should never see this message.");
            }
            else
            {
                wait(&status);
        
                if (WIFEXITED(status)) {
                    int exit_status = WEXITSTATUS(status);
                    printf("Child process exited with status: %d\n", exit_status);
                }
                printf("Parent process PID: %d.\n", getpid());
            }
        }
        else if(!strcmp("ls", token))
        {
            pid_t pid;
            int status;
            token = strtok(NULL, " ");
            if((pid=fork()) < 0)
            {
                printf("vfork error!\n");
                exit(1);
            }
            else if(pid==0)
            {
                char *argv[20]={"./bin/ls", NULL, NULL};
                if(token!=NULL) argv[1]=token;
                // char *envp[ ]={"PATH=/bin", NULL};
                char *envp[ ]={NULL};
                int return_num = execve("./bin/ls", argv, envp);
                if(return_num < 0)
                {
                    printf("subprocess error");
                    exit(1);
                }
                // 子进程要么从 ls 命令中退出，要么从上面的 exit(1) 语句退出
                // 所以代码的执行路径永远也走不到这里，下面的 printf 语句不会被执行
                printf("You should never see this message.");
            }
            else
            {
                wait(&status);
            }
        }
        else if(!strcmp("pwd", token))
        {
            char buf[255];
            getcwd(buf, sizeof(buf));
            printf("%s\n",buf);
        }
        else if(!strcmp("cd", token))
        {
            token = strtok(NULL, " ");
            if(token[0]=='$')
            {
                copy_string(t,token);
            }
            for(int i=1;i<=envt.tot;i++)
                if(!strcmp(envt.name[i], t))
                    token=t;
            if (chdir(token)>=0)
            {
                char buf[255];
                getcwd(buf,sizeof(buf));
                printf("Current dir is:%s\n",buf);
            }
            else
            {
                printf("Error path!\n");
            }
        }
        else if(!strcmp("set", token))
        {
            char s1[20];
            char s2[20];
            char *token1 = strtok(NULL, " ");
            strcpy(s1,token1);
            char *token2 = strtok(NULL, " ");
            strcpy(s2,token2);
            if(token1[0]=='$')
            {
                copy_string(t,token1);
                for(int i=1;i<=envt.tot;i++)
                    if(!strcmp(envt.name[i], t))
                        strcpy(s1,envt.val[i]);
            }

            if(token2[0]=='$')
            {
                copy_string(t,token2);
                for(int i=1;i<=envt.tot;i++)
                    if(!strcmp(envt.name[i], t))
                        strcpy(s2,envt.val[i]);
            }
            
            printf("%s\n", s1);
            printf("%s\n", s2);
            envt.tot++;
            strcpy(envt.name[envt.tot], s1);
            strcpy(envt.val[envt.tot], s2);
        }
        else if(!strcmp("unset", token))
        {
            char *token1 = strtok(NULL, " ");
            if(token1[0]=='$')
            {
                copy_string(t,token1);
            }
            for(int i=1;i<=envt.tot;i++)
                if(!strcmp(envt.name[i], t))
                    token1=envt.val[i];

            int pd=1;
            for(int i=1;i<=envt.tot;i++)
                if(!strcmp(envt.name[i], token1))
                {
                    memset(envt.name[i], 0x00, sizeof (char) * 20);
                    memset(envt.val[i], 0x00, sizeof (char) * 20);
                    pd=0;
                }
            if(pd==1) printf("NOT FOUND!\n");
        }
        else if(!strcmp("env", token))
        {
            char *token1 = strtok(NULL, " ");
            if(token1==NULL)
            {
                for(int i=1;i<=envt.tot;i++)
                    printf("%s=%s\n", envt.name[i], envt.val[i]);
                return 0;
            }
            if(token1[0]=='$')
            {
                copy_string(t,token1);
            }
            for(int i=1;i<=envt.tot;i++)
                if(!strcmp(envt.name[i], t))
                    token1=envt.val[i];

            int pd=1;
            for(int i=1;i<=envt.tot;i++)
                if(!strcmp(envt.name[i], token1))
                {
                    printf("%s=%s\n", envt.name[i], envt.val[i]);
                    pd=0;
                }
            if(pd==1) printf("%s=\n", token1);
        }
    }
    return 0;
}