#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getch.h>
#include <unistd.h>

#define COUNT_MAX 100

typedef struct Contact
{
	char name[20];
	char sex;
	char tel[12];
}Contact;

int count = 0;

Contact con[COUNT_MAX];

//	按任意按键继续
void anykey_continue(void)
{
	printf("按任意键继续...");
	//清理输入缓冲区
	stdin->_IO_read_ptr = stdin->_IO_read_end;

	getch();
}

//	打印提示信息
void show_msg(const char* msg,float sec)
{
	printf("%s",msg);
	//如果msg没有换行，需刷新输出缓冲区
	fflush(stdout);
	usleep(sec*1000000);
}

void add(void)
{
	if(COUNT_MAX <= count)
	{
		show_msg("系统正在升级,请稍后!\n",2);
		return;
	}

	int i = 0;
	while(con[i].sex) i++;

	printf("请输入姓名 性别 电话:");
	scanf("%s %c %s",con[i].name,&(con[i].sex),con[i].tel);
	count++;

	show_msg("添加联系人成功!",1.5);
}

void delete(void)
{
	char name[20] = {};
	printf("请输入要删除的联系人姓名:");
	gets(name);

	for(int i=0; i<COUNT_MAX; i++)
	{
		if(con[i].sex && 0 == strcmp(con[i].name,name))	
		{
			show_msg("删除联系人成功!",1.5);
			con[i].sex = 0;
			count--;
			return;
		}
	}
	show_msg("联系人不存在，请检查联系人姓名!",1.5);
}

void modify(void)
{
	char name[20] = {};
	printf("请输入要修改的联系人姓名:");
	gets(name);

	for(int i=0; i<COUNT_MAX; i++)
	{
		if(con[i].sex && 0 == strcmp(con[i].name,name))	
		{
			printf("请更改该联系人的姓名 性别 电话:");
			scanf("%s %c %s",con[i].name,&(con[i].sex),con[i].tel);
			show_msg("修改成功！",0.5);
			return;
		}
	}
	show_msg("联系人不存在，请检查联系人姓名!",1.5);
}

void find(void)
{
	char key[20] = {};
	printf("请输入要查询的关键字:");
	gets(key);

	for(int i=0; i<COUNT_MAX; i++)
	{
		if(con[i].sex && 
				strstr(con[i].name,key) || strstr(con[i].tel,key))
		{
			printf("%s %s %s\n",
				con[i].name,con[i].sex=='w'?"女":"男",con[i].tel);		
		}
	}
}

void show(void)
{
	for(int i=0; i<COUNT_MAX; i++)
	{
		if(con[i].sex)
		{
			printf("%s %s %s\n",
				con[i].name,con[i].sex=='w'?"女":"男",con[i].tel);	
		}
	}
	anykey_continue();
}

char menu(void)
{
	system("clear");
	puts("*****欢迎使用指针通讯录*****");
	puts("1、添加");	
	puts("2、删除");	
	puts("3、修改");	
	puts("4、查询");	
	puts("5、显示");
	puts("6、退出");
	puts("----------------------------");
	puts("请输入指令:");
	char cmd = getch();
	printf("%c\n",cmd);	//为了回显
	return cmd;
}

int main(int argc,const char* argv[])
{

	for(;;)
	{
		switch(menu())
		{
			case '1': add();	break;	
			case '2': delete();	break;	
			case '3': modify();	break;	
			case '4': find();	break;	
			case '5': show();	break;	
			case '6': return 0;
		}
	}
}
