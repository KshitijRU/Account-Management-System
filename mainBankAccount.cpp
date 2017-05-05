/* Developed by kshitij chhawani 
   BankAccount.cpp file 
*/

#include<iostream>
#include<fstream>
using namespace std;

// Include the header file containing BankAccount class
#include "BankAccount.h"
#include "Account.h"

// Function Definition 
BankAccount::BankAccount()
{
	Account();
}

// Prints out the current account balance
void BankAccount::CurrentBalance()
{
	//cout << " You have  $" << balance << " in your bank account " << endl;
	Account::displayBalance();
}

// Function to deposit Money in the Account.
void BankAccount::DepositMoney()
{
	double amount;
	cout << " Enter amount to be withdrawn : ";
	cin >> amount;
	cout << endl;
	cout << " The amount to be deposited is : $"<<amount<<endl;
	Account::setCashBalance(getCashBalance()+amount);
	Account::TransactionHistory("DEPOSIT", amount);
}

// Function to withdrw Money from the Account
void BankAccount::WithdrawMoney()
{
	double amount;
	cout <<" The amount to be withdrawn is :"<<endl;
	cin >> amount;
	if (amount > getCashBalance())
	{
		cout << " Withdrawl of $" << amount << " cannot be completed since it is higher than the Account Balance. Sorry for the Incovienience " << endl;
	}
	else
	{
		Account::delCashBalance(amount);
		Account::TransactionHistory("WITHDRAW", amount);
	}
}

// Function that displays the entire transaction history.
void BankAccount::DisplayHistory()
{
	Account::printHistory();

}
