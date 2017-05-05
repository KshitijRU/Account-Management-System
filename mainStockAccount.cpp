/*  Devloped by Kshitij Chhatwani
    StockAccount.cpp file
*/

#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<ctype.h>
#include<algorithm>
#include<functional>
#include<sstream>
using namespace std;
using std::string;

// Include the class StockAccount header file
#include"StockAccount.h"

// Function Definitions for the functions declared in the StockAccount.h header file

// Constructor called to initialise balance to $10,000
StockAccount::StockAccount()
{
	// Write this to a file
}

// Display the price of the user requested ticker- stock information
void StockAccount::DisplayPrice()
{
	bool status = false;
	string ticker;
	cout << " Enter the Stock ticker you want information for :" << endl;
	cin >> ticker;
	string symbol;
	symbol = ticker;
	std::transform(ticker.begin(), ticker.end(), symbol.begin(), toupper);
	cout << symbol << endl;
	string line;
	string search;
	string date;
	double price;
	ifstream fin;

	int i = rand() % 2;                     // Randomly select Result_1 or Result_2.txt
	if (i == 1)
	{
		fin.open("Result_1.txt");
		cout << " Result_1.txt is selected " << endl;
	}
	else
	{
		fin.open("Result_2.txt");
		cout << " Result_2.txt is selected " << endl;
	}
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			istringstream s(line);
			
			while (s >> search >>price )
			{
				if (search == symbol)
				{
					cout << "\nCompany-Symbol\tPrice Per Share\n";
					cout << "     " << symbol << "\t      $" << price << endl;
					status = true;
					break;
				}
			}
			
		}
	}
	if (status = false)
	{
		cout << " The symbol cannot be found " << endl;
	}

}

void StockAccount::DisplayCurrentPortfolio()
{

}