#include <stdio.h>

int day_of_year(int, int, int);
void month_day(int, int , int *, int *);

int main(void)
{
        int m, d;

        printf("day_of_year(2025, 1, 1) = %d (expected 1)\n", day_of_year(2025, 1, 1));
        printf("day_of_year(2025, 12, 31) = %d (expected 365)\n", day_of_year(2025, 12, 31));
        printf("day_of_year(2024, 12, 31) = %d (expected 366)\n", day_of_year(2024, 12, 31));
        printf("day_of_year(2025, 3, 1) = %d (expected 60)\n", day_of_year(2025, 3, 1));
        printf("day_of_year(2024, 3, 1) = %d (expected 61)\n", day_of_year(2024, 3, 1));

        /* error cases */
        printf("day_of_year(2025, 0, 1) = %d (expected -1)\n", day_of_year(2025, 0, 1));
        printf("day_of_year(2025, 13, 1) = %d (expected -1)\n", day_of_year(2025, 13, 1));
        printf("day_of_year(2025, 2, 30) = %d (expected -1)\n", day_of_year(2025, 2, 30));
        printf("day_of_year(2025, 6, 0) = %d (expected -1)\n", day_of_year(2025, 6, 0));
        printf("day_of_year(2024, 2, 29) = %d (expected 60)\n", day_of_year(2024, 2, 29));
        printf("day_of_year(2025, 2, 29) = %d (expected -1)\n", day_of_year(2025, 2, 29));

        month_day(2025, 1, &m, &d);
        printf("month_day(2025, 1) = %d/%d (expected 1/1)\n", m, d);

        month_day(2025, 365, &m, &d);
        printf("month_day(2025, 365) = %d/%d (expected 12/31)\n", m, d);

        month_day(2024, 366, &m, &d);
        printf("month_day(2024, 366) = %d/%d (expected 12/31)\n", m, d);

        month_day(2025, 60, &m, &d);
        printf("month_day(2025, 60) = %d/%d (expected 3/1)\n", m, d);

        /* error cases */
        month_day(2025, 0, &m, &d);
        printf("month_day(2025, 0) = %d/%d (expected -1/-1)\n", m, d);

        month_day(2025, 366, &m, &d);
        printf("month_day(2025, 366) = %d/%d (expected -1/-1)\n", m, d);

        month_day(2024, 367, &m, &d);
        printf("month_day(2024, 367) = %d/%d (expected -1/-1)\n", m, d);

        return 0;
}

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
        int leap;
        leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

        if (month < 1 || month > 12)
                return -1;
        if (day < 1 || day > daytab[leap][month])
                return -1;

        char *p = daytab[leap];
        char *pb = daytab[leap];
        while (p < pb + month)
                day += *p++;
        return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
        int leap;
        leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;

        if (yearday < 1 || ((leap) ? yearday > 366 : yearday > 365)) {
                *pmonth = *pday = -1;
                return;
        }

        char *p = daytab[leap];
        char *pb = daytab[leap];
        while (yearday > *p)
                yearday -= *p++;
        *pmonth = p - pb;
        *pday = yearday;
}
