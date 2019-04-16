#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include<windows.h>

typedef struct users_info {
	char name[15];
	char pswd[20];
} users_info;

void users_create()
{
	FILE* fp;
	if ((fp = fopen("users_info.txt", "rb")) == NULL)                 /*如果此文件不存在*/
	{
		if ((fp = fopen("users_info.txt", "wb+")) == NULL)
		{
			printf("无法建立文件！\n");
			exit(0);

		}
	}
}

void users_register() {//注册
	FILE* fp;
	char t[20];
	int count = 0;
	users_info a, b;
	fp = fopen("users_info.txt", "r");
	printf("注册您的四则运算训练系统账户\n");

	fread(&b, sizeof(users_info), 1, fp);/*读入一个结构体字符块到b中*/
	printf("请输入您的用户名：\n");
	scanf("%s", &a.name);
	while (1) {
		if (strcmp(a.name, b.name) != 0) {/*如果两个用户名不一样*/
			if (!feof(fp)) {/*/如果没读到文件尾*/
				fread(&b, sizeof(users_info), 1, fp);
			}
			else
				break;
		}
		else {
			printf("该用户名已被使用，请重试。\n");
			fclose(fp);
			return;
		}
	}
	printf("请输入密码：\n");
	scanf("%s", &a.pswd);
	fp = fopen("users_info.txt", "a");
	fwrite(&a, sizeof(users_info), 1, fp);
	printf("账号注册成功，请登录\n");
	fclose(fp);
	return;
}

void users_login() {//登录
	users_info a, b;

	FILE* fp;
	printf("四则运算系统登录界面\n");
	fp = fopen("users_info.txt", "r");

	fread(&b, sizeof(users_info), 1, fp);
	printf("请输入账号\n");
	scanf("%s", &a.name);
	while (1) {
		if (strcmp(a.name, b.name) == 0)/*如果已经注册了*/
			break;
		else {
			if (!feof(fp))
				fread(&b, sizeof(users_info), 1, fp);
			else {
				printf("此账号不存在，请重新输入！\n");
				fclose(fp);
				return;
			}
		}
	}
	printf("请输入密码\n");
	scanf("%s", &a.pswd);
	int i = 3;
	while(1) {
		if (strcmp(a.pswd, b.pswd) == 0) {
			fclose(fp);
			printf("登录成功\n");
			return;
		}
		else {
			printf("密码不正确，请重新输入，您还有%d次机会\n",i);
			i--;
			scanf("%s", &a.pswd);
		}
		if (i == 0) {
			printf("您已输错超过3次，即将返回主界面\n");
			Sleep(1000);
			system("cls");
			break;
		}
			
	} 


}

int main() {
	users_create();
beginning:
	printf("四则运算练习系统\n");
	printf("1.注册\n");
	printf("2.登录\n");
	printf("6.退出系统\n");
	printf("-.请输入对应序号\n");
	int option;
	scanf("%d", &option);
	switch (option) {

	case 1:users_register(); goto beginning;
	case 2:users_login(); goto beginning;
	case 6:exit(0);
	}
	return 0;
}
