/*
Code written and developed by kshitij Chhatwani
*/

#pragma once
#ifndef ACCOUNT_KSHITIJ_H
#define ACCOUNT_KSHITIJ_H

class Account //abstract base class
{
public:
	Account(); //constructor
	static double cash_balance;

	//pure virtual functions since the Base Class Account is an abstract class as stated in the Question
	virtual float getBalance() = 0;
	virtual void setBalance(double) = 0;
};
#endif // !ACCOUNT_KSHITIJ_H
