#include <stdio.h>
#include <windows.h> //system �Լ��� ����ϱ� ����
#include <time.h>

typedef struct { //�޷��� ������ �Է��� ����ü ����
	int year;
	int month;
	int days;
	int start_day;
}CALENDAR;

void PrintTitle(int year, char *month);
void title(void);
int leapYear(int year);
char *month_name(int month);
void PrintCalendar(CALENDAR *information);
int Month_Day(int leap, int month);
int totalDay(int year, int month);
int start_Day(int year, int month);

int main(void){

	CALENDAR information; // ����ü ���� ����
	title();

	printf("input the year(num) : ");
	scanf("%d", &information.year);
	printf("input the month(1~12) : ");
	scanf("%d", &information.month);
	int c = getchar();
	if (c == 10) { //������ �ƽ�Ű �ڵ��� ���� 10
		system("cls"); //���Ͱ� �ԷµǸ� ȭ�� �����
	}

	information.days = Month_Day(leapYear(information.year), information.month);
	information.start_day = start_Day(information.year, information.month);
	
	PrintTitle(information.year, month_name(information.month));
	PrintCalendar(&information);

	printf("\n\n");

	return 0;
}

void title(void) { //�� ó�� Ÿ��Ʋ �Լ�
	printf("=================================================================\n\n\n\n\n");
	printf("                          CALENDAR        \n\n\n\n\n");
	printf("=================================================================");
	int c = getchar();
	if (c == 10) { //������ �ƽ�Ű �ڵ��� ���� 10
		system("cls"); //���Ͱ� �ԷµǸ� ȭ�� �����
	}
}

char *month_name(int month) { //���ڷ� �Է��� ���� ����� �ٲٴ� ����
	static char *name[13] = { "0", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JULY", "AUG", "SEP", "OCT", "NOV", "DEC" };
	return name[month];
}

void PrintTitle(int year, char *month){
	printf("=================================================================\n");
	printf("                          %4d\t%s\n", year, month);
	printf("=================================================================\n");
}

void PrintCalendar(CALENDAR *information) {
	//��=0 ��=1 ȭ=2 ��=3 ��=4 ��=5 ��=6 ��=7

	int day = 1; //ó�� ��¥�� 1�� ����
	int week_day; //����
	printf("\tSUN\tMON\tTUE\tWED\tTHU\tFRI\tSAT\n");
	
	for (week_day = 0; week_day != information->start_day; week_day++) {
		printf("\t");
	}

	while (day <= information->days) {
		
		printf("\t%2d", day);
		day++;
		week_day++;

		if ((week_day % 7) == 0) {
			printf("\n");
			week_day = 0;
		}
		
	}
}

int leapYear(int year) { //���� ���ϴ� �Լ�
	int leap;
	leap = ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) ? 1 : 0; //�����̸� 1 �ƴϸ� 0
	return leap;
}

int Month_Day(int leap, int month) { //���� �ϼ��� ���ϴ� �Լ�
	int days[2][13] = {
		{0, 31,28,31,30,31,30,31,31,30,31,30,31},
		{0, 31,29,31,30,31,30,31,31,30,31,30,31}
	};
	return days[leap][month];
}

int totalDay(int year, int month){ //�� ��¥�� ���ϴ� �Լ�
	
	int start_year = 1;
	int total_days=0;

	for (int i = start_year; i < year; i++) { //year �� ����
		if (leapYear(i) == 1)
			total_days += 366; //�����̸� total_days�� 366�� ������
		else 
			total_days += 365; //����̸� total_days�� 365�� ������
	}

	for (int j = 1; j < month; j++) { //month ������
		int leap = leapYear(year);
		total_days += Month_Day(leap, j); //���� �ϼ��� ����
	}
	
	return total_days;
}

int start_Day(int year, int month) { //�����ϴ� ���� ���ϱ�
									 //��=0 ��=1 ȭ=2 ��=3 ��=4 ��=5 ��=6 ��=7
	int monthStart;
	int startDay = 1; // 1�� 1�� 1���� ������ ������

	monthStart = (totalDay(year, month) + startDay) % 7; //�������� ��������(������) 7�� ���� �������� ���� ���ۿ����� �ȴ�.
	return monthStart;
}