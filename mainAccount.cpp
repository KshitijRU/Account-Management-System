/* 
Code developed by Kshitij Chhatwani
*/

#include "Account.h"
#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<time.h>
using namespace std;
using std::string;

Account::Account()
{
	balance = 10000;                   // Initialise the bank balance with $10,000
}
void Account::setCashBalance(double amount)
{
	balance = amount;
}

void Account::delCashBalance(double amount)
{
	balance = balance - amount;
}
void Account::displayBalance()
{
	cout << " You have $" << getCashBalance() << " in your Bank Account currently " << endl;
}

double Account::getCashBalance()
{
	return balance;
}

string Account::GetDate()
{
	time_t seconds;
	seconds = time(NULL);
	tm *timeinfo;
	timeinfo = localtime(&seconds);
	char buf[100];
	strftime(buf, sizeof(buf), "%m/%d/%Y/%X", timeinfo);
	string c = buf;
	return c;
}
void Account::TransactionHistory(string event, double amount)
{
	char str[250];
	_snprintf(str, sizeof(str), "%s\t%.21f\t%s\t%.21f\n", event.c_str(), amount, GetDate().c_str(), getCashBalance());
	ofstream fout;
	fout.open("bank_account_history.txt", ios::app);
	fout << event <<"\t"<<amount<<"\t" <<GetDate()<<"\t"<< balance;
	fout << endl;
	fout.close();
}

void Account::printHistory()
{
	string Event;
	double amount;
	string dat;
	double b;
	ifstream fin;
	fin.open("bank_account_history.txt");
	if (fin.good())
	{
		cout << " Event " << "\t\t" << "Amount " << "\t\t" << " Date " << "\t\t\t" << "Balance " << endl;
		while (fin.eof())//fin >> Event >> amount >> dat >> balance
		{
			cout << Event << "\t" << amount << "\t" << dat << "\t" << b << endl;

		}
	}


}