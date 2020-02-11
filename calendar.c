#include <stdio.h>

typedef struct { //달력의 기본 정보를 저장할 구조체
	int year;
	int month;
	int days;
	int start_day;
}CALENDAR; //구조체 별칭으로 지정


void PrintTitle(int year, int month);
void PrintCalendar(CALENDAR *);

int MonthDays(int year, int month);
int LeapYear(int year);
int TotalDays(int year, int month);
int Space(int year, int month);

int main(void)
{
	CALENDAR information; //구조체 변수 선언
	printf("연도를 입력하세요(숫자) : ");
	scanf("%d", &information.year);
	printf("월을 입력하세요(1~12) : ");
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



void PrintTitle(int year, int month)//Title 그리는 함수
{
	printf("====================================================\n");
	printf("                  %d년\t%d월\n", year, month);
	printf("====================================================\n");
}


void PrintCalendar(CALENDAR *information)//캘린더 그리는 함수
{
	int day = 1; //날짜
	int week_day = 0; // 일요일부터 시작

	printf("SUN\tMON\tTUE\tWED\tTUR\tFRI\tSAT\n"); //일=0,월=1,화=2,수=3,목=4,금=5,토=6
	
	for (week_day = 0; week_day != information->start_day;week_day++)
	{
		printf("\t"); // week_day가 start_day가 아닐때 까지 탭함
	}
	
	while(day <= information->days) //day가 월별 일수 보다 작거나 같을때
	{
		printf("%2d\t", day); //출력

		day++; //day는 +
		week_day++;//week_day++

		if ((week_day % 7) == 0) //week_day가 7로 나누었을때 0이면, 즉 토요일을 넘어가면
		{
			printf("\n"); //일요일은 가장 처음에 있느니깐 "\n" 해줘야됨
			
			week_day = 0; //다시 week_day 0으로 초기화
		}
	}
}



int MonthDays(int year, int month)//월별 날짜들 계산 함수
{
	int days = 0;
	
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10||month==12)
		days = 31; 
	else if (month == 2)
		days = 28 + (LeapYear(year)); //2월은 28일, 윤년일때는 29일
	else
		days = 30; //나머지 달은 30일

	return days;
}


int LeapYear(int year)//윤년 계산 함수
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		/*윤년은 4로 나누어 떨어지는 대신 100으로 나누어 떨어지지 않거나 400으로 나누어 떨어진다*/
		return 1; 
	else
		return 0; 
}

int TotalDays(int year, int month) // 총일수 구하는 함수
{	
	int startYear = 1;//1년부터 시작
	int totalDays = 0;

	for (int i = startYear; i < year; i++) //year전까지
	{
		if (LeapYear(i) == 1) 
			totalDays = totalDays + 366; //윤년이면 366일을 더해주고
		else
			totalDays = totalDays + 365; //윤년이 아니면 365일 더해준다
	}


	for (int i = 1; i < month; i++)
	{
		totalDays = totalDays + MonthDays(year, i); // totalDays에 1월부터 구하고자 하는 달 전까지 일수들을 더해준다
	}

	return totalDays;
}

int Space(int year, int month) // 시작 날 구하는 함수
{
	//일=0,월=1,화=2,수=3,목=4,금=5,토=6
	int totalDays = TotalDays(year, month);
	int weekday;
	int startDay = 1;//startYear은 기원후 1년이고 0001년의 1월 1일은 월요일이므로 startDay는 월요일이다

	weekday = (totalDays+startDay) % 7; //시작 기준점이 월요일이고 이를 기반으로 하여 시작날을 구한다.

	return weekday; // weekday 반환
}