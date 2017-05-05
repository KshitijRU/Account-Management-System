#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<string>
#include<string.h>
using std::string;
class Account
{
	double balance;
public:
	Account();                     // Constructor of class Account
	//double closingBalance();       // return the balance present in the account on user's request at the end of the day.
	double getCashBalance();           // return the balance present in a user's account.
	void setCashBalance(double amount); // Set the cash balance
	void delCashBalance(double amount); // Subtract cash balance on accountof a withdrawl.
	void displayBalance();            // display the balance present in the account.
	void TransactionHistory(string event, double amount);   // Keep track of transaction history
	string GetDate();
	void printHistory();
};
#endif // !ACCOUNT_H

