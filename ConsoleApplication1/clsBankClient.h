#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iomanip>


#include "clsDate.h"
#include "clsPerson.h"
#include "clsString.h"
#include "clsTime.h"
#include "GlobalUser.h"
#include "clsUtil.h"
using namespace std;
class clsBankClient: public clsPerson
{
private:
	enum enMode 
	{
		EmptyMode=0,
		UpdateMode=1,
		AddNewMode=2 //Lesson #3
	};

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;
	string fileName = "clients.txt";

public:
	clsBankClient(enMode Mode, string firstName, string lastName, string phoneNumber, string email, string AccountNumber,
		string PinCode, float AccountBalance) :clsPerson(firstName, lastName, phoneNumber, email)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}
	string setAccountNumber()
	{
		return _AccountNumber;
	}
	void setPinCode(string pincode)
	{
		_PinCode = pincode;
	}

	void  setAccountBalance(float accountBalance)
	{
		_AccountBalance = accountBalance;
	}
	string getPinCode()
	{
		return _PinCode;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	string getAccountNumber()
	{
		return _AccountNumber;
	}

	void Print()
	{
		cout << "Client Card:" << endl;
		cout << "______________________" << endl;
		cout << "First Name: " << getFirstName() << endl;
		cout << "Last Name: " << getLastName() << endl;
		cout << "Full Name:" << getFullName()<<endl;
		cout << "Email: " << getEmail() << endl;
		cout << "Account Number: " << _AccountNumber << endl;
		cout << "Password: " << _PinCode << endl;
		cout << "Balance: " << _AccountBalance << endl;
		cout << "______________________" << endl;
	}



private:
	
	static clsBankClient _convertLineToClientObject(string Line, string separator = "#//#")
	{
		vector<string> myvec = clsString::split(Line, separator);
		return clsBankClient(enMode::UpdateMode, myvec[0], myvec[1], myvec[3], myvec[2], myvec[4], clsUtil::decrypt(myvec[5]), stod(myvec[6]));

	}

	static clsBankClient _GetEmptyClientOBject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:
	static clsBankClient Find(string AccountNumber)
	{
		//first step:: search within the file
		fstream MyFile;
		MyFile.open("clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline (MyFile, line) )
			{
				clsBankClient Client = _convertLineToClientObject(line);
				if (Client._AccountNumber == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientOBject();
	}



	static clsBankClient Find(string AccountNumber,string pincode)
	{
		//first step:: search within the file
		fstream MyFile;
		MyFile.open("clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsBankClient Client = _convertLineToClientObject(line);
				if (Client._AccountNumber == AccountNumber && Client._PinCode==pincode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientOBject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient client = clsBankClient::Find(AccountNumber);
		return (!client.IsEmpty());
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}


	//##Lesson #2: Update Client
	enum enSaveResultsToFile { svFailedEmptyObject = 0,svSucceed=1 };

	enSaveResultsToFile Save()
	{
		switch (_Mode)
		{
			case enMode::EmptyMode:
				return enSaveResultsToFile:: svFailedEmptyObject;
				break;

			case enMode::UpdateMode:
				_update();
				return enSaveResultsToFile::svSucceed;
				break;
			case enMode::AddNewMode: //## Lesson #3
				if (clsBankClient::IsClientExist(_AccountNumber))
				{
					return enSaveResultsToFile::svFailedEmptyObject;
				}
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResultsToFile::svSucceed;
				break;
				
			
		}
	}

	private:
		void _update()
		{
			vector<clsBankClient> _myvec = _LoadClientDataFromFile();
			fstream file;
			string line;
			file.open(fileName, ios::out); // open for writing

			//step 1 update the data inside the vector
			for (clsBankClient& n : _myvec)
			{
				if (n._AccountNumber == _AccountNumber) // if the client acocunt number same as the account number of the object
				{
					n = *this; //store the new edited info of the object into the clinet inside the vecotr
				}
			}
			//step 2: write the new client info to the file  using the newly updated vector
			_saveDataToFile(_myvec);
			
		}

		static vector<clsBankClient> _LoadClientDataFromFile() //static because I dont wanna do any direct operations on the object by this fn
		{
			vector<clsBankClient> _myvec;
			fstream file;
			file.open("clients.txt", ios::in);
			if(file.is_open())
			{
				string line;
				while (getline(file, line))
				{
					_myvec.push_back(_convertLineToClientObject(line)); // from lesson #1 fn
				}
				file.close();
			}
			return _myvec;

		}

		static void _saveDataToFile(vector<clsBankClient> _myvec)
		{
			fstream file;
			string line;
			file.open("clients.txt", ios::out);
			if(file.is_open())
			{
				for (clsBankClient& c : _myvec)
				{
					if (c._MarkForDelete == false)
					{
						//update for lesson 4 delete client
						line = _convertClientObjectToLine(c);
						file << line << endl;
					}
					
				}
			}
		}

		static string _convertClientObjectToLine(clsBankClient c,string separator="#//#")
		{
			return c.getFirstName() + separator + c.getLastName() + separator + c.getEmail() + separator + c.getPhoneNumber() 
				+ separator + c.getAccountNumber() + separator + clsUtil::encrypt( c.getPinCode() ) + separator + to_string(c.GetAccountBalance());
		}

		//____________________________________
		// ## Lesson#3::Add new Client

		public:

		static clsBankClient GetNewClientObject(string accountNumber)
		{
			return clsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
		}

		private:
		void _AddNew()
		{
			_addDataLineToFile(_convertClientObjectToLine(*this));
		}

		static void _addDataLineToFile(string line)
		{
			
			fstream file;
			file.open("clients.txt", ios::out | ios::in);
			if (file.is_open())
			{
				file << line << endl;
				file.close();
			}
			
		}

		//_______________________________________
		//## Lesson #4: Delete Client
		// ** LoadClient Data got slight update
		public:
		void DeleteClient()
		{
			//step 1: load vector data to file
			vector<clsBankClient> myvec = _LoadClientDataFromFile();
			//find that client that you want to delete and mark it in the vecotr
			fstream file;
			file.open(fileName, ios::out);
			for (clsBankClient& n : myvec)
			{
				if (n._AccountNumber == this->_AccountNumber)
				{
					n._MarkForDelete = true;
				}

			}

			_saveDataToFile(myvec);
			//we didn't write to file but we must flush the object
			*this = _GetEmptyClientOBject();
		}
		//Lesson #5 List Clients
		static vector<clsBankClient> getClientsList()
		{
			return _LoadClientDataFromFile();
		}

		//##Lesson #6 TotalBalances
		public:
		static double getTotalBalances()
		{
			vector<clsBankClient> myvec = _LoadClientDataFromFile();
			if (myvec.size() == 0) return 0;
			double total=0;
			for (clsBankClient& n : myvec)
			{
				total += n.GetAccountBalance();
			}
			return total;
		}
		//##Lesson #14
		bool Deposit(int amount)
		{
			if (amount <= 0)
			{
				return false;
			}
			_AccountBalance += amount;
			Save();
		}

		bool Withdraw(int amount)
		{
			if (amount <= 0 || amount > _AccountBalance)
			{
				return false;
			}
			_AccountBalance -= amount;
			Save();
			return true;
		}

		bool Transfer(float amount, clsBankClient& toClient)
		{
			if (amount <= 0 || amount > _AccountBalance)
			{
				return false;
			}
			this->Withdraw(amount);
			toClient.Deposit(amount);
			_TransferLog( toClient, amount);
			return true;
		}



		static vector<string> _loadTransferLog()
		{
			vector<string> logData;
			fstream file("transferLog.txt", ios::in);
			if (file.is_open())
			{
				string line;
				while (getline(file, line))
				{
					logData.push_back(line);
				}
				file.close();
			}
			return logData;
		}


		string _ConvertTransferInfoToLine(clsBankClient toClient, float amount,clsUser username, string separator = "#//#")
		{

			return clsDate::GetTodaysDate() + "-" + clsTime::GetSystemTime() + separator + getAccountNumber() + separator +
				toClient.getAccountNumber() + separator + to_string(amount) + separator + to_string(GetAccountBalance()) + separator + to_string(toClient.GetAccountBalance()) + separator + username.getUserName();
		}



		void _TransferLog(clsBankClient toClient, float amount)
		{
			vector<string> _logData = _loadTransferLog();
			string line = _ConvertTransferInfoToLine(toClient, amount,CurrentUser);
			fstream file;
			file.open("transferLog.txt", ios::out | ios::app);
			if (file.is_open())
			{
				file << line << endl;
				file.close();
			}
		}
};

