#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)


#include <chrono>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class clsTime
{
private: 
	struct strTime {
		int hour;
		int minute;
		int second;
	};

	static strTime _GetCurrentTime()
	{
		// Get current time as time_t
		auto now = std::chrono::system_clock::now();
		std::time_t t = std::chrono::system_clock::to_time_t(now);

		// Convert to local time
		std::tm local_tm = *std::localtime(&t);

		strTime Time;
		Time.hour = local_tm.tm_hour;
		Time.minute= local_tm.tm_min;
		Time.second = local_tm.tm_sec;
		return Time;

	}

	static string _CurrentTimeToString(strTime Time)
	{
		return to_string(Time.hour) + ":" + to_string(Time.minute) + ":" + to_string(Time.second);
	}
public:
	static string GetSystemTime()
	{
		return _CurrentTimeToString(_GetCurrentTime());
	}
};

