#include <stdio.h>

typedef struct { //�޷��� �⺻ ������ ������ ����ü
	int year;
	int month;
	int days;
	int start_day;
}CALENDAR; //����ü ��Ī���� ����


void PrintTitle(int year, int month);
void PrintCalendar(CALENDAR *);

int MonthDays(int year, int month);
int LeapYear(int year);
int TotalDays(int year, int month);
int Space(int year, int month);

int main(void)
{
	CALENDAR information; //����ü ���� ����
	printf("������ �Է��ϼ���(����) : ");
	scanf("%d", &information.year);
	printf("���� �Է��ϼ���(1~12) : ");
	scanf("%d", &information.month);

	LeapYear(information.year);
	TotalDays(information.year, information.month);

	information.start_day = Space(information.year, information.month);
	information.days = MonthDays(information.year, information.month);

	PrintTitle(information.year, information.month);
	PrintCalendar(&information);

	printf("\n");
	return 0;
}



void PrintTitle(int year, int month)//Title �׸��� �Լ�
{
	printf("====================================================\n");
	printf("                  %d��\t%d��\n", year, month);
	printf("====================================================\n");
}


void PrintCalendar(CALENDAR *information)//Ķ���� �׸��� �Լ�
{
	int day = 1; //��¥
	int week_day = 0; // �Ͽ��Ϻ��� ����

	printf("SUN\tMON\tTUE\tWED\tTUR\tFRI\tSAT\n"); //��=0,��=1,ȭ=2,��=3,��=4,��=5,��=6
	
	for (week_day = 0; week_day != information->start_day;week_day++)
	{
		printf("\t"); // week_day�� start_day�� �ƴҶ� ���� ����
	}
	
	while(day <= information->days) //day�� ���� �ϼ� ���� �۰ų� ������
	{
		printf("%2d\t", day); //���

		day++; //day�� +
		week_day++;//week_day++

		if ((week_day % 7) == 0) //week_day�� 7�� ���������� 0�̸�, �� ������� �Ѿ��
		{
			printf("\n"); //�Ͽ����� ���� ó���� �ִ��ϱ� "\n" ����ߵ�
			
			week_day = 0; //�ٽ� week_day 0���� �ʱ�ȭ
		}
	}
}



int MonthDays(int year, int month)//���� ��¥�� ��� �Լ�
{
	int days = 0;
	
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10||month==12)
		days = 31; 
	else if (month == 2)
		days = 28 + (LeapYear(year)); //2���� 28��, �����϶��� 29��
	else
		days = 30; //������ ���� 30��

	return days;
}


int LeapYear(int year)//���� ��� �Լ�
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		/*������ 4�� ������ �������� ��� 100���� ������ �������� �ʰų� 400���� ������ ��������*/
		return 1; 
	else
		return 0; 
}

int TotalDays(int year, int month) // ���ϼ� ���ϴ� �Լ�
{	
	int startYear = 1;//1����� ����
	int totalDays = 0;

	for (int i = startYear; i < year; i++) //year������
	{
		if (LeapYear(i) == 1) 
			totalDays = totalDays + 366; //�����̸� 366���� �����ְ�
		else
			totalDays = totalDays + 365; //������ �ƴϸ� 365�� �����ش�
	}


	for (int i = 1; i < month; i++)
	{
		totalDays = totalDays + MonthDays(year, i); // totalDays�� 1������ ���ϰ��� �ϴ� �� ������ �ϼ����� �����ش�
	}

	return totalDays;
}

int Space(int year, int month) // ���� �� ���ϴ� �Լ�
{
	//��=0,��=1,ȭ=2,��=3,��=4,��=5,��=6
	int totalDays = TotalDays(year, month);
	int weekday;
	int startDay = 1;//startYear�� ����� 1���̰� 0001���� 1�� 1���� �������̹Ƿ� startDay�� �������̴�

	weekday = (totalDays+startDay) % 7; //���� �������� �������̰� �̸� ������� �Ͽ� ���۳��� ���Ѵ�.

	return weekday; // weekday ��ȯ
}