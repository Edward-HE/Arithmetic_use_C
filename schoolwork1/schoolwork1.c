#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct users_info {
	char name[15];
	char pswd[20];
} users_info;

void users_register() {
	FILE* fp;
	char t[20];
	int count = 0;
	users_info a, b;
	fp = fopen("users_info.txt", "w+");
	printf("\t\t\t\t注册您的四则运算训练系统账户\n");

	fread(&b, sizeof(users_info), 1, fp);
	printf("\t\t\t\t请输入您的用户名：\n");
	scanf("\t\t\t\t%s", &a.name);
	while (1) {
		if (strcmp(a.name, b.name) != 0) {
			if (!feof(fp)) {
				fread(&b, sizeof(users_info), 1, fp);
			}
			else
				break;
		}
		else {
			printf("\t\t\t\t该用户名已被使用，请重试。\n");
			fclose(fp);
			return;
		}
	}
	printf("\t\t\t\t请输入密码：\n");

}

int main() {
	users_register();
	return 0;
}
