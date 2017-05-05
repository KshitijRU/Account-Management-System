#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<cstdlib>
#include "bankAccount_Kshitij.h"
#include "account_kshitij.h"
using namespace std;

bankAccount::bankAccount() //constructor
{

}

bankAccount::~bankAccount() //destructor
{

}

string bankAccount::getDate() //fucntion to print the date
{
	char dateStr[9];
	_strdate_s(dateStr);
	return dateStr;
}

float bankAccount::DisplayBalance() //function to print the cash_balance
{
	cout << "Your account balance is " << cash_balance << "$\n";
	return cash_balance;
}

void bankAccount::deposit(double amount) //function to deposit money into bank account
{
	cash_balance += amount;
	cout << "Your cash balance after depositing " << amount << "$ is " << cash_balance << "$" << endl;

	//writing the transaction to the history / log file
	ofstream fout;
	fout.open("bank_transaction_history.txt", ios::app);
	if (fout.is_open())
	{
		fout.eof();
		fout << "\nDeposit\t\t$" << amount << "\t" << getDate() << "\t$" << cash_balance << endl;
	}
	else
	{
		cout << "Cannot record this transaction. File opening failed.\n";
	}
}

void bankAccount::withdraw(double amount) //function to withdraw money from the bank account
{
	if (amount<cash_balance)
	{
		cash_balance -= amount;
		cout << "Your cash balance after withdrawal of " << amount << "$ is " << cash_balance << "$" << endl;

		//writing the transaction to the history / log file
		ofstream myfile;
		myfile.open("bank_transaction_history.txt", ios::app);
		if (myfile.is_open())
		{
			myfile << "\nWithdrawal\t$" << amount << "\t" << getDate() << "\t" << cash_balance << endl;
		}
		else
		{
			cout << "Cannot record this transaction. File opening failed.\n";
		}
	}
	else
		cout << "Transaction failed. Insufficient balance\n"; //if balance not sufficient to withdraw
}

void bankAccount::BankHistory() //function to print transactions of the bank account
{
	ifstream myfile;
	string line;
	myfile.open("bank_transaction_history.txt", ios::app);
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			cout << line << endl;
		}
		myfile.close();
	}
	else
		cout << "Error in opening the file.\n";
}

float bankAccount::getBalance()
{
	return cash_balance;
}

void bankAccount::setBalance(double bal)
{
	cash_balance = bal;
}

