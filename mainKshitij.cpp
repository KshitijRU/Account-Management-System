/*
Code written and developed by kshitij Chhatwani
*/

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif

#include "mex.h"
#include<Engine.h>

#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<sstream>
#include<ctime>
#include<time.h>

#include "account_kshitij.h"
#include "stockAccount_Kshitij.h"
#include "bankAccount_Kshitij.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmex.lib")
#pragma comment(lib, "libeng.lib") 

int main()
{

	Engine *ep; //creating an engine
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		std::cout << "Error: NOT FOUND!" << endl;
		exit(1);
	}
	int choice = 999, s_choice = 999, b_choice = 999;
	float deposit, withdraw;
	int length = 0;
	int value = 0;
	//arrays for plotting
	double array_1[100]; 
	double array_2[100];

	// Objects of BankAcount and StockAccount
	StockAccount stk_obj; 
	bankAccount bank_obj;

	//fstream class file object
	fstream myfile;
	string line;

	float sub;
	//copying the cash balance from the text file that has the closing value from previous run
	myfile.open("cash_balance.txt"); 
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			istringstream s(line);
			while (s >> sub)
			{
				Account::cash_balance = sub;
			}
		}
	}
	else
		cout << "Error in opening the file\n";

	
	//updating the stocks from previous transactions
	stk_obj.update_stocks(); 
	//priting the current portfolio
	stk_obj.current_portfolio(); 
								 
	while (choice != 3)
	{
		cout << "Welcome to the Account Management System.\n";
		cout << "Please select an account to access: \n";
		cout <<" 1. Stock Portfolio Account \n ";
		cout <<" 2.Bank Account \n";
		cout <<" 3.Exit";
		cout << "\nOption: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout <<"\nStock Portfolio Account \n";
			cout <<"Please select an option : \n ";
			cout <<"1. Display the price for a stock symbol \n";
			cout <<"2. Display the current portfolio \n";
			cout <<"3. Buy shares \n";
			cout <<"4. Sell shares \n";
			cout <<"5. View a graph for the portfolio value \n";
			cout <<"6. View transaction history \n";
			cout <<"7. Return to previous menu \n";
			cout << "\nOption: ";
			cin >> s_choice;

			while (s_choice != 7)
			{
				switch (s_choice)
				{
				case 1:
					stk_obj.DisplayStock();                           //function to display current value of stock
					break;
				case 2:
					stk_obj.sort_wrapper();                           //function for sorting the portfolio
					stk_obj.current_portfolio();
					break;
				case 3:
					stk_obj.BuyShares();                             //function to buy shares
					break;
				case 4:
					stk_obj.sell_shares();                          //function to sell shares
					break;
				case 5:                                             //for plotting the graph of changing portfolio 
				{

					fstream file("total_portfolio_value.txt", ios::in);
					string line;
					while (getline(file, line))
					{
						istringstream s(line);
						double no;
						while (s >> no)
						{
							array_1[length] = no;
							array_2[value] = length;
							length = length + 1;
							value = value + 1;
						}
					}
					for (int i = 0; i < length; i++)
					{
						cout << (double)array_1[i] << endl;
					}
					for (int j = 0; j < length; j++)
					{
						cout << (double)array_2[j] << endl;
					}
					mxArray *A = NULL;
					A = mxCreateDoubleMatrix(1, length, mxREAL);
					memcpy((void *)mxGetPr(A), (void *)array_1, sizeof(array_1));
					engPutVariable(ep, "x", A);
					mxArray *B = NULL;
					B = mxCreateDoubleMatrix(1, length, mxREAL);
					memcpy((void *)mxGetPr(B), (void *)array_2, sizeof(array_2));
					engPutVariable(ep, "y", B);
					engEvalString(ep, "A1=y;");
					engEvalString(ep, "B1=x;");
					engEvalString(ep, "plot(A1,B1);");
					engEvalString(ep, "xlabel('Number of transactions');");
					engEvalString(ep, "ylabel('Total portfolio value');");
					engEvalString(ep, "title('Change in total portfolio value');");
				}
				break;
				case 6:
					stk_obj.transac_history();
					break;
				case 7:
					break;
				default:
					cout << "Please enter a number in between 1 and 7" << endl;
					break;
				}
				cout <<"\nStock Portfolio Account \n";
				cout << " Please select an option : \n";
				cout <<" 1. Display the price for a stock symbol"<<endl;
				cout <<" 2. Display the current portfolio \n";
				cout <<" 3. Buy shares \n";
				cout <<" 4. Sell shares \n";
				cout <<" 5. View a graph for the portfolio value\n";
				cout <<" 6. View transaction history \n";
				cout <<" 7. Return to previous menu \n";
				cout << "\nOption: ";
				cin >> s_choice;
			}
		}
		break;


		case 2:
		{
			cout <<"\nBank Account \n";
			cout <<" Please select an option : \n";
			cout <<" 1. View account balance \n";
			cout <<" 2. Deposit money \n";
			cout <<" 3. Withdraw money\n";
			cout <<" 4. Print out history \n";
			cout<<"  5. Return to previous menu\n" << endl;
			cout << " Option: ";
			cin >> b_choice;
			while (b_choice != 5)
			{
				switch (b_choice)
				{
				case 1:

					bank_obj.DisplayBalance();
					break;
				case 2:
					cout << "Please enter the amount you wish to deposit: ";
					cin >> deposit;
					bank_obj.deposit(deposit);
					break;
				case 3:
					cout << "Please enter the amount you wish to withdraw: ";
					cin >> withdraw;
					bank_obj.withdraw(withdraw);
					break;
				case 4:
					bank_obj.BankHistory();       
					break;
				case 5:
					break;
				default:
					cout << "Please enter a number in between 1 and 5" << endl;
					break;
				}
				cout <<"\nBank Account \n";
				cout <<" Please select an option : \n";
				cout <<" 1.View account balance \n";
				cout <<" 2.Deposit money \n";
				cout <<" 3.Withdraw money\n";
				cout <<" 4. Print out history \n";
				cout <<" 5. Return to previous menu" << endl;
				cout << "\nOption: ";
				cin >> b_choice;
			}
		}
		break;


		case 3:
			break;
		default:
			cout << "Please enter a number in between 1 and 3" << endl;
			break;
		}

	}

	stk_obj.sort_wrapper();
	stk_obj.current_portfolio();
	float tpf_value = StockAccount::total_portfolio; 
	ofstream fout3;
	fout3.open("total_portfolio_value.txt", ios::app);
	fout3 << tpf_value << endl;
	fout3.close();

	ofstream fout2;
	fout2.open("cash_balance.txt"); 
	fout2 << "$" << Account::cash_balance << "\t" << bank_obj.getDate() << "\t" << stk_obj.getTime() << endl;
	fout2.close();

	system("pause");
	return 0;
}