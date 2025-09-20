#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
class clsUtil
{
public:
	enum enCharType
	{
		capitalLetters = 1,
		smallLetters = 2,
		digits = 3,
		MixChar = 4,
		SpcialCharacter = 5
	};
	static void sRand()
	{
		srand(unsigned int(time(NULL)));
	}

	static int getRandomNumber(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

	static char getRandomCharacter(enCharType charType)
	{
		switch (charType)
		{
		case enCharType::capitalLetters:
			return getRandomNumber(65, 90);
			break;
		case enCharType::smallLetters:
			return getRandomNumber(97, 122);
			break;
		case enCharType::digits:
			return getRandomNumber(48, 57);
			break;
		case enCharType::SpcialCharacter:
			return getRandomNumber(32, 47);
			break;
		}
	}

	static string GenerateRandomWord(enCharType chartype, short wordlength)
	{
		string word = "";
		for (int i = 0; i < wordlength; ++i)
		{
			word = word + getRandomCharacter(chartype);
		}
		return word;
	}

	static string GenerateRandomKey(enCharType charType)
	{
		string key = "";
		int length = 4;
		for (int i = 0; i < 4; ++i)
		{
			key = key + GenerateRandomWord(charType, 4);

			if (i != 4 - 1)
			{
				key += "-";
			}
		}
		return key;
	}


	static vector<string> GenerateRandomKeys(short numberOfKeys, enCharType charType)
	{

		vector<string> myvec;
		for (int i = 0; i < numberOfKeys; ++i)
		{
			myvec.push_back(GenerateRandomKey(charType));
		}
		return myvec;
	}


	static void swap(int& num1, int& num2)
	{
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void swap(double& num1, double& num2)
	{
		double temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void swap(string& num1, string& num2)
	{
		string temp = num1;
		num1 = num2;
		num2 = temp;
	}



	static void ShuffleArray(int arr[], int length)
	{
		int randNum1; //random index
		int randNum2;
		for (int i = 0; i < length; ++i)
		{
			randNum1 = getRandomNumber(0, length - 1); //random index
			randNum2 = getRandomNumber(0, length - 1); //random index 2
			swap(arr[randNum1], arr[randNum2]);

		}
	}

	static void fillArrayWithRandomNumbers(int arr[], int length, int from, int to)
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = getRandomNumber(from, to);
		}
	}

	static void fillArrayWithRandomWord(string arr[], int length, enCharType charType, short wordLength)
	{
		for (int i = 0; i < wordLength; i++)
		{
			arr[i] = getRandomCharacter(charType);
		}
	}

	static void fillArrayWithRandomKeys(string arr[], int length, enCharType charType)
	{
		for (int i = 0; i < length; ++i)
		{
			arr[i] = GenerateRandomKey(charType);
		}
	}

	static void tabs(short numberOfTabs)
	{
		for (int i = 0; i < numberOfTabs; ++i)
		{
			cout << "\t";
		}
	}
	static string encryptText(string text, short key)
	{
		for (int i = 0; i < text.length(); ++i)
		{
			text[i] += key;
		}
		return text;
	}

	static string decryptkey(string text, short key)
	{
		for (int i = 0; i < text.length(); ++i)
		{
			text[i] -= key;
		}
		return text;
	}

	static string NumberToText(int number)
	{
		/*In English, we read numbers in groups of thousands:

		123 ? One Hundred Twenty Three

		1,234 ? One Thousand Two Hundred Thirty Four

		12,345 ? Twelve Thousand Three Hundred Forty Five

		1,000,000 ? One Million

		So, the logical structure in language is: Billions ? Millions ? Thousands ? Hundreds ? Tens ? Units
		So we group by magnitude: every 3 digits ? thousands, millions, etc.
		*/

		//group	1: odd numbers that needs to be memroized
		if (number == 0)
		{
			return "";
		}

		if (number >= 1 && number <= 19)
		{
			string arr[] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
			return(arr[number]);
		}

		//group 2: numbers that are in position of tens ( from 20---99 )
		//we extract the tens position digit then we recall the fn again to get the group1 
		if (number >= 20 && number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Fourty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return (arr[number / 10]) + " " + NumberToText(number % 10);
		}
		//group 3: numbers of 1 hundreds (from 100--199)
		if (number >= 100 && number <= 199)
		{
			return "one hundred " + NumberToText(number % 100);
		}

		//group 4:: numbers in hundreds (from 101---999)
		if (number >= 200 && number <= 999)
		{
			return NumberToText(number / 100) + " Hundred " + NumberToText(number % 100);
		}
		//group 5:: numbers in one thousand (from 1000-1999)
		if (number >= 1000 && number <= 1999)
		{
			return "One thousand " + NumberToText(number % 1000);
		}
		//group 6:: numbers in thousnads( from 2000- 999,999)
		if (number >= 2000 && number <= 999999)
		{
			return NumberToText(number / 1000) + " Thousand " + NumberToText(number % 1000);
		}
		//group 7:: numbers in one million ( from 1,000,000- 1,999,999)
		if (number >= 1000000 && number <= 1999999)
		{
			return "One million " + NumberToText(number % 1000000);
		}
		//group 8:: numbers in millions (from 2,000,000 - 999,999,999)
		if (number >= 2000000 && number <= 999999999)
		{
			return NumberToText(number / 1000000) + " Million " + NumberToText(number % 1000000);
		}
		//group 9:: number in one billion (from 1,000,000,000 - 1,999,999,999)
		if (number >= 1000000000 && number <= 1999999999)
		{
			return "One Billion " + NumberToText(number % 1000000000);
		}

		//group 10:: numbers in billions (from 2,000,000,000- 999,999,999,999)
		if (number >= 2000000000 && number <= 999999999)
		{
			return NumberToText(number / 1000000000) + " Billion " + NumberToText(number % 1000000000);
		}
	}

	static string encrypt(string txt)
	{
		int key = 2;
		for (char& n : txt)
		{
			n = n + key;
		}
		return txt;
	}
	static string decrypt(string txt, int key=2)
	{
		for (char& n : txt)
		{
			n = n - key;
		}
		return txt;
	}
};

