/* Program code developed by Kshitij chhatwani 
   Main file : to run the program 
*/

#include<iostream>
#include<fstream>
using namespace std;

// Header files of the StockAccount, BankAccount and Account class respectively.
#include"Account.h"
#include "StockAccount.h"
#include"BankAccount.h"

void firstoption();
void stockoption();
void bankoption();

// User Navigation Listings Functions
void firstoption()
{
	int option;
	cout << " Please select an option to access : " << endl;
	cout << " 1. Stock Portfolio Account " << endl;
	cout << " 2. Bank Account " << endl;
	cout << " 3. Exit " << endl;
	cin >> option;
	switch (option)
	{
	case 1:
		stockoption();
		break;
	case 2: cout << " Bank Account " << endl;
		bankoption();
		break;
	default: cout << " Invalid Option !!!" << endl;
	}

}

void stockoption()
{
	int option;
	StockAccount S;
	cout << " Please select an option : " << endl;
	cout << " 1. Display price for a stock symbol " << endl;
	cout << " 2. Display the current portfolio " << endl;
	cout << " 3. Buy Shares " << endl;
	cout << " 4. Sell Shares " << endl;
	cout << " 5. View a graph for the portfolio value " << endl;
	cout << " 6. View Transaction history " << endl;
	cout << " 7. Return to previous menu " << endl;
	cin >> option;
	switch (option)
	{
	case 1: S.DisplayPrice();
		break;
	/*case 2: S.DisplayCurrentPortfolio();
		break;
	case 3: S.BuyShares();
		break;
	case 4: S.SellShares();
		break;
	case 5: S.viewGraph();
		break;
	case 6: S.TransactionHistory();
		break;
	case 7: firstoption();
		break;*/
	default: cout << " Invalid option !!!" << endl;
	}
}

void bankoption()
{
	int option;
	//Account A;
	BankAccount B;
	double amount = 0.00;
	cout << " Please select an option to access : " << endl;
	cout << " 1. View account balance " << endl;
	cout << " 2. Deposit Money  " << endl;
	cout << " 3. Withdraw Money  " << endl;
	cout << " 4. Print out History  " << endl;
	cout << " 5. Return to previous menu  " << endl;
	cin >> option;
	switch (option)
	{
	case 1: B.displayBalance();
		break;
	case 2:
		B.DepositMoney();
		break;
	case 3:
		B.WithdrawMoney();
		break;
	case 4: B.DisplayHistory();
		break;
	case 5: firstoption();
		break;
	default: cout << " Invalid Option " << endl;
	}
}

// Start of Main 
void main()
{
	cout << " Welcome to Account Management System " << endl;
	char ch = 'y';
	while (ch == 'y' || ch == 'Y')
	{
		// Calling the User Navigation options 
		firstoption();
		cout << " Do you want to continue ?" << endl;
		cin >> ch;
	}

	


}// End of main()