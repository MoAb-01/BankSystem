#pragma once

#include "clsDate.h"
#include <iostream>
#include <limits>
#include <string>

template <class T>
class clsInputValidate
{
public:
    static bool isNumberBetween(T number, T from, T to)
    {
        return number >= from && number <= to;

    }

    static bool isDateBetween(clsDate date, clsDate dateFrom, clsDate dateTo)
    {
        // First, handle the case where the year is strictly between
        if (date.Year > dateFrom.Year && date.Year < dateTo.Year)
            return true;

        // If years are the same as the lower bound
        if (date.Year == dateFrom.Year)
        {
            if (date.Month > dateFrom.Month) return true;
            if (date.Month == dateFrom.Month && date.Day >= dateFrom.Day) return true;
        }

        // If years are the same as the upper bound
        if (date.Year == dateTo.Year)
        {
            if (date.Month < dateTo.Month) return true;
            if (date.Month == dateTo.Month && date.Day <= dateTo.Day) return true;
        }

        // Special case: both bounds are in the same year
        if (dateFrom.Year == dateTo.Year)
        {
            if (date.Year == dateFrom.Year)
            {
                if (date.Month > dateFrom.Month && date.Month < dateTo.Month)
                    return true;
                if (date.Month == dateFrom.Month && date.Day >= dateFrom.Day)
                    return true;
                if (date.Month == dateTo.Month && date.Day <= dateTo.Day)
                    return true;
            }
        }

        return false; // Add missing return statement
    }

    static T Read(string txt = "")
    {
        T x;
        while (true)
        {
            cin >> x;
            if (!cin.fail())
            {
                return x;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input

        }
    }
 

    static T readNumberBetween(T from, T to, string message="")
    {
        T x;
        do
        {
            x = Read("invalid data Type");
            if (!(x >= from && x <= to))
                cout << message << endl;

        } while (!(x >= from && x <= to));
        return x;
    }
    static bool isValidDate(clsDate date)
    {
        int totalDays = date.NumberOfDaysInAMonth();

        if (date.Month >= 1 && date.Month <= 12)
        {
            if (date.Day >= 1 && totalDays >= date.Day)
            {
                return true;
            }
        }
        return false;
    }
    
};
