#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <fstream>
using namespace std;


class clsCurrency
{
private:

	enum enMode {eEmptyMode=1, eUpdateMode=2};

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;



	static clsCurrency _convertLineToCurrencyObject(string line,string separator="#//#")
	{
		vector<string> myvec = clsString::split(line, separator);
		if (myvec.size() == 4)
		{
			return clsCurrency(eUpdateMode, myvec[0], myvec[1], myvec[2], stof(myvec[3]));
		}
	}

	static vector<clsCurrency> _LoadCurrencysDataFromFile()
	{
		vector<clsCurrency> _myvec;
		fstream file;
		file.open("Currencies.txt", ios::in);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				_myvec.push_back(_convertLineToCurrencyObject(line)); // from lesson #1 fn
			}
		}
		return _myvec;
	}


	static string _convertToCurrencyObjectLine(clsCurrency Currency)
	{
		return Currency._Country + "#//#" + Currency._CurrencyCode + "#//#" + Currency._CurrencyName + "#//#" + to_string(Currency._Rate);
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> myvec)
	{
		fstream file;
		file.open("Currencies.txt", ios::out);
		if (file.is_open())
		{
			for (clsCurrency& C : myvec)
			{
				file << _convertToCurrencyObjectLine(C)<<endl;
			}
		}
	}


	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(eEmptyMode, "", "", "", 0.0f);			
	}

	void _Update() //update the currency object when we update the currency rate //we are inside the updated currency object already
	{
		vector<clsCurrency> myvec = _LoadCurrencysDataFromFile();
		fstream file;

		for (clsCurrency& C : myvec)
		{
			if (C._CurrencyCode == this->_CurrencyCode)
			{
				C._Rate = this->_Rate; //update the rate of the currency object
			}
		}
		_SaveCurrencyDataToFile(myvec); //save the updated vector to the file

	}


public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string getCountry()
	{
		return _Country;
	}

	string getCurrencyCode()
	{
		return _CurrencyCode;
	}

	string getCurrencyName()
	{
		return _CurrencyName;
	}

	float getRate()
	{
		return _Rate;
	}
	static clsCurrency FindByCode(string currencyCode)
	{
		currencyCode = clsString::UpperAllString(currencyCode);
		vector<clsCurrency> myvec = _LoadCurrencysDataFromFile();
		for (clsCurrency& C : myvec)
		{
			if (clsString::UpperAllString( C._CurrencyCode) == currencyCode)
			{
				return C;
			}
		}
		return _GetEmptyCurrencyObject();
	}
     
	static clsCurrency FindByCountry(string CurrencyCountry)
	{
		CurrencyCountry = clsString::UpperAllString(CurrencyCountry);
		vector<clsCurrency> myvec = _LoadCurrencysDataFromFile();
		for (clsCurrency& C : myvec)
		{
			if (clsString::UpperAllString( C._Country) == CurrencyCountry)
			{
				return C;
			}
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist (string CurrencyCode) //EGP
	{
		clsCurrency C = FindByCode(CurrencyCode);
		return C._Mode != eEmptyMode;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	void Print()
	{
		cout << "_________________________________" << endl;
		cout << "Country: " << getCountry() << endl;
		cout << "Currency Code: " << getCurrencyCode() << endl;
		cout << "Currency Name: " << getCountry() << endl;
		cout << "Rate: " << getRate() << endl;
		cout << "_________________________________" << endl;
		cout << endl;
	}
	bool isEmpty()
	{
		return _Mode == eEmptyMode;
	}
	static vector<clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrencysDataFromFile();
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencysDataFromFile();
	}

	static bool isCurrenciesSame(clsCurrency currency1, clsCurrency currency2)
	{
		return currency1.getCurrencyCode() == currency2.getCurrencyCode();
	}
	bool isUSD()
	{
		return getCurrencyCode() == "USD";
	}

	double ConvertFromCurrencyToUSD(double amount)
	{
		return amount /= getRate(); //convert from the currency to USD
	}

	double ConvertFromUSDToCurrency(double amountInUSD)
	{
		return amountInUSD * getRate();
	}

};

