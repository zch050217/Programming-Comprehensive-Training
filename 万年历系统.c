#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int year, month, day;

int d[2][13] = {{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31} };
int LeapYear[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
int CommonYear[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
char weekday[7][10] = { "����һ","���ڶ�","������","������","������","������","������" };

int caculateWeekDay(int year, int month, int day);
int festival(int year1, int month1, int day1, int iWeek);

// ���˵�
void MainMenu()
{
	system("cls");
	printf("������ϵͳ\n");
	printf("1.����ת��\n");
	printf("2.N�������\n");
	printf("3.��ǰ����\n");
	printf("4.��ڼ���\n");
	printf("5.�ж�ƽ��\n");
	printf("6.�˳�ϵͳ\n");
	for (int i = 0; i < 7; i++)
		printf("\t%s", weekday[i]);
	printf("\n");
}

// ƽ�����жϣ�����ֵΪ1��Ϊ���꣬����ֵΪ0��Ϊƽ��
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

// ��������� year �� 1900���ж�����
int day_sum(int year, int month, int day, int LeapYear[], int CommonYear[])
{
	// 1900 1 1 ������һ
	int sum = 0;
	for (int i = 1900; i <= year + 1; i++)
	{
		int flag = leap(year);// �ж�ƽ����
		if (flag == 1)
		{
			sum += 366;
		}
		else
		{
			sum += 365;
		}
	}
	// �����·ݵ�����
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

// ��ӡ����
void print(int sum, int year, int month)
{
	int result, temp, i;
	result = sum % 7;// ����ǰ����������

	for (i = 0; i < result; i++)
	{
		printf("\t");
	}
	temp = 7 - result;// �ӵڼ���ʼ��ӡ1��
	if (leap(year) == 1)
	{
		for (i = 1; i <= LeapYear[month - 1]; i++)// ��ӡ31��
		{
			printf("\t%d", i);
			if (i == temp || (i - temp) % 7 == 0)
				printf("\n");
		}
		printf("\n");
	}
	else
	{
		for (i = 1; i <= CommonYear[month - 1]; i++)// ��ӡ30��
		{
			printf("\t%d", i);
			if (i == temp || (i - temp) % 7 == 0)
				printf("\n");
		}
		printf("\n");
	}
}

// �ж����ڼ�
int caculateWeekDay(int year, int month, int day)
{
	int iWeek;// ��ķ����ɭ���㹫ʽW= (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7
	if (month == 1 || month == 2) 
	{
		// 1�º�2�¿�����һ��13�º�14��
		month += 12;
		year--;
	}
	return iWeek = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
}

// ����ת��
void week_day()
{
	system("cls");
	int year1, month1, day1, iWeek;
	printf("��������Ҫת���������գ�");
	scanf("%d %d %d", &year1, &month1, &day1);
	iWeek = caculateWeekDay(year1, month1, day1);
	switch (iWeek)//iWeek��÷���ֵ
	{
	case 0: printf("%4d��%2d��%2d��������һ\n", year1, month1, day1); break;
	case 1: printf("%4d��%2d��%2d�������ڶ�\n", year1, month1, day1); break;
	case 2: printf("%4d��%2d��%2d����������\n", year1, month1, day1); break;
	case 3: printf("%4d��%2d��%2d����������\n", year1, month1, day1); break;
	case 4: printf("%4d��%2d��%2d����������\n", year1, month1, day1); break;
	case 5: printf("%4d��%2d��%2d����������\n", year1, month1, day1); break;
	case 6: printf("%4d��%2d��%2d����������\n", year1, month1, day1); break;
	}
}

// N�������
void ndays()
{
	system("cls");
	int year1 = year, month1 = month, day1 = day, n, k;
	printf("������������");
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
	printf("N���Ϊ��%04d��%02d��%02d��\n", year1, month1, day1);
}

// ��ǰ����
void time_now()
{
	system("cls");
	printf("������%4d��%2d��%2d�գ�\n", year, month, day);
}

// ��ڼ���
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
	printf("������Ҫ��ѯ�����ڣ�");
	scanf("%d %d %d", &year1, &month1, &day1);
	iWeek = caculateWeekDay(year1, month1, day1);
	if (festival(year1, month1, day1, iWeek))
		printf("%4d��%2d��%2d���ǽڼ��գ�\n", year1, month1, day1);
	else
		printf("%4d��%2d��%2d�ղ��ǽڼ��գ�\n", year1, month1, day1);
}

// �ж�ƽ��Ľ�������
void leapORcommon()
{
	system("cls");
	int year1;
	printf("������Ҫ�жϵ���ݣ�");
	scanf("%d", &year1);
	if (leap(year1) == 1)
		printf("%dΪ���꣡\n", year1);
	else
		printf("%dΪƽ�꣡\n", year1);
}

// �˳�������ϵͳ
void ExitSys()
{
	printf("�������˳�\n");
	exit(0);// ��������
}

int main()
{
	int choice = 0;
	printf("�����뵱ǰ���ڣ��� �� �գ���");
	scanf("%d %d %d", &year, &month, &day);

	while (TRUE)
	{
		MainMenu();
		int sum = day_sum(year, month, day, LeapYear, CommonYear);
		print(sum, year, month);

		printf("��ѡ����Ҫʵ�ֵĹ��ܣ����֣���");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:// ����ת��
			week_day();
			break;
		case 2:// N�������
			ndays();
			break;
		case 3:// ��ǰ����
			time_now();
			break;
		case 4:// ��ڼ���
			fest();
			break;
		case 5:// �ж�ƽ��
			leapORcommon();
			break;
		case 6:// �˳�ϵͳ
			ExitSys();
			break;
		}
		printf("�Ƿ���Ҫ������������Yes��1 / No��0)��");
		scanf("%d", &choice);
		if (choice == 0)
		{
			break;
		}
	}
	ExitSys();
	return 0;
}