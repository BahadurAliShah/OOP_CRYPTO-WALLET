#include"HashedAccountManager.h"
#include<stdlib.h>
int MainMenu();
int SubMenu(string);
bool Operations(AccountManager*, int,string);
void Header();
int main(){
	Account miner("miner", "123");//default Account
	AccountManager manager1;
	HashedAccountManager manager2;
	manager1.LoadFromFile("manager1.docx");	//to Load preious data of manager 1
	manager2.LoadFromFile("manager2.docx");	//to load previoud data of manager 2
	manager1.AddAccount(miner);
	manager2.AddAccount(miner);
	Header();
	int first = 0;	//for switch expression
	bool iterator = true;	//iterator for coming loop
	while (iterator) {	/*loop is used to display main menu multiple times */
		switch (first) {
		case 1:	/*For manager 1*/
		{
			bool c1iterator = true;	/*iterator for coming loop which is used to display Account Manager Menu multiple times according to user choice*/
			while (c1iterator) {
				c1iterator = Operations(&manager1, SubMenu("Account Manager"), "Account Manager");	/*if Operations() will return 1 which is used for back option then loop will iterate and when it will return 0 which is used for main menu option the loop will stop and default case will execute*/
				first = 0;
			}
			break;
		}
		case 2:	/*For manager 2*/
		{
			bool c1iterator = true;
			while (c1iterator) {
				c1iterator = Operations(&manager2, SubMenu("Hashed Account Manager"), "Hashed Account Manager");
				first = 0;
			}
			break;
		}
		case 3:	/*Exit*/
			iterator = false;/*it will stop the loop*/
			break;
		default:
			first = MainMenu();	/*first is assigning to option selected by user in Main Menu*/
		}
	}
	manager1.WriteToFile("manager1.docx");	/*to maintain record of manager 1*/
	manager2.WriteToFile("manager2.docx");	/*to maintain record of manager 2*/
}

void Header() {
	cout << "\n=========================================================================================\n";
	cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n" << "|\t\t\t\t  Bank Management System\t\t\t\t|\n" << "|\t\t\t\t\t\t\t\t\t\t\t|\n"
		<< "=========================================================================================\n";

	cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n" << "|\t\t\t\tMade By: Syed Bahadur Ali\t\t\t\t|\n" << "|\t\t\t\t\t\t\t\t\t\t\t|\n"
		<< "|\t\t\t\t    Roll No. 19I-1783\t\t\t\t\t|\n" << "|\t\t\t\t\t\t\t\t\t\t\t|\n"
		<< "=========================================================================================\n";
}
int MainMenu() {
	int selector;
	cout << "| Main Menu:\t\t\t\t\t\t\t\t\t\t|\n" << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
	cout << "| 1. Account Manager\t\t\t\t\t\t\t\t\t|\n" << "| 2. Hashed Account Manager\t\t\t\t\t\t\t\t|\n";
	cout << "| 3. Exit\t\t\t\t\t\t\t\t\t\t|\n";
	cout << "|\t\t\t\t  Select One from Above\t\t\t\t\t|\n";
	bool exception_flag = true;
	while (exception_flag) {
		try {
			cout << "|\t\t\t\t\t    ";
			cin >> selector;	//getting user choice of mainmenu
			if (selector < 1 || selector > 3) {	//there are no more option so exeption is thrown and taking input again
				char exception[] = "You Have Entered an Invalid No. Please select 1 or 2";
				selector = 0;
				throw exception;
			}
			exception_flag = false;
		}
		catch (char exception[]) {
			cout << "|\t\t   " << exception << "\t\t\t|\n";
		}
	}
	cout << "=========================================================================================\n";
	return selector;	//return the user choice
}

int SubMenu(string manager_string) {
	cout << "| MainMenu/" << manager_string << "      \t\t\t\t\t\t\t|\n" << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
	cout << "| 1. Create Account\t\t\t\t\t\t\t\t\t|\n" << "| 2. Make a Transaction\t\t\t\t\t\t\t\t\t|\n"
		<< "| 3. See Transaction Log\t\t\t\t\t\t\t\t|\n" << "| 4. See All Accounts\t\t\t\t\t\t\t\t\t|\n"
		<< "| 5. Back\t\t\t\t\t\t\t\t\t\t|\n" << "|\t\t\t\t  Select One from Above\t\t\t\t\t|\n";
	bool exception_flag = true;
	int selector;
	while (exception_flag) {
		try {
			cout << "|\t\t\t\t\t    ";
			cin >> selector;
			if (selector < 1 || selector > 5) {
				char exception[] = "You Have Entered an Invalid No. Please select from 1 to 5";
				selector = 0;
				throw exception;
			}
			exception_flag = false;
		}
		catch (char exception[]) {
			cout << "|\t\t" << exception << "\t\t|\n";
		}
	}
	cout << "=========================================================================================\n";
	return selector;
}
bool Operations(AccountManager* manager, int second,string string_type) {
		switch (second) {
		case 1: {	//for create Account
			int type;
			bool exception_flag = true;
			cout << "| MainMenu/" << string_type << "/Create Account:      \t\t\t\t\t|\n" << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
			cout << "| 1. BITCOIN\t\t\t\t\t\t\t\t\t\t|\n| 2. ETHER\t\t\t\t\t\t\t\t\t\t|\n" << "| 3. Back\t\t\t\t\t\t\t\t\t\t|\n"
				<< "| 4. MainMenu\t\t\t\t\t\t\t\t\t\t|\n" << "|\t\t       Enter the type of Account you want to create\t\t\t|\n";
			while (exception_flag) {
				try {
					cout << "|\t\t\t\t\t    ";
					cin >> type;	/*taking input for account type*/
					if (type > 4 || type < 1) {
						char exception[] = "You Have Entered an Invalid No. Please select from 1 to 3";
						throw exception;	
					}
					exception_flag = false;
				}
				catch (char exception[]) {
					cout << "|\t\t" << exception << "\t\t|\n";
				}
			}
			cout << "=========================================================================================\n";
			switch (type) {
			case 1:	//For BitcoinAccount
				cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
				cout << "|\t\t";
				manager->CreateAccount(BITCOIN);
				cout << "\t\t|\n";
				break;
			case 2:	//For Ether Account
				cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
				cout << "|\t\t";
				manager->CreateAccount(ETHER);
				cout << "\t\t|\n";
				break;
			case 3:
				return 1;
			case 4:
				return 0;
			}
			cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
			cout << "=========================================================================================\n";
			break;
		}
		case 2:	/*For Make a Transaction*/
		{
			string sender_public_key, sender_private_key, receiver_public_key;
			double amount;
			bool c2iterator = true;
			while (c2iterator) {
				cout << "| MainMenu/" << string_type << "/Make a Transaction:  \t\t\t\t\t|\n" << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
				cout << "|   Enter Your Public Key:\t\t\t\t\t\t\t\t|\n|\t\t\t\t";
				cin >> sender_public_key;
				cout << "|   Enter your private Key:\t\t\t\t\t\t\t\t|\n|\t\t\t\t";
				cin >> sender_private_key;
				cout << "|   Enter Reciver Public Key:\t\t\t\t\t\t\t\t|\n|\t\t\t\t";
				cin >> receiver_public_key;
				cout << "|   Enter Amount:\t\t\t\t\t\t\t\t\t|\n|\t\t\t\t";
				cin >> amount;
				c2iterator = manager->MakeTransaction(sender_public_key, sender_private_key, receiver_public_key, amount);
				cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
				if (!c2iterator) {
					cout << "|\t  Make Sure That you have correctly Entered the public and private keys\t\t|\n";
				}
				else {
					cout << "|\t\t\t\tCoins Transferred Successfully\t\t\t\t|\n" << "|\t\t\t\t\t\t\t\t\t\t\t|\n";
				}
				cout << "|\t\t\t\t\t\t\t\t\t\t\t|\n" << "|\t\t    if you want more transactions enter 1 otherwise 0\t\t\t|\n|\t\t\t\t\t    ";
				int i;
				cin >> i;
				c2iterator = i;
				cout << "=========================================================================================\n";
			}
			return 1;
		}
			break;
		case 3:	//For See Transaction Log
			cout << "Transaction Log:\n" << manager->ToStringTransactionLog();
			cout << "=========================================================================================\n";
			return 1;
		case 4:	//For See All the Accounts
			cout << "Accounts:\n" << manager->ToStringAccounts();
			cout << "=========================================================================================\n";
			return 1;
		case 5:	//For Back
			return 0;
		}
}