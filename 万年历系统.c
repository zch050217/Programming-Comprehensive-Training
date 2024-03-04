#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int year, month, day;

int d[2][13] = {{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31} };
int LeapYear[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
int CommonYear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
char weekday[7][10] = { "星期一","星期二","星期三","星期四","星期五","星期六","星期日" };

int caculateWeekDay(int year, int month, int day);
int festival(int year1, int month1, int day1, int iWeek);

// 主菜单
void MainMenu()
{
	system("cls");
	printf("万年历系统\n");
	printf("1.日期转换\n");
	printf("2.N天后日期\n");
	printf("3.当前日期\n");
	printf("4.求节假日\n");
	printf("5.判断平闰\n");
	printf("6.退出系统\n");
	for (int i = 0; i < 7; i++)
		printf("\t%s", weekday[i]);
	printf("\n");
}

// 平闰年判断，返回值为1则为闰年，返回值为0则为平年
int leap(int year)
{
	int four, hundred, fourhundred;
	four = year % 4;
	hundred = year % 100;
	fourhundred = year % 400;

	if (four == 0 && hundred == 0 && fourhundred == 0)
	{
		return 1;
	}
	else if (four == 0 && hundred != 0 && fourhundred != 0)
	{
		return 1;
	}
	return 0;
}

// 计算输入的 year 与 1900年有多少天
int day_sum(int year, int month, int day, int LeapYear[], int CommonYear[])
{
	// 1900 1 1 ：星期一
	int sum = 0;
	for (int i = 1900; i <= year + 1; i++)
	{
		int flag = leap(year);// 判断平闰年
		if (flag == 1)
		{
			sum += 366;
		}
		else
		{
			sum += 365;
		}
	}
	// 加上月份的天数
	for (int i = 0; i < month - 1; i++)
	{
		if (leap(year) == 1)
		{
			sum += LeapYear[i];
		}
		else
		{
			sum += CommonYear[i];
		}
	}
	return sum;
}

// 打印日历
void print(int sum, int year, int month)
{
	int result, temp, i;
	result = sum % 7;// 计算前面空余的天数

	for (i = 0; i < result; i++)
	{
		printf("\t");
	}
	temp = 7 - result;// 从第几格开始打印1号
	if (leap(year) == 1)
	{
		for (i = 1; i <= LeapYear[month - 1]; i++)// 打印31天
		{
			printf("\t%d", i);
			if (i == temp || (i - temp) % 7 == 0)
				printf("\n");
		}
		printf("\n");
	}
	else
	{
		for (i = 1; i <= CommonYear[month - 1]; i++)// 打印30天
		{
			printf("\t%d", i);
			if (i == temp || (i - temp) % 7 == 0)
				printf("\n");
		}
		printf("\n");
	}
}

// 判断星期几
int caculateWeekDay(int year, int month, int day)
{
	int iWeek;// 基姆拉尔森计算公式W= (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7
	if (month == 1 || month == 2) 
	{
		// 1月和2月看作上一年13月和14月
		month += 12;
		year--;
	}
	return iWeek = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
}

// 日期转换
void week_day()
{
	system("cls");
	int year1, month1, day1, iWeek;
	printf("请输入需要转换的年月日：");
	scanf("%d %d %d", &year1, &month1, &day1);
	iWeek = caculateWeekDay(year1, month1, day1);
	switch (iWeek)//iWeek获得返回值
	{
	case 0: printf("%4d年%2d月%2d日是星期一\n", year1, month1, day1); break;
	case 1: printf("%4d年%2d月%2d日是星期二\n", year1, month1, day1); break;
	case 2: printf("%4d年%2d月%2d日是星期三\n", year1, month1, day1); break;
	case 3: printf("%4d年%2d月%2d日是星期四\n", year1, month1, day1); break;
	case 4: printf("%4d年%2d月%2d日是星期五\n", year1, month1, day1); break;
	case 5: printf("%4d年%2d月%2d日是星期六\n", year1, month1, day1); break;
	case 6: printf("%4d年%2d月%2d日是星期日\n", year1, month1, day1); break;
	}
}

// N天后日期
void ndays()
{
	system("cls");
	int year1 = year, month1 = month, day1 = day, n, k;
	printf("请输入天数：");
	scanf("%d", &n);
	day1 += n;
	k = month;
	for (; day1 > d[leap(year1)][k]; k++)
	{
		day1 -= d[leap(year1)][k];
		if (k == 12)
			k = 0, year1++;
	}
	month1 = k;
	printf("N天后为：%04d年%02d月%02d日\n", year1, month1, day1);
}

// 当前日期
void time_now()
{
	system("cls");
	printf("现在是%4d年%2d月%2d日！\n", year, month, day);
}

// 求节假日
int festival(int year1, int month1, int day1, int iWeek)
{
	if (month1 == 1)
	{
		if (day1 <= 3)
			return 1;
	}
	if (month1 == 4)
	{
		if (day1 >= 3 && day1 <= 5)
			return 1;
	}
	if (month1 == 5)
	{
		if (day1 <= 5)
			return 1;
	}
	if (month1 == 6)
	{
		if (day1 >= 3 && day1 <= 5)
			return 1;
	}
	if (month1 == 9)
	{
		if (day1 >= 10 && day1 <= 12)
			return 1;
	}
	if (month1 == 10)
	{
		if (day1 <= 7)
			return 1;
	}
	if (iWeek >= 5)
		return 1;
	return 0;
}

void fest()
{
	system("cls");
	int year1, month1, day1, iWeek;
	printf("请输入要查询的日期：");
	scanf("%d %d %d", &year1, &month1, &day1);
	iWeek = caculateWeekDay(year1, month1, day1);
	if (festival(year1, month1, day1, iWeek))
		printf("%4d年%2d月%2d日是节假日！\n", year1, month1, day1);
	else
		printf("%4d年%2d月%2d日不是节假日！\n", year1, month1, day1);
}

// 判断平闰的交互界面
void leapORcommon()
{
	system("cls");
	int year1;
	printf("请输入要判断的年份：");
	scanf("%d", &year1);
	if (leap(year1) == 1)
		printf("%d为闰年！\n", year1);
	else
		printf("%d为平年！\n", year1);
}

// 退出万年历系统
void ExitSys()
{
	printf("程序已退出\n");
	exit(0);// 结束程序
}

int main()
{
	int choice = 0;
	printf("请输入当前日期（年 月 日）：");
	scanf("%d %d %d", &year, &month, &day);

	while (TRUE)
	{
		MainMenu();
		int sum = day_sum(year, month, day, LeapYear, CommonYear);
		print(sum, year, month);

		printf("请选择想要实现的功能（数字）：");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:// 日期转换
			week_day();
			break;
		case 2:// N天后日期
			ndays();
			break;
		case 3:// 当前日期
			time_now();
			break;
		case 4:// 求节假日
			fest();
			break;
		case 5:// 判断平闰
			leapORcommon();
			break;
		case 6:// 退出系统
			ExitSys();
			break;
		}
		printf("是否需要继续操作？（Yes：1 / No：0)：");
		scanf("%d", &choice);
		if (choice == 0)
		{
			break;
		}
	}
	ExitSys();
	return 0;
}