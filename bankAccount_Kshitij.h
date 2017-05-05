/*
Code written and developed by kshitij Chhatwani
*/

#pragma once
#ifndef BANKACCOUNT_KSHITIJ_H
#define BANKACCOUNT_KSHITIJ_H
#include "account_kshitij.h"
#include<string>
using namespace std;

class bankAccount :public Account   //public inheritance from class 'account'
{
public:
	//member functions 
	bankAccount();                               // Constructor
	~bankAccount();                              // Destructor
	float DisplayBalance();                      // Display the Balance in the account
	void deposit(double);
	void withdraw(double);
	void BankHistory();
	string getDate();
	virtual float getBalance();
	virtual void setBalance(double);
};
#endif



