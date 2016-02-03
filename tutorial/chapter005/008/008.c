#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void get_date();
void day_of_year(int d, int m, int y);
void month_day();

static int daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }};
static char *monthtab[] = {
	"Illegal month",
	"January", "February", "March",
	"April", "May", "June",
	"July", "August", "September",
	"October", "November", "December"};

int main() {
	int c;
	printf("0 - to convert date to day\n1 - to convert day to date\n");
	
	while ((c = getchar()) != EOF) {
		if (c == '0')
			get_date();
		else if (c == '1')
			month_day();
		else
			printf("error: unknown command\n");
		printf("0 - to convert date to day\n1 - to convert day to date\n");
	}
	return 0;
}

void get_date() {
	int c, leap, day, month, year;
	char *s, buf[10];

	s = &buf[0];
	printf("Day: ");

	if ((c = getchar()) != '\n')
		*s++ = c;

	while ((c = getchar()) != '\n' && isdigit(c))
		*s++ = c;
	day = atoi(buf);

	s = &buf[0];
	printf("Month: ");
	while ((c = getchar()) != '\n' && isdigit(c))
		*s++ = c;
	month = atoi(buf);

	s = &buf[0];
	printf("Year: ");
	while ((c = getchar()) != '\n' && isdigit(c))
		*s++ = c;
	year = atoi(buf);

	leap = (year % 4 == 0) && ((year % 400 == 0) || (year % 100 != 0));
	if ((0 <= year) && (year <= 9999) && (1 <= month) && (month <= 12) && (1 <= day) && (day <= daytab[leap][month])) 
		day_of_year(day, month, year);
	else {
		printf("date input error: try once more\n");
		get_date();
	}
}

void day_of_year(int day, int month, int year) {
	int i, leap, num = 0;

	leap = (year % 4 == 0) && ((year % 400 == 0) || (year % 100 != 0));
	for (i = 1; i < month; i++)
		num += daytab[leap][i];
	printf("%d.%d.%d is %d day of the year\n", day, month, year, num);
}

void month_day() {
	int c, i, leap, yearday, year, *dp, out;
	char *s, buf[10], *mp;

	s = &buf[0];
	printf("Day No: ");

	if ((c = getchar()) != '\n')
		*s++ = c;

	while ((c = getchar()) != '\n' && isdigit(c))
		*s++ = c;
	yearday = atoi(buf);
	out = yearday;

	s = &buf[0];
	printf("Year: ");
	while ((c = getchar()) != '\n' && isdigit(c))
		*s++ = c;
	year = atoi(buf);

	leap = (year % 4 == 0) && ((year % 400 == 0) || (year % 100 != 0));

	if ((0 <= year) && (year <= 9999) && (1 <= yearday) && (yearday <= ((leap) ? 366 : 365))) {
		for (i = 1; yearday > daytab[leap][i]; i++)
			yearday -= daytab[leap][i];

		mp = &monthtab[i][0];
		dp = &daytab[leap][0];
		*dp += yearday;
		printf("%d day of the year is %d %s %d\n", out, *dp, mp, year);
	}
	else {
		printf("date input error: try once more\n");
		month_day();
	}
}