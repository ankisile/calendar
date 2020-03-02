#include <stdio.h>
#include <windows.h> //system 함수를 사용하기 위해
#include <time.h>

typedef struct { //달력의 정보를 입력할 구조체 선언
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

	CALENDAR information; // 구조체 변수 선언
	title();

	printf("input the year(num) : ");
	scanf("%d", &information.year);
	printf("input the month(1~12) : ");
	scanf("%d", &information.month);
	int c = getchar();
	if (c == 10) { //엔터의 아스키 코드의 값이 10
		system("cls"); //엔터가 입력되면 화면 지우기
	}

	information.days = Month_Day(leapYear(information.year), information.month);
	information.start_day = start_Day(information.year, information.month);
	
	PrintTitle(information.year, month_name(information.month));
	PrintCalendar(&information);

	printf("\n\n");

	return 0;
}

void title(void) { //맨 처음 타이틀 함수
	printf("=================================================================\n\n\n\n\n");
	printf("                          CALENDAR        \n\n\n\n\n");
	printf("=================================================================");
	int c = getchar();
	if (c == 10) { //엔터의 아스키 코드의 값이 10
		system("cls"); //엔터가 입력되면 화면 지우기
	}
}

char *month_name(int month) { //숫자로 입력한 달을 영어로 바꾸는 역할
	static char *name[13] = { "0", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JULY", "AUG", "SEP", "OCT", "NOV", "DEC" };
	return name[month];
}

void PrintTitle(int year, char *month){
	printf("=================================================================\n");
	printf("                          %4d\t%s\n", year, month);
	printf("=================================================================\n");
}

void PrintCalendar(CALENDAR *information) {
	//일=0 월=1 화=2 수=3 목=4 금=5 토=6 일=7

	int day = 1; //처음 날짜를 1로 설정
	int week_day; //요일
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

int leapYear(int year) { //윤년 구하는 함수
	int leap;
	leap = ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) ? 1 : 0; //윤년이면 1 아니면 0
	return leap;
}

int Month_Day(int leap, int month) { //달의 일수를 구하는 함수
	int days[2][13] = {
		{0, 31,28,31,30,31,30,31,31,30,31,30,31},
		{0, 31,29,31,30,31,30,31,31,30,31,30,31}
	};
	return days[leap][month];
}

int totalDay(int year, int month){ //총 날짜를 구하는 함수
	
	int start_year = 1;
	int total_days=0;

	for (int i = start_year; i < year; i++) { //year 전 까지
		if (leapYear(i) == 1)
			total_days += 366; //윤년이면 total_days에 366를 더해줌
		else 
			total_days += 365; //평년이면 total_days에 365를 더해줌
	}

	for (int j = 1; j < month; j++) { //month 전까지
		int leap = leapYear(year);
		total_days += Month_Day(leap, j); //달의 일수를 더함
	}
	
	return total_days;
}

int start_Day(int year, int month) { //시작하는 요일 구하기
									 //일=0 월=1 화=2 수=3 목=4 금=5 토=6 일=7
	int monthStart;
	int startDay = 1; // 1년 1월 1일의 요일은 월요일

	monthStart = (totalDay(year, month) + startDay) % 7; //시작점을 기준으로(월요일) 7로 나눈 나머지가 월의 시작요일이 된다.
	return monthStart;
}