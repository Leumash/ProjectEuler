/*
   You are given the following information, but you may prefer to do some research for yourself.

   1 Jan 1900 was a Monday.
   Thirty days has September,
   April, June and November.
   All the rest have thirty-one,
   Saving February alone,
   Which has twenty-eight, rain or shine.
   And on leap years, twenty-nine.
   A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
   How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
 */

#include <iostream>

using namespace std;

bool IsLeapYear(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return true;
            }

            return false;
        }

        return true;
    }

    return false;
}

int GetDaysInMonth(int month, int year)
{
    if (month == 1)     // Feb
    {
        if (IsLeapYear(year))
        {
            return 29;
        }

        return 28;
    }
    else if (month == 0)
    {
        return 31;
    }
    else if (month == 2)
    {
        return 31;
    }
    else if (month == 3)
    {
        return 30;
    }
    else if (month == 4)
    {
        return 31;
    }
    else if (month == 5)
    {
        return 30;
    }
    else if (month == 6)
    {
        return 31;
    }
    else if (month == 7)
    {
        return 31;
    }
    else if (month == 8)
    {
        return 30;
    }
    else if (month == 9)
    {
        return 31;
    }
    else if (month == 10)
    {
        return 30;
    }
    else if (month == 11)
    {
        return 31;
    }
}

int GetDays()
{
    int day = 1;    // Start on Monday
    int count = 0;

    for (int year=1900; year <=2000; ++year)
    {
        for (int month=0; month<12; ++month)
        {
            // Check if Sunday
            if (day == 0 && year > 1900 && year <= 2000)
            {
                ++count;
            }

            // Set day for next month's first
            int daysInMonth = GetDaysInMonth(month, year);

            day = (day + daysInMonth) % 7;
        }
    }

    return count;
}

int main()
{
    cout << GetDays() << endl;
    return 0;
}

