# ifndef LOGIN_H
# define LOGIN_H

// TODO: implement login here

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>
#include <termios.h>  
#include <unistd.h>  
#include <errno.h>
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
#define SIZE 50
//为了安全的输入（防止暴力输入)
int set_disp_mode(int fd,int option);
char get_choice();	
char get_first();
char * s_gets(char * st, int n);
// void secret_pwd(char * pwd);
//具体功能实现函数
void create_user_file();
void register_user();
int login();
//加密解密函数
void encipher(char * original);
void decipher(char * cipher);
//菜单函数
void show_line(const char * line);
void user_menu();

typedef struct user		//用户信息主体
{
	char id[SIZE];		//账号
	char pwd[SIZE];		//密码
}user;
# endif