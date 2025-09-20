#pragma once
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;


class clsDate
{

private:
	int day;
	int month;
	int year;

public:

	clsDate(int day, int month, int year) {

		this->day = day;
		this->month = month;
		this->year = year;
	}

	clsDate()
	{
		std::time_t now = std::time(nullptr);

		// Convert to local time structure
		std::tm* localTime = std::localtime(&now);

		// Extract date parts
		day = localTime->tm_mday;
		month = localTime->tm_mon + 1;  // tm_mon is 0-based
		year = localTime->tm_year + 1900; // tm_year counts years since 1900
	}

	clsDate(string Date)
	{
		clsDate myDate = StringToDate(Date);
		day = myDate.day;
		month = myDate.month;
		year = myDate.year;
	}
	clsDate(int totalDays, int year)
	{
		clsDate mydate = GetDateForTotalDays(totalDays, year);

		this->day = mydate.day;
		this->month = mydate.month;
		this->year = mydate.year;
	}



	static vector<string> SplitString(string dateString, string del)
	{
		vector<string> tokens;

		int pos;
		while ((pos = dateString.find(del)) != string::npos) //if the delm is found
		{
			tokens.push_back(dateString.substr(0, pos)); // 2024/
			dateString.erase(0, pos + del.length());
		}
		if (!dateString.empty())
		{
			tokens.push_back(dateString);
		}

		return tokens;

	}


	static  clsDate StringToDate(string dateString)
	{
		vector<string> myvec = SplitString(dateString, "/");

		clsDate date;
		date.day = stoi(myvec[0]);
		date.month = stoi(myvec[1]);
		date.year = stoi(myvec[2]);
		return date;
	}

	//**********//
	static bool isLeapYear(int Year)
	{
		return ((Year % 100 == 0) && (Year % 400 == 0)) || (Year % 4 == 0 && Year % 100 != 0);
	}

	bool isLeapYear()
	{
		return ((year % 100 == 0) && (year % 400 == 0)) || (year % 4 == 0 && year % 100 != 0);
	}

	//**********//
	static int MonthToDays(int year, int month)
	{

		if (month < 1 || month>12)
		{
			return 0;
		}

		return (month == 2 ? (isLeapYear(year) ? 29 : 28) : (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) ? 31 : 30);
	}
	int MonthToDays()
	{

		if (month < 1 || month>12)
		{
			return 0;
		}

		return (month == 2 ? (isLeapYear(year) ? 29 : 28) : (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) ? 31 : 30);
	}
	//**********//
	static int CalculateTotalDaysFromADate(int year, int month, int day)
	{
		int totalDays = 0;
		//we check if it is leap year or not  ti know the total days in the year

		for (int i = 0; i < month - 1; ++i)
		{
			totalDays = totalDays + (MonthToDays(year, i + 1));
		}
		totalDays += day;
		return totalDays;

	}

	int CalculateTotalDaysFromADate()
	{
		int totalDays = 0;
		//we check if it is leap year or not  ti know the total days in the year

		for (int i = 0; i < month - 1; ++i)
		{
			totalDays = totalDays + (MonthToDays(year, i + 1));
		}
		totalDays += day;
		return totalDays;

	}
	//*********//

	static clsDate GetDateForTotalDays(int totalDays, int year)
	{
		clsDate Date{};
		Date.year = year;

		int i;
		for (i = 1; i <= 12; ++i)
		{
			int monthDays = MonthToDays(year, i); // Get number of days in this month
			if (totalDays <= monthDays)
			{
				Date.month = i;
				Date.day = totalDays;
				return Date;
			}
			totalDays -= monthDays;
		}

		return Date;
	}



	//**********//

	static void PrintNumberOfYearsFromDay(int year, int month, int day)
	{
		int TotalDays = CalculateTotalDaysFromADate(year, month, day);
		cout << "Number Of Days From The Beginning Of The Year is " << TotalDays;
		GetDateForTotalDays(year, TotalDays);
	}

	void Print()
	{
		cout << day << "/" << month << "/" << year << endl;
	}









};

