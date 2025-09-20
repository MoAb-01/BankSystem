#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsTime.h"
#include "clsUtil.h"
#include <fstream>
using namespace std;
class clsUser: public clsPerson
{
private:

	enum enMode
	{
		EmptyMode = 0,
		UpdateMode = 1,
		AddNewMode = 2
	};
	string _UserName;
	string _Password;
	int _Permissions;
	enMode _Mode;
	bool _MarkedForDelete = false;


	



public:
	clsUser(enMode Mode, string firstName, string lastName, string phoneNumber, string email, string UserName, string Password, int Permission)
		: clsPerson(firstName, lastName, phoneNumber, email)  // ← This is correct
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permission;
	}

	bool isEmpty()
	{
		return  _Mode ==  enMode::EmptyMode ;
	}

	bool getMarkedForDelete()
	{
		return _MarkedForDelete;
	}

	string setUserName()
	{
		return _UserName;
	}

	void setUserName(string UserName)
	{
		_UserName = UserName;
	}
	string getUserName()
	{
		return _UserName;
	}

	void setPassword(string Password)
	{
		_Password = Password;
	}

	string getPassword()
	{
		return _Password;
	}

	void setPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int getPermissions()
	{
		return _Permissions;
	}
private:


	static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4],clsUtil::decrypt( vUserData[5] ), stoi(vUserData[6]));

	}

	static clsUser _EmptyObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
public:
	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}


	static bool isUserExist(string username)
	{
		clsUser user = clsUser::Find(username);
		return (!user.isEmpty());
	}
public:
	static clsUser Find(string UserName)
	{
		fstream myfile;
		myfile.open("users.txt",ios::in);
		
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsUser myUser = _ConvertLinetoUserObject(line);
				if (myUser._UserName == UserName)
				{
					return myUser;
				}
			}
		}
		return _EmptyObject();
	}


	static clsUser Find(string UserName,string password)
	{
		fstream myfile;
		myfile.open("users.txt", ios::in);

		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsUser myUser = _ConvertLinetoUserObject(line);
				if (myUser._UserName == UserName && myUser._Password==password)
				{
					return myUser;
				}
			}
		}
		return _EmptyObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	enSaveResults save()
	{
		switch (_Mode)
		{
			case enMode::EmptyMode:
			{
				if (isEmpty())
				{
					return enSaveResults::svFaildEmptyObject;
				}
				break;
			}

			case enMode::UpdateMode:
			{
				_Update();
				return enSaveResults::svSucceeded;
				break;
			}



			case enMode::AddNewMode:
			{

				if (isUserExist(_UserName))
				{
					return enSaveResults::svFaildUserExists;
				}
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

		}
	}
	private:


		static vector<clsUser> _loadUsersDataFromFile()
		{
			vector<clsUser> myvec;
			fstream file;
			file.open("users.txt", ios::in);
			string line;
			if (file.is_open())
			{
				while (getline(file, line))
				{
					clsUser myUser = _ConvertLinetoUserObject(line);
					myvec.push_back(myUser);
				}
				file.close();
			}
			return myvec;

		}

		/*clsUser(enMode Mode, string firstName, string lastName, string phoneNumber, string email, string UserName, string Password, int Permission)
			/*: clsPerson(firstName, lastName, phoneNumber, email)*/
		static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
		{

			string UserRecord = "";
			UserRecord += User.getFirstName() + Seperator;
			UserRecord += User.getLastName() + Seperator;
			UserRecord += User.getEmail() + Seperator;
			UserRecord += User.getPhoneNumber() + Seperator;
			UserRecord += User._UserName + Seperator;
			UserRecord += clsUtil::encrypt( User._Password ) + Seperator;
			UserRecord += to_string(User.getPermissions());

			return UserRecord;

		}
		static void _SaveUsersDataToFile(vector <clsUser> vUsers)
		{

        fstream MyFile;
        MyFile.open("users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U._MarkedForDelete == false)
                {
                    //we only write records that are not marked for delete.  
					DataLine = _ConvertUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

		}





		void _Update()
		{
			vector<clsUser> _myvec = _loadUsersDataFromFile();
			//Searching 

			for (clsUser& u : _myvec)
			{
				if (u._UserName == _UserName)
				{
					u = *this;
					break;
				}
			}
			_SaveUsersDataToFile(_myvec);

		}
		void _AddDataLineToFile(string line)
		{
			fstream file;
			file.open("users.txt", ios::out | ios::app);
			if (file.is_open())
			{
				file << line << endl;
				file.close();
			}
		}
		void _AddNew()
		{

			_AddDataLineToFile(_ConvertUserObjectToLine(*this));
		}
		public:
			bool Delete()
			{
				vector<clsUser> myvec = _loadUsersDataFromFile();
				for (clsUser& u : myvec)
				{
					if (u._UserName == _UserName)
					{
						u._MarkedForDelete = true;
						break;
					}
				}
				_SaveUsersDataToFile(myvec);
				*this = _EmptyObject();
				return true;
			}
			static vector <clsUser> GetUsersList()
			{
				return _loadUsersDataFromFile();
			}


			public:
				clsUser GetEmptyUserObject()
				{
					return _EmptyObject();
				}

				enum enUserPermission
				{
					usrAll=-1,
					usrEshowClientList = 1,
					userEAddNewClient = 2,
					userEDeleteClient = 3,
					userEUpdateClient = 4,
					userEFindClient = 5,
					userETransactions = 6,
					userEManageUsers = 7,
					userELoginRegister = 8
				};

				bool CheckAccessPermission(enUserPermission Permission)
				{
					if (this->_Permissions == enUserPermission::usrAll)
						return true;

					if ((Permission & this->_Permissions) == Permission)
						return true;
					else
						return false;

				}

				void StoreUserRegisterInfo()
				{
					string fileName = "loginRegister.txt";
					fstream file;
					file.open(fileName, ios::out | ios::app);
					if (file.is_open())
					{
						file << clsDate::GetTodaysDate() << " - " << clsTime::GetSystemTime() << "#//#" << getUserName() << "#//#" << getPassword() << "#//#" << getPermissions() << endl;
						file.close();
					}
				}
	
};

