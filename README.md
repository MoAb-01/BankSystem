This is a console-based banking system implemented in C++. It simulates basic operations of a bank, including adding new clients, updating or deleting client information, searching for accounts, and performing transactions like deposits and withdrawals.

All client data is stored in a local file named clients.txt, using a custom delimiter #//#.

✨ Operations

Show all clients

Add new client

Delete client

Update client information

Search for a client by account number

Transactions:

Deposit

Withdraw

View total balances

Manage Users:

Each Banking System user has special Previliages or Rights Where they can or can not access some of the features or the program operations that is pre determined by user using the bitwise logic

✨ Operations


List Users

Add New User

Delete User (Admin User Cant be deleted)

Update User (Admin User Cant be updated)

Find User 

🛠️ Technologies Used
C++17

Standard Template Library (STL): vector, fstream, string, etc.

File-based data storage

📁 File Format (clients.txt)
Each line in the file represents one client, with fields separated by #//#:

swift
Copy
Edit
AccountNumber#//#PinCode#//#ClientName#//#PhoneNumber#//#Balance
Example:

swift
Copy
Edit
12345#//#9876#//#John Doe#//#1234567890#//#1500.50
