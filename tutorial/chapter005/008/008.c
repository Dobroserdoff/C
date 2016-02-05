#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void get_date();
int get_routine(char s[]);
void day_of_year();
void month_day();

int *daytab[2];
int nonleap_array[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int leap_array[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *monthtab[] = {"Illegal month", "January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"};

int main() {
	int c;
	daytab[0] = &nonleap_array[0];
	daytab[1] = &leap_array[0];
	printf("0 - to convert date to day\n1 - to convert day to date\n");
	
	while ((c = getchar()) != EOF) {
		if (c == '0')
			day_of_year();
		else if (c == '1')
			month_day();
		else
			printf("error: unknown command\n");
		printf("0 - to convert date to day\n1 - to convert day to date\n");
	}
	return 0;
}

void day_of_year() {
	int i, leap, num = 0;
	int day = get_routine("Day: ");
	int month = get_routine("Month: ");
	int year = get_routine("Year: ");

	leap = (year % 4 == 0) && ((year % 400 == 0) || (year % 100 != 0));
	if ((0 <= year) && (year <= 9999) && (1 <= month) && (month <= 12) && (1 <= day) && (day <= *(daytab[leap] + month))) {
		for (i = 0; i < month; i++)
			num += *(daytab[leap] + i);
		num += day;
		printf("%d.%d.%d is %d day of the year\n", day, month, year, num);
	}
	else {
		printf("date input error: try once more\n");
		day_of_year();
	}
}

void month_day() {
	char *mp;
	int i, leap, *dp, out;
	int yearday = get_routine("Day No: ");
	int year = get_routine("Year: ");
	out = yearday;
	
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

int get_routine(char str[]) {
	int c;
	char *s, buf[10];

	s = &buf[0];
	printf("%s", str);

	if ((c = getchar()) != '\n')
		*s++ = c;

	while ((c = getchar()) != '\n' && isdigit(c))
		*s++ = c;
	return atoi(buf);
}
