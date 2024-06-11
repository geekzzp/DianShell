# include "login.h"

int set_disp_mode(int fd,int option)
{  
   int err;  
   struct termios term;  
   if(tcgetattr(fd,&term)==-1){  
     perror("Cannot get the attribution of the terminal");  
     return 1;  
   }  
   if(option)  
        term.c_lflag|=ECHOFLAGS;  
   else  
        term.c_lflag &=~ECHOFLAGS;  
   err=tcsetattr(fd,TCSAFLUSH,&term);  
   if(err==-1 && err==EINTR){  
        perror("Cannot set the attribution of the terminal");  
        return 1;  
   }  
   return 0;  
}
//保证文件users的存在，该文件存在时也不清空其中的数据
void create_user_file()
{
	FILE * fp;

	if ((fp = fopen("users", "r")) == NULL)	
	{
		if ((fp = fopen("users", "w+")) == NULL)
		{
			fprintf(stderr, "无法打开用户信息!\n");
			
			return;
		}
	}
	fclose(fp);

	return;
}
//显示主界面并获取用户键入的信息
char get_choice(void)
{
	char ch;

	ch =get_first();
	while(ch != 'a' && ch != 'b' && ch != 'c' && ch != 'q')
	{
		puts("请输入正确选项");
		ch =get_first();
	}

	return ch;
}
//返回键入的第一个字母字符并清空缓存区
char get_first(void)
{
    char ch = 0;

    while (!isalpha(ch = getchar()))
	{
        continue;
	}

	while (getchar() != '\n')
		continue;

    return tolower(ch);	 //返回小写值
}
//注册函数
void register_user()
{
	FILE * fp;
	user new_, old;
	char temp[SIZE];

	show_line("请开始注册您的账号!");
	
	if ((fp = fopen("users", "r")) == NULL)
	{
		fprintf(stderr, "读取用户信息失败！\n");
		
		return;
	}
	puts("请输入您的账号：");
	s_gets(new_.id, SIZE);
	while (!feof(fp))
	{
		fread(&old, sizeof(user), 1, fp);
		decipher(old.pwd);
		if (!strcmp(new_.id, old.id))
		{
			fprintf(stderr, "账号重复！\n");
			sleep(2);
			return;
		}
	}
	puts("请输入您的密码：");
	set_disp_mode(STDIN_FILENO,0);
	s_gets(new_.pwd, SIZE);
	set_disp_mode(STDIN_FILENO,1);
	puts("请再次输入您的密码：");
	set_disp_mode(STDIN_FILENO,0);
	s_gets(temp, SIZE);
	set_disp_mode(STDIN_FILENO,1);
	while (1)
	{
		if (!strcmp(new_.pwd, temp))
			break;
		puts("两次密码不一致！");
        puts("请重新输入您的密码：");
		set_disp_mode(STDIN_FILENO,0);
        s_gets(new_.pwd, SIZE);
        set_disp_mode(STDIN_FILENO,1);
		puts("请再次输入您的密码：");
        set_disp_mode(STDIN_FILENO,0);
        s_gets(temp, SIZE);
        set_disp_mode(STDIN_FILENO,1);
	}
	fp = fopen("users", "a");
	encipher(new_.pwd);
	fwrite(&new_, sizeof(user), 1, fp);
	printf("账号%s已注册成功！\n", new_.id);
	fclose(fp);
	return;
}
//登录函数
int login()
{
	FILE * fp;
	user old;
	char temp[SIZE];

	show_line("请开始登录您的账号！");

	if ((fp = fopen("users", "r")) == NULL)
	{
		fprintf(stderr, "读取用户信息失败！\n");
		return 0;
	}
	puts("请输入您的账号：");
	s_gets(temp, SIZE);
	while (!feof(fp))	//判断是否到达文件结尾
	{
		fread(&old, sizeof(user), 1, fp);
		decipher(old.pwd);
		if (!strcmp(temp, old.id))
		{
            puts("请输入您的密码：");
            set_disp_mode(STDIN_FILENO,0);
            s_gets(temp, SIZE);
            set_disp_mode(STDIN_FILENO,1);
			if (!strcmp(temp, old.pwd))
			{
				show_line("登录成功！");
				return 1;
			}
			else
			{
				puts("密码不匹配！");
				return 0;
			}
		}
	}
	printf("账号%s不存在！\n", temp);

	fclose(fp);
	return 0;
}

char * s_gets(char * st, int n)
{
	char * ret_val;
	int i = 0;

	ret_val = fgets(st, n, stdin);
	if (ret_val != NULL)
	{
		while (st[i] != '\0' && st[i] != '\n')
			i++;
		if (st[i] == '\n')
			st[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}
//加密函数
void encipher(char * original)
{
    int key = 1;

    for (int i = 0; i < strlen(original); i++)
    {
		original[i] += key;
		key=-key;
    }
	return;
}
//解密函数
void decipher(char * cipher)
{
    int key = -1;
    for (int i = 0; i < strlen(cipher); i++)
    {
        cipher[i] += key;
        key = -key;
    }

	return;
}
//展示某句话
void show_line(const char * line)
{
	printf("%s\n", line);
	return;
}

void user_menu()
{
	char choice;			//记录get_choice()返回值

	show_line("欢迎使用Dian Shell登录系统!");
//用字符串来输出是一个比较好用的技巧，来保证对齐
    printf("%-20s%-20s%-20s\n", "a. 注册账号", "b. 登录账号", "q. 退出登录");
	create_user_file();
	while ((choice = get_choice()) != 'q')
	{
        if(choice=='a') register_user();
        else if(login()==1) return;
	    printf("%-20s%-20s%-20s\n", "a. 注册账号", "b. 登录账号", "q. 退出登录");
	}
	exit(0);
}
