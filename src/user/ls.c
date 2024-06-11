#include "ls.h"

int main(int argc, char **argv)
{
	char buf[MAX_SIZE];
	getcwd(buf, sizeof(buf));
    if(argc==1)
	    listDir(buf, 0);
    else
    {
        listdrf(buf, argv);
    }
	return 0;
}
void listDir(char buf[], int flag) {
	
	// 列出当前目录的文件
    DIR *dir;
    struct dirent *entry;
    dir = opendir(buf);
    struct stat st;
    
    // 非法路径
	if (stat(buf, &st) < 0 || ! S_ISDIR(st.st_mode)) {
		printf("ERROR: Invalid path: %s\n", buf);
		return;
	} 
    
	// 如果打开错误则报错
    if (dir == NULL) {
		printf("ERROR: OPEN directory \"%s\": %m (ERROR %d)\n", buf, errno);
        return;
    }
	// 遍历目录文件，只打印文件，子目录和以.开头的文件不打印
    while ((entry = readdir(dir)) != NULL) {	
		// 不输出目录，且如果没有-a选项不输出以.开头的文件 
		if (entry -> d_type != 4 && (entry -> d_name[0] != '.')) 
			// 输出文件 
			listFile(buf, entry, flag);
			
		// 如果是目录，递归调用本身，进入子目录继续遍历 
		if (entry -> d_type == 4 && (entry -> d_name[0] != '.')) {
			printf("%s :\n", entry -> d_name);
			
			// 目录下的.和..不用列出（为本目录和上级目录）   
			if (strcmp(".", entry -> d_name) == 0 || strcmp("..", entry -> d_name) == 0)
				continue;
				
			char pathname[MAX_PATHLEN];
			if (flag != 0) {
				snprintf(pathname, (size_t)MAX_PATHLEN+1, "%s/%s", buf, entry -> d_name);
				listDir(pathname, 1);
			}
			else {
				listDir(entry -> d_name, 1);
			}
		}
			
    }
	printf("\n");
    closedir(dir);
}

void listdrf(char buf[], char **argv){
    DIR *dir;
    struct dirent *entry;
    dir = opendir(buf);
    struct stat st;
    
    // 非法路径
	if (stat(buf, &st) < 0 || ! S_ISDIR(st.st_mode)) {
		printf("ERROR: Invalid path: %s\n", buf);
		return;
	} 
    
	// 如果打开错误则报错
    if (dir == NULL) {
		printf("ERROR: OPEN directory \"%s\": %m (ERROR %d)\n", buf, errno);
        return;
    }
	// 遍历目录文件，只打印文件，子目录和以.开头的文件不打印
    while ((entry = readdir(dir)) != NULL) {
			
		// 如果是目录，递归调用本身，进入子目录继续遍历 
		if (entry -> d_type == 4 && (entry -> d_name[0] != '.') && (!strcmp(entry -> d_name, argv[1]))) {
			printf("%s :\n", entry -> d_name);
			
			// 目录下的.和..不用列出（为本目录和上级目录）   
			if (strcmp(".", entry -> d_name) == 0 || strcmp("..", entry -> d_name) == 0)
				continue;
			listDir(entry -> d_name, 1);
		}
			
    }
	printf("\n");
    closedir(dir);

}

// 如果要查看的是文件，那么直接输出文件信息 
// 函数参数：buf：文件名，st：文件的stat结构体 
void listFile(char buf[], struct dirent *entry, int flag) {
	
	// 为获取文件大小，要得到stat结构体，所以这里使用snprintf获得文件的绝对路径
	char pathname[MAX_PATHLEN];
	snprintf(pathname, (size_t)MAX_PATHLEN+1, "%s/%s", buf, entry -> d_name);
	struct stat temp;
	stat(pathname, &temp);
	
	// 非本目录下的文件或者参数中带有路径，要输出路径+文件名
	if (flag == 1)
		printf("%s \n", entry -> d_name);
	// 本目录下的文件，只需要输出文件名
	else 
		printf("%s \n", entry -> d_name);
	
}