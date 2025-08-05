
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;





enum enClientChoice
{
	ShowClientList = 1,
	AddNewClient = 2,
	DeleteClient = 3,
	UpdateClient = 4,
	FindClient = 5,
	eTransactions = 6,
	enManageUsers=7,
	enLogOut = 8
};

enum enTransactionChoice
{
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalances = 3,
	eMainMeunue = 4
};

enum enUsersChoice
{
	eListUsers=1,
	eAddNewUser=2,
	eDeleteUser=3,
	eUpdateUser=4,
	eFindUser=5,
	eMainMenue=6
};

enum enUserPermission
{
 usrEshowClientList = 1,
 userEAddNewClient = 2,
 userEDeleteClient = 3,
 userEUpdateClient = 4,
 userEFindClient = 5,
 userETransactions = 6,
 userEManageUsers = 7
};

struct strClient
{
	string accNo;
	string pincode;
	string clientName;
	string phonenumber;
	bool isMarked = false;
	double balance;
};

//###///###//###
struct strUser
{
	string UsrName;
	short password;
	int permission;
	bool isMarked = false;
};


std::vector<strUser> loadUsers(std::string filename);
void Login();
void ManageUsers(int);
bool checkPermission(int, int);
void PrintUserInfoCard(strUser user);
string convertUserRecordToLine(strUser user, string del);
bool isUserExist(string userName);
void AddNewUser(int permission, bool isNewUser, string UserName);
strUser ReturnUserByUsername(string username);






void MainMenueMssg(int& choice)
{
	system("cls");
	cout << "===========================\n";
	cout << "\t\t Main Menue Screen\n";
	cout << "===========================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] ManageUsers.\n";
	cout << "\t[8] Log Out.\n";
	cout << "===========================\n";
	cout << "Choose what do you want to do ? [1 to 8]: ";
	cin >> choice;
}

vector<string> splitString(string line, string del)
{
	int pos;
	vector<string> token;
	while ((pos = line.find(del)) != string::npos)
	{
		token.push_back(line.substr(0, pos));
		line.erase(0, pos + del.length());
	}
	if (!line.empty())
	{
		token.push_back(line);
	}
	return token;

}

strClient ConvertLineToRecord(string line)
{
	strClient client;
	string separator = "#//#";
	string builder = " ";
	int count = 0;
	vector<string> token = splitString(line, "#//#"); //tokens 
	client.accNo = token[0]; //account number
	client.pincode = token[1]; //pincode
	client.clientName = token[2];
	client.phonenumber = token[3];
	client.balance = stod(token[4]);

	return client;
}

vector<strClient> loadClient(string filename) //getting client from a file
{
	vector<strClient> myvec;
	strClient client;
	fstream myfile;
	string line;
	myfile.open(filename, ios::in);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			client = ConvertLineToRecord(line);
			myvec.push_back(client);
		}
	}
	myfile.close();
	return myvec;
}
void ShowClientsList(bool isSubProgram = false)
{
	system("cls");
	char choice;
	vector<strClient> myvec = loadClient("clients.txt");
	cout << "\t\t\t\t Client list (" << myvec.size() << ") Client(s).\n";
	cout << "_____________________________________________________________________________" << endl;
	cout << "| " << setw(15) << "Account Number"
		<< "| " << setw(10) << "Pin Code"
		<< "| " << setw(20) << "Client Name"
		<< "| " << setw(15) << "Phone"
		<< "| " << setw(10) << "Balance"
		<< " |" << endl;
	cout << "______________________________________________________________________________" << endl;
	for (int i = 0; i < myvec.size(); ++i)
	{
		cout << "| " << setw(15) << myvec[i].accNo
			<< "| " << setw(10) << myvec[i].pincode
			<< "| " << setw(20) << myvec[i].clientName
			<< "| " << setw(15) << myvec[i].phonenumber
			<< "| " << setw(10) << myvec[i].balance
			<< " |" << endl;
	}
	if (isSubProgram == true) return;
	cout << "Press Any Key To Go Main Menu";
	system("pause>0");



}
bool isAccountNumberExist(strClient client, vector<strClient> myvec)
{
	for (int i = 0; i < myvec.size(); ++i)
	{
		if (client.accNo == myvec[i].accNo)
		{
			return true;
		}
	}
	return false;
}
bool isAccountNumberExist(string accountNumber, vector<strClient> myvec)
{
	for (int i = 0; i < myvec.size(); ++i)
	{
		if (accountNumber == myvec[i].accNo)
		{
			return true;
		}
	}
	return false;
}


strClient ClientInfo(vector<strClient> myvec, bool isNewClient = true) //adding new client
{

	bool flag = false;
	strClient client;

	if (isNewClient == true)
	{

		do
		{
			if (flag == true) cout << "This account Number " << client.accNo << " Already Exists " << "Enter another number?\n";
			cout << "Enter Account Number: ";
			getline(cin >> ws, client.accNo);
			flag = true;
		} while (isAccountNumberExist(client.accNo, myvec) == true);


	}

	cout << "Enter Pin Code: ";
	getline(cin >> ws, client.pincode);

	cout << "Enter Name: ";
	getline(cin >> ws, client.clientName);
	cout << "Enter Phone Number: ";
	getline(cin >> ws, client.phonenumber);

	cout << "Enter Balance: ";
	cin >> client.balance;
	return client;
}
string convertRecordToLine(strClient client, string del)
{
	string line = "";
	line = client.accNo + del + client.pincode + del + client.clientName + del + client.phonenumber + del + to_string(client.balance);
	return line;
}
void AddNewClients()
{
	system("cls");

	strClient client;
	vector<strClient> myvec = loadClient("clients.txt");
	string line;
	fstream myfile;
	myfile.open("clients.txt", ios::app);

	char choice;
	do
	{
		client = ClientInfo(myvec);
		line = convertRecordToLine(client, "#//#");
		if (myfile.is_open())
		{
			myfile << line << endl;
		}
		myvec = loadClient("clients.txt");
		cout << "Client Added Sucessfully!\n";
		cout << "Do you want to add more clients? Y N ";
		cin >> choice;
		if (choice == 'Y')
		{
			system("cls");
		}
	} while (toupper(choice) == 'Y');



}
strClient MarkClient(string accountNumber, vector<strClient>& myvec)
{


	for (strClient& n : myvec)
	{
		if (accountNumber == n.accNo)
		{
			n.isMarked = true;
			return n;
		}
	}
}

bool FindClientWithAccountNumber(string accountNumber)
{
	vector<strClient> myvec = loadClient("clients.txt");
	for (strClient n : myvec)
	{
		if (n.accNo == accountNumber)
		{
			cout << "\n\t\t\tClient is found. The following details..:\n";
			cout << "-----------------\n";
			cout << "Accont Number: " << n.accNo << endl;
			cout << "Pin Code:\t " << n.pincode << endl;
			cout << "Name:\t\t" << n.clientName << endl;
			cout << "Phone:\t " << n.phonenumber << endl;
			cout << "Account Balance: " << n.balance << endl;
			cout << "-----------------\n\n\n\n";
			return true;
		}
	}
	cout << "The Client is not found !\n";
	return false;


}

strClient SaveClientInfo(string accountNumber)
{
	vector<strClient> myvec = loadClient("clients.txt");
	for (strClient n : myvec)
	{
		if (n.accNo == accountNumber)
		{
			return n;
		}
	}
	cout << "The Client is not found !";

}



void DeleteClients()
{
	system("cls");

	cout << "====================================\n";
	cout << "\t\tDelete Client\t\t\n";
	cout << "====================================\n";

	fstream myfile;
	string accountNumber;
	char choice;

	cout << "Please Enter account number? ";
	cin >> accountNumber;

	vector<strClient> myvec = loadClient("clients.txt");

	if (isAccountNumberExist(accountNumber, myvec) == false)
	{
		cout << "Client with account number (" << accountNumber << ") is not found" << endl;
		cout << "press any key to go back to main menue...";
		system("pause>0");
		return;
	}

	strClient clientToDelete = MarkClient(accountNumber, myvec);
	string line;
	FindClientWithAccountNumber(clientToDelete.accNo);

	myfile.open("clients.txt", ios::out);

	cout << "Are u sure you want to delete this client? Y N";
	cin >> choice;

	if (myfile.is_open() && toupper(choice) == 'Y')
	{

		for (strClient& client : myvec)
		{
			line = convertRecordToLine(client, "#//#");
			if (client.isMarked == true)
			{
				continue;
			}
			myfile << line << endl;

		}
		cout << "Client Deleted Successuflly! " << endl;

	}

	cout << "press any key to go back to main menue...";
	system("pause>0");



}


void UpdateClientInfo()
{
	system("cls");

	char choice;
	vector<strClient> myvec = loadClient("clients.txt");
	string accNo;
	strClient clientToBeUpdated;
	fstream file;

	cout << "Enter accountNumber: ";
	cin >> accNo;
	if (FindClientWithAccountNumber(accNo) == true)
	{
		cout << "Are u sure you want to update this client info? Y N";
		cin >> choice;
		if (toupper(choice) == 'Y')
		{

			file.open("clients.txt", ios::out);

			clientToBeUpdated = ClientInfo(myvec, false);
			string line;
			if (file.is_open())
			{
				for (strClient& n : myvec)
				{
					if (accNo == n.accNo)
					{
						n = clientToBeUpdated;
						n.accNo = accNo;


					}
				}

				for (strClient n : myvec)
				{
					line = convertRecordToLine(n, "#//#");
					file << line << endl;
				}
				cout << "Client Updated Successfully!";
			}
		}
	}

	cout << "press any key to go back to main menue...";
	system("pause>0");
}

void FindClients()
{
	system("cls");

	string accNo;
	cout << "Enter account number?";
	cin >> accNo;
	FindClientWithAccountNumber(accNo);
	cout << "press any key to go back to main menue...";
	system("pause>0");
}

//###///###//##//##//##
void showTransactionsMenue()
{
	system("cls");
	cout << "=========================\n";
	cout << "Transactions Menue screen\n";
	cout << "=========================\n";

	cout << "[1] Deposit\n";
	cout << "[2] Withdraw\n";
	cout << "[3] Total Balances\n";
	cout << "[4] Main Menue\n";
}



void SaveDataToFile(vector<strClient> myvec)
{
	fstream file;
	file.open("clients.txt", ios::out);
	string line;
	if (file.is_open())
	{
		for (strClient n : myvec)
		{
			line = convertRecordToLine(n, "#//#");
			file << line << endl;
		}
	}
}


void ShowTotalBalances()
{
	cout << "=====================\n";
	cout << "Transacations-: Total Balances\n";
	cout << "=====================\n";
	vector<strClient> myvec = loadClient("clients.txt");
	double totalBalances = 0;

	for (strClient n : myvec)
	{
		totalBalances = totalBalances + n.balance;
	}

	ShowClientsList(true);
	cout << "\n\t\t Total Balance: " << totalBalances << endl;

	cout << "press any key to go back to main menue...";
	system("pause>0");


}


void TakeFromBalance(string accNo)
{
	vector<strClient> myvec = loadClient("clients.txt");
	double balance;
	char confirm;
	do
	{
		cout << "Enter balance that you want to withdraw?";
		cin >> balance;
		if (balance < 0) {
			cout << "you cant withdraw negative balance! retry";
		}
	} while (balance < 0);
	for (strClient& n : myvec)
	{
		if (n.accNo == accNo)
		{
			if (n.balance - balance < 0)
			{
				cout << "The amount that you want to draw is out of the total balance range in your account!\nProcess Terminated! " << endl;
				cout << "press any key to go back to main menue...";
				system("pause>0");
				break;
			}
			n.balance = n.balance - balance;
			cout << balance << "will be taken withdrawn from your account\nTotal amount will be " << n.balance << " press Y to confirm? : ";
			cin >> confirm;
			break;
		}
	}
	if (toupper(confirm) == 'Y')
	{
		SaveDataToFile(myvec);
	}
	else
	{
		cout << "Process terminated!" << endl;
	}

	cout << "press any key to go back to main menue...";
	system("pause>0");

}

void withdraw()
{
	string accNo;
	cout << "Enter account Number: ";
	cin >> accNo;

	if (FindClientWithAccountNumber(accNo))
	{
		TakeFromBalance(accNo);
	}
	else
	{
		cout << "press any key to go back to main menue...";
		system("pause>0");
	}
}
void showWithdraw()
{
	system("cls");
	cout << "=====================\n";
	cout << "Transacations-: Withdraw\n";
	cout << "=====================\n";
	withdraw();
}



void AddBalanceToClient(string accNo)
{
	vector<strClient> myvec = loadClient("clients.txt");
	double balance;
	char Confirm;
	do
	{
		cout << "Enter deposit amount: ";
		cin >> balance;
		if (balance < 0) { cout << "deposit balance can't be negative try again!\n" << endl; }
	} while (balance < 0);



	for (strClient& n : myvec)
	{
		if (n.accNo == accNo)
		{
			n.balance = n.balance + balance;
			cout << balance << "will be added to your account\nTotal amount will be " << n.balance << " press Y to confirm? : ";
			break;
		}
	}
	cin >> Confirm;
	if (toupper(Confirm) == 'Y')
	{
		SaveDataToFile(myvec);
		cout << "Deposit Successful!";
	}
	else
	{
		cout << "Process is terminated..." << endl;
	}
	cout << "press any key to go back to main menue...";
	system("pause>0");

}

void Deposit()
{
	string accNo;
	cout << "Enter account Number: ";
	cin >> accNo;

	if (FindClientWithAccountNumber(accNo))
	{
		AddBalanceToClient(accNo);
	}
	else
	{
		cout << "press any key to go back to main menue...";
		system("pause>0");
	}
}

void ShowDepositMenue()
{
	system("cls");
	cout << "=====================\n";
	cout << "Transacations-: Deposit\n";
	cout << "=====================\n";

	Deposit();
}

void Transactions()
{
	system("cls");

	short choice;
	do
	{
		showTransactionsMenue();
		cout << "Choose what you want to do? 1 to 4? ";
		cin >> choice;

		switch (choice)
		{
		case enTransactionChoice::eDeposit:
			ShowDepositMenue();
			break;
		case enTransactionChoice::eWithdraw:
			showWithdraw();
			break;
		case enTransactionChoice::eTotalBalances:
			ShowTotalBalances();
			break;
		case enTransactionChoice::eMainMeunue:
			break;

		}

	} while (choice != enTransactionChoice::eMainMeunue);
}


void PrintAccessDenied()
{
	system("cls");
	cout << "___________________________________________" << endl;
	cout << "Access Deinied,\nYou Don't Have Permission To Do this\nPlease Contact Your Admin\n ";
	cout << "___________________________________________" << endl;

	cout << "Press Any Key To Go Back TO Main Menu....";
	system("pause>0");
}



void MainMenu(int UserPremission)
{
	int choice;

	do
	{
		MainMenueMssg(choice);
		switch (choice)
		{

		case enClientChoice::ShowClientList:
			if (checkPermission(UserPremission, enUserPermission::usrEshowClientList) )
			{
				ShowClientsList();
			}
			else
			{
				PrintAccessDenied();
			}
			break;
		case enClientChoice::AddNewClient:
			if (checkPermission(UserPremission, enUserPermission::userEAddNewClient))
			{
				AddNewClients();
			}
			else
			{
				PrintAccessDenied();
			}
			break;
		case enClientChoice::DeleteClient:
			if (checkPermission(UserPremission, enUserPermission::userEDeleteClient))
			{
				DeleteClients();
			}
			else
			{
				PrintAccessDenied();
			}
			break;
		case enClientChoice::UpdateClient:
			if (checkPermission(UserPremission, enUserPermission::userEUpdateClient))
			{
				UpdateClientInfo();
			}
			else
			{
				PrintAccessDenied();
			}
			break;
		case enClientChoice::FindClient:
			if (checkPermission(UserPremission, enUserPermission::userEFindClient))
			{
				FindClients();
			}
			else
			{
				PrintAccessDenied();
			}
			break;
		case enClientChoice::eTransactions:
			if (checkPermission(UserPremission, enUserPermission::userETransactions))
			{
				Transactions();
			}
			else
			{
				PrintAccessDenied();
			}
			break;
		case enClientChoice::enManageUsers:
			if (checkPermission(UserPremission, enUserPermission::userEManageUsers))
			{
				ManageUsers(UserPremission);
			}
			else
			{
				PrintAccessDenied();
			}
		case enClientChoice::enLogOut:
			Login();
		}


	} while (choice != enClientChoice::enLogOut);


}

void showLoginScreen()
{
	cout << "----------------------------------------------\n";
	cout << "\t\t Log in Screen\n";
	cout << "----------------------------------------------\n";
}

//##//##//##//##

void UpdateUser(int UserPermission)
{
	system("cls");
	char choice;
	cout << "_____________________________________" << endl;
	cout << "Update User Screen" << endl;
	cout << "_____________________________________" << endl;
	string username;
	cout << "Enter User Name: ";
	cin >> username;

	if (username == "Admin")
	{
		cout << "You Can't Change The Previlages Of The Admin!" << endl;
		cout << "Press Any Key To Return To Manage Users Screen...";
		system("pause>0");
		return;
	}


	strUser user = ReturnUserByUsername(username);
	PrintUserInfoCard(user);

	cout << "Are you sure you want to update this user? Y/N: ";

	cin >> choice;
	if (toupper(choice) == 'Y')
	{
		AddNewUser(UserPermission, false, username);
	}
}





void FindUser()
{
	system("Cls");

	cout << "_____________________________\n";
	cout << "\tFind User Screen\n";
	cout << "_____________________________\n";

	string username;
	cout << "Enter UserName: ";
	cin >> username;
	vector<strUser> myvec=loadUsers("users.txt");
	for (strUser n : myvec)
	{
		if (n.UsrName == username)
		{
			PrintUserInfoCard(n);
		}
	}
	cout << endl << endl;
	cout << "Press Any Key To Go Back To Manage Users Screen";
	system("pause>0");
	return;
}


void MarkUserForDeletion(vector<strUser>& myvec,string username)
{
	for (strUser& n : myvec)
	{
		if (n.UsrName == username)
		{
			n.isMarked = true;
			return;
		}
	}
}

void DeleteUser(int userPermission)
{
	system("cls");
	string username;
	char choice='\0';
	cout << "Please Enter User Name: ";
	cin >> username;

	vector<strUser> myvec = loadUsers("users.txt");
	MarkUserForDeletion(myvec,username);
	fstream File;
	string line;


	if (!isUserExist(username))
	{
		cout << "User with ["<<username<<"] is not found ! Process Terminated.\n";
		cout << "Press Any Key to go to Manage Users Screen Menu";
		system("pause>0");
		return;
	}


	if (username == "Admin")
	{
		cout << "You Can't Delete The User Admin!\n";
		cout << "Press Any Key to go to Manage Users Screen Menu";
		system("pause>0");
		return;
	}

	for (strUser& n : myvec)
	{
		if (n.isMarked == true)
		{
			PrintUserInfoCard(n);
			cout << "\n\nAre You Sure You Want To Delete This User? Y/N ";
			cin >> choice;
			break;
		}
	}

	if (toupper(choice) == 'Y' )
	{
		File.open("users.txt", ios::out);
		if (File.is_open())
		{
			for (strUser& n : myvec)
			{
				if (n.isMarked == true)
				{
					continue;
				}
				line = convertUserRecordToLine(n, "#//#");
				File << line << endl;
			}
			cout << "User Deleted Successfully!" << endl;
		}
		
	}

	myvec = loadUsers("users.txt");
	cout << "Press Any Key to go to Manage Users Screen Menu";
	system("pause>0");
	return;
}


string convertUserRecordToLine(strUser user, string del)
{
	return user.UsrName + del + to_string (user.password) + del + to_string (user.permission);
}


bool checkPermission(int userPermission,int actualPermission)
{
	return (userPermission & actualPermission) == actualPermission;
}
int ReadUserPermission()
{
	int currPermissions = 0;
	char choice;
	cout << "Do you want to give to: " << endl;
	cout << "Show Client List? y/n ";
	cin >> ws >> choice;

	if (toupper(choice) == 'Y')
	{
		currPermissions = currPermissions | enUserPermission::usrEshowClientList;

	}


	cout << "Add New Client? y/n ";
	cin >> ws >> choice;
	if (toupper(choice) == 'Y')
	{
		currPermissions = currPermissions | enUserPermission::userEAddNewClient;
	}

	cout << "Delete Client? y/n ";
	cin >> ws >> choice;
	if (toupper(choice) == 'Y')
	{
		currPermissions = currPermissions | enUserPermission::userEDeleteClient;
	}

	cout << "Update Client? y/n ";
	cin >> ws >> choice;
	if (toupper(choice) == 'Y')
	{
		currPermissions = currPermissions | enUserPermission::userEUpdateClient;
	}

	cout << "Find Client? y/n ";
	cin >> ws >> choice;
	if (toupper(choice) == 'Y')
	{
		currPermissions = currPermissions | enUserPermission::userEFindClient;
	}

	cout << "Transactions? y/n ";
	cin >> ws >> choice;
	if (toupper(choice) == 'Y')
	{
		currPermissions = currPermissions | enUserPermission::userETransactions;
	}

	cout << "Manage Users? y/n ";
	cin >> choice;
	if (toupper(choice) =='Y')
	{
		currPermissions = currPermissions | enUserPermission::userEManageUsers;
	}

	return currPermissions;
}


bool isUserExist(string userName)
{
	vector<strUser> myvec = loadUsers("users.txt");
	for (strUser& n : myvec)
	{
		if (n.UsrName == userName)
		{
			return true;
		}
	}
	return false;
}


void AddNewUser(int permission,bool isNewUser=true,string UserName="")
{
	
	
	strUser user;
	string line;
	fstream file;
	vector<strUser> myvec = loadUsers("users.txt");
	char UserChoice;

	do
	{
		if (isNewUser)
		{
			system("cls");
			cout << "----------------------------------------------\n";
			cout << "\t\t Add New User Screen\n";
			cout << "----------------------------------------------\n";
			cout << "Enter User Name: ";
			getline(cin >> ws, user.UsrName);
			while (isUserExist(user.UsrName) == true)
			{
				cout << "User With [" << user.UsrName << "] already exists, Enter Another User Name? ";
				getline(cin >> ws, user.UsrName);

			}
		}

		else
		{
			user.UsrName = UserName;
		}
		cout << "Enter Password: ";
		cin >> user.password;

		cout << "Do you want to give full access y/n? ";
		cin >> UserChoice;

		if (UserChoice == toupper('y'))
		{
			user.permission = -1;
		}
		else
		{
			user.permission = ReadUserPermission();
		}

		myvec = loadUsers("users.txt");
		myvec.push_back(user);


		file.open("users.txt", std::ios::out);
		if (file.is_open())
		{
			for (strUser& n : myvec)
			{
				line = convertUserRecordToLine(n, "#//#");
				file << line << endl;
			}
			cout << "User Added Successfully!, Do You Want To Add More Users";
		}
		cin >> ws >> UserChoice;
	} while (toupper(UserChoice) == 'Y');

	cout << "Press Any Key to go to Manage Users Screen Menu";
	system("pause>0");
	return;

}
void ListUsers()
{
	system("cls");
	vector<strUser> myvec = loadUsers("users.txt");
	cout << "\t\t\t\t Users list (" << myvec.size() << ") Client(s).\n";
	cout << "_____________________________________________________________________________" << endl;
	cout << "| " << setw(15) << "User Name"
		<< "| " << setw(10) << "Password"
		<< "| " << setw(20) << "Permissions"
		<< " |" << endl;
	cout << "______________________________________________________________________________" << endl;
	

	for (int i = 0; i < myvec.size(); ++i)
	{
		cout << "| " << setw(15) << myvec[i].UsrName
			<< "| " << setw(10) << myvec[i].password
			<< "| " << setw(20) << myvec[i].permission
			<< " |" << endl;

	}

	cout << "Press Any Key to go to users menu";
	system("pause>0");
}


void ShowUsersScreen()
{
	system("cls");
	cout << "===========================\n";
	cout << "\t\t Manage Users Screen\n";
	cout << "===========================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update user.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu\n";
	cout << "===========================\n";
	cout << "Choose what do you want to do ? [1 to 6]: ";

}
void ManageUsers(int UserPermission)
{
	
	int choice;
	while (true)
	{
		ShowUsersScreen();
		cin >> choice;
		switch (choice)
		{
			case enUsersChoice::eListUsers:
			{
				ListUsers();
				break;
			}
			case enUsersChoice::eAddNewUser:
			{
				AddNewUser(UserPermission);
				break;
			}
			case enUsersChoice::eDeleteUser:
			{
				DeleteUser(UserPermission);
				break;
			}
			case enUsersChoice::eUpdateUser:
			{
				UpdateUser(UserPermission);
				break;
			}
			case enUsersChoice::eFindUser:
			{
				FindUser();
				break;
			}
			case enUsersChoice::eMainMenue:
			{
				MainMenu(UserPermission);
				break;
			}
		}
	}
	

}



strUser ConvertUserLineToRecord(string line)
{
	strUser user;
	string separator = "#//#";
	int count = 0;

	vector<string> token = splitString(line, "#//#"); //tokens 
	user.UsrName = token[0]; //account number
	user.password = stoi(token[1]); //pincode
	user.permission = stoi(token[2]);
	
	return user;
}

vector<strUser> loadUsers (string filename) //getting client from a file
{
	vector<strUser> myvec;
	strUser user;
	fstream myfile;
	string line;
	myfile.open(filename, ios::in); //open file in appending mode
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			user = ConvertUserLineToRecord(line);
			myvec.push_back(user);
		}
	}
	myfile.close();
	return myvec;
}

bool FindUserByUserNameAndPassword(string username, short password)
{
	vector<strUser> myvec = loadUsers("users.txt"); //load vector
	for (strUser& n : myvec)
	{
		if ( n.UsrName == username && n.password == password)
		{
			return true;
		}
	}
	return false;

}
void PrintUserInfoCard(strUser user ) 
{
	cout << "The Following Are The User Details: \n";
	cout << "_________________________\n";
	cout << "UserName: " << user.UsrName << endl;
	cout << "Password: " << user.password << endl;
	cout << "Permission: " << user.permission << endl;
	cout << "_________________________\n";

}


strUser ReturnUserByUserNameAndPassword(string username, short password)
{
	vector<strUser> myvec = loadUsers("users.txt"); //load vector
	for (strUser& n : myvec)
	{
		if (n.UsrName == username && n.password == password)
		{
			return n;
		}
	}
	return { "",-122,-404 };
}



strUser ReturnUserByUsername(string username)
{
	vector<strUser> myvec = loadUsers("users.txt"); //load vector

	if (isUserExist(username))
	{
		for (strUser& n : myvec)
		{
			if (n.UsrName == username)
			{
				return n;
			}
		}
	}

	return { "",-122,-404 };
}



void Login()
{
	system("cls");
	string username;
	short password;
	showLoginScreen();
	while(true)
	{
		cout << "Enter User Name? ";
		cin >> username;
		cout << "Enter Password? ";
		cin >> password;

		if (FindUserByUserNameAndPassword(username, password))//result is true
		{
			strUser user = ReturnUserByUserNameAndPassword(username, password);
			MainMenu(user.permission);
		}
		else
		{
			system("cls");
			showLoginScreen();
			cout << "Invalid Username/password!" << endl;
		}

	}
	

}


int main()
{
	Login();
}

