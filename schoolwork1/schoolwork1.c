#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#include<time.h>

typedef struct users_info {
	char name[50];
	char pswd[20];
} users_info;

int flag_login = 0;
users_info a, b;
char login_name[50];
char login_name_wq[150];
FILE* fp2;
FILE* fp3;

int main();

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
	printf("===================================\n");
	printf("\n注册您的四则运算训练系统账户\n");
	fread(&b, sizeof(users_info), 1, fp);/*读入一个结构体字符块到b中*/
	printf("请输入您的用户名：");
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
			printf("\n该用户名已被使用，请重试。\n");
			fclose(fp);
			system("pause");
			return;
		}
	}
	printf("\n请输入密码：");
	scanf("%s", &a.pswd);
	fp = fopen("users_info.txt", "a");
	fwrite(&a, sizeof(users_info), 1, fp);

	printf("\n账号注册成功，请登录\n");
	printf("\n===================================\n");
	strcpy(login_name_wq, a.name);
	fclose(fp);
	system("pause");
	strcat(login_name_wq, ".txt");
	fp3 = fopen(login_name_wq, "w+");
	fclose(fp3);
	return;
}

char users_login() {//登录
	users_info a, b;

	FILE* fp;
	printf("===================================\n");
	printf("\t四则运算系统登录界面\n");
	fp = fopen("users_info.txt", "r");

	fread(&b, sizeof(users_info), 1, fp);
	printf("\n请输入账号：");
	scanf("%s", &a.name);
	strcpy(login_name, a.name);
	while (1) {
		if (strcmp(a.name, b.name) == 0)/*如果已经注册了*/
			break;
		else {
			if (!feof(fp))
				fread(&b, sizeof(users_info), 1, fp);
			else {
				printf("\n此账号不存在，请注册或重新登录！\n");
				fclose(fp);
				system("pause");
				return;
			}
		}
	}
	printf("\n请输入密码：");
	scanf("%s", &a.pswd);
	int i = 3;
	while (1) {
		if (strcmp(a.pswd, b.pswd) == 0) {
			fclose(fp);
			printf("\n\n登录成功！即将进入训练系统\n");
			printf("\n===================================\n");
			flag_login = 1;
			Sleep(2000);
			return (login_name);
		}
		else {
			printf("\n密码不正确，请重新输入，您还有%d次机会\n", i);
			printf("请输入密码：");
			i--;
			scanf("%s", &a.pswd);
		}
		if (i == 0) {
			printf("您已输错超过3次，即将返回主界面\n");
			printf("\n===================================\n");
			Sleep(1000);
			system("cls");
			break;
		}
	}
}

/*
	功能：进行一道题的测试过程
*/
double test(int n)
{
	int ranswer = 0;			//正确答案
	int uanswer = 0;			//用户输入的答案
	int t = 0;				//临时变量
	char operation;			//运算类别
	int num1 = 0;				//操作数1
	int num2 = 0;				//操作数2

	srand(time(NULL));		//初始化随机数种子
	num1 = rand() % 10;			//取0—9之间的随机数
	num2 = rand() % 10;

	//进入程序功能，如果选择5就随机产生1-4所代表的每一种运算方式
	if (n == 5)
	{
		n = rand() % 4 + 1;
	}

	switch (n)
	{
	case 1:
		operation = '+';
		break;

	case 2:
		operation = '-';
		break;

	case 3:
		operation = '*';
		break;

	case 4:
		operation = '/';
		break;
	}

	//加入一条防止“不够减”的语句，当选择减法且num1小于num2时不够减
	//不够减的时候，用临时变量交换两个操作数
	if ((operation == '-') && (num1 < num2))
	{
		t = num1;
		num1 = num2;
		num2 = t;
	}

	//防止“除数为0”的程序漏洞
	//当num2被随机取值到0时，就将num2强制置为1
	//做除法时，将num1的值强制赋值给num1*num2，防止不能整除
	if (operation == '/')
	{
		if (num2 == 0)
		{
			num2 = 1;
		}
		num1 = num1 * num2;			//防止num1不能被num2整除的语句
	}

	//输出测试题本身、提示用户输入
	printf("%d%c%d= ", num1, operation, num2);
	scanf("%d", &uanswer);

	//程序计算正确结果
	switch (operation)
	{
	case '+':
		ranswer = num1 + num2;
		break;

	case '-':
		ranswer = num1 - num2;
		break;

	case '*':
		ranswer = num1 * num2;
		break;

	case '/':
		ranswer = num1 / num2;
		break;
	}
	//评判，做对返回1，做错返回0
	if (uanswer == ranswer)
	{
		printf("做对了！\n");
		return 1;
	}
	else
	{
		printf("做错了，再试一次吧！\n");
		printf("%d%c%d= ", num1, operation, num2);
		scanf("%d", &uanswer);
		if (uanswer == ranswer)
		{
			printf("做对了！\n");
			return 0.5;
		}
		else {
			printf("又做错了，正确答案是：%d\n", ranswer);
			char tmp1[256];
			memset(tmp1, 0, sizeof(tmp1));
			sprintf(tmp1, "   %d%c%d= %d , 正确答案为： %d\n", num1,operation,num2,uanswer,ranswer);
			
			fp3 = fopen(login_name_wq, "a");
			fwrite(tmp1, 1, strlen(tmp1), fp3);
			fclose(fp3);
			return 0;
		}

	}
}

void doExercise()
{
	double score = 0;		//练习得分，初始化为0
	int i = 0;			//练习题数的计数器
	printf("===================================\n");
	printf("\n欢迎使用小学生四则运算练习软件\n");
	printf("\t1、加法练习\t2、减法练习\n");
	printf("\t3、乘法练习\t4、除法练习\n");
	printf("\t5、综合练习\t0、退出系统\n");
	printf("请输入你的选择（0--5）：\n");
	printf("\n===================================\n");
	int op1,num;
	scanf("%d", &op1);
	printf("输入本次训练题数： ");
	scanf("%d", &num);
	for (i = 1; i <= num; i++)
	{
		score = score + test(op1);		//间接递归调用test(n)
	}
	printf("本次练习%d道题，你做对了%.1lf道\n", num,score);
	double final_score;
	final_score = (score / (double)num) * 100;
	printf("本次得分 %.0lf 分 ", final_score);
	if (final_score > 90) printf(" , Smart!\n");
	else if((final_score>80)&&(final_score<=90)) printf(" , Good!\n");
	else if ((final_score > 70) && (final_score <= 80)) printf(" , OK!\n");
	else if ((final_score > 60) && (final_score <= 70)) printf(" , Pass!\n");
	else  printf(" , Try again!\n");
}




int main() {
	users_create();
beginning:
	printf("=============================================\n");
	printf("\n\t      四则运算练习系统\n\n");
	printf("\t1.注	册");
	printf("\t2.登	录\n\n");
	printf("\t3.关于我们");
	printf("\t4.退出系统\n\n");
	printf("\t      请输入对应序号: \n");
	printf("\n=============================================\n");
	int option;
	scanf("%d", &option);
	switch (option) {

	case 1:system("cls"); users_register(); system("cls"); goto beginning;
	case 2:system("cls"); users_login(); system("cls");
		while (1) {
			if (flag_login == 0)
				goto beginning;
			else
				break;
		}
		
		
		
mainly:
		printf("=============================================\n");
		printf("\n\t      四则运算练习系统\n\n");
		printf("\t       当前用户：%s\n\n", login_name);
		printf("\t1.四则运算");
		printf("\t2.错题集\n\n");
		printf("\t3.退出登录");
		printf("\t4.退出系统\n\n");
		printf("\t      请输入对应序号: \n");
		printf("\n=============================================\n");
		int option1;
		scanf("%d", &option1);
		switch (option1) {
		case 1:
			system("cls");
			fp3 = fopen(login_name_wq, "a");
			char tmp2[256];
			memset(tmp2, 0, sizeof(tmp2));
			time_t timep;
			struct tm* p;
			time(&timep);
			p = gmtime(&timep);
			sprintf(tmp2, "%d年%d月%d日 %d:%d:%d\n", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
			fwrite(tmp2, 1, strlen(tmp2), fp3);
			fclose(fp3);
			doExercise();
			system("pause");
			system("cls");
			goto mainly;
		case 2:
			
			fp2 = fopen(login_name_wq, "r");
			
			while (!feof(fp2))
				putchar(fgetc(fp2));
			fclose(fp2);
			system("pause");
			system("cls");
			goto mainly;
		case 3:
			system("cls");
			goto beginning;
		case 4:
			exit(0);
		}
	case 3:
		system("cls");
		printf("==============================================\n");
		printf("\n\t      关  于  我  们\n\n");
		printf("      系统为适用于小学生的四则运算练习系统，\n");
		printf("  系统由C语言编写，可以进行100以内的四则运算\n");
		printf("  练习，每次练习可以任意指定题目数量，每题有\n");
		printf("  两次答题机会，第一次答对得满分，第二次答对\n");
		printf("  得一半的分，答错不得分。练习后可查看每次练\n");
		printf("  习的错题。\n");
		printf("\n\t   Powered by Edward_du\n");
		printf("\n\t   \t2019.4.19\n");
		printf("\n==============================================\n");
		system("pause");
		system("cls");
		goto beginning;
	case 4:exit(0);
	}
	return 0;
}
