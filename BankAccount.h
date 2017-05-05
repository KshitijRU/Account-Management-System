#pragma once
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include "Account.h"

// Class BankAccount inherits from class Account
class BankAccount : public Account
{                 
public:
	BankAccount();                     // Constructor of class BankAccount used to initialise the Balance to $10,000
	void CurrentBalance();             // Prints out the current account balance
	void DepositMoney();   // Function to deposit Money in the Account.
	void WithdrawMoney();  // Function to withdrw Money from the Account
	void DisplayHistory();             // Function to display all transaction history.
	//void writeToFile();                // Writing to file so to save transaction history

};
#endif // !BANKACCOUNT_H

