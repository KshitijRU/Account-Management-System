/*
 Code written and developed by kshitij Chhatwani
 */


// Compiler Suggested - To prevent warnings.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// Header Files
#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<cstdlib>
#include<algorithm>
#include<functional>

#include "stockAccount_Kshitij.h"
using namespace std;

double StockAccount::total_portfolio = 0;      //initializing the portfolio variable

StockAccount::StockAccount()                       //constructor
{
	firstPtr = 0;
	lastPtr = 0;
}

string StockAccount::getTime()                
{
	/* I have used this method instead of the other one because this one only provides the date whereas the other implementation
	   aslo prints the time with the date which I found to be a bit more than needed for a user
	*/
	
	char str[9];
	_strtime_s(str);
	return str;
}

//function to display the value of a stock
void StockAccount::DisplayStock()                       
{
	
	string ticker;
	cout << "Please enter the stock symbol: ";
	cin >> ticker;
	string symbol;
	symbol = ticker;

	// If user enters a ticker in lowercase letters , the command on the next line converts it into a uppercase letter
	std::transform(ticker.begin(), ticker.end(), symbol.begin(), toupper);
	//cout << symbol << endl;

	ifstream fin; //creating a stream object
	string line;
	string search;
	string date;
	double price;
	bool status = false;

	//Randomly select one file to read the stock value
	int i = rand() % 2;
	if (i == 0)
	{
		fin.open("Results_1.txt");
		cout << " File 1 is selected " << endl;
	}
	else
	{
		fin.open("Results_2.txt");
		cout << " File 2 is selected " << endl;
	}
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			istringstream s(line);                                      //constructing an istringstream object( more favourable) over a stringstream object
			while (s >> search >> price)
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
	if (status == false)
	{
		cout << "The symbol you entered is not present in the file. Please enter a valid symbol." << endl;
	}

}

//Function to display the current portfolio
void StockAccount::current_portfolio() 
{
	cout << "Cash balance = $" << cash_balance << "\n";
	ListNode *ptrcurrent = firstPtr;
	string ticker;
	float price;
	int count = 0;
	float mode = 0;
	if (ptrcurrent == 0) 
	{
		cout << "\nNo stocks to display\n";
		return;
	}
	else
	{
		cout << "\nCompanySymbol\tNumber\tPricePerShare\tTotalValue\n";
		while (ptrcurrent != 0)
		{
			ticker = ptrcurrent->symbol;
			count = ptrcurrent->number;
			if (count != 0)
			{
				cout << ticker << "\t\t" << count << "\t";

				ifstream file; 
				string line, sub;

				//Randomly selecting a stock value from either of the results file
				int i = rand() % 2;
				if (i == 0)
				{
					file.open("Results_1.txt");
				}
				else
				{
					file.open("Results_2.txt");
				}
				if (file.is_open())
				{
					while (getline(file, line))
					{
						istringstream iss(line); 
						
						while (iss >> sub >> price)
						{
							if (sub == ticker)
							{
								float sum = count * price;
								cout << "$" << price << "\t\t" << "$" << sum << "\n";
								mode+= sum; 
							}
						}
					}

				}
			}

			ptrcurrent = ptrcurrent->next;
		}
	}
	total_portfolio = mode + cash_balance; 
	cout << "\nTotal portfolio value : $" << total_portfolio << endl;
}

//3.Function to Buy Shares 
void StockAccount::BuyShares() 
{
	string ticker;
	string symbol, search,line,date;
	double price;
	double cost;
	float share_amount;
	time_t seconds;
	seconds = time(NULL);
	struct tm *timeinfo;
	timeinfo = localtime(&seconds);
	bool stock = false;
	bool available = false;

	cout << "Please enter the stock symbol you wish to purchase: " << endl;
	cin >> ticker;
	cout << "Please enter the number of shares you want to purchase: " << endl;
	cin >> cost;
	cout << "Please enter the maximum amount you are willing to pay for each share: " << endl;
	cin >> share_amount;

	symbol = ticker;
	std::transform(ticker.begin(), ticker.end(), symbol.begin(), toupper);
	//cout << " Ticker entered is  : " << symbol << endl;

	ifstream fin; 
	

	//Randomly select one file out of the two given to select a ticker's stock value
	int i = rand() % 2;
	if (i == 0)
	{
		fin.open("Results_1.txt");
		cout << " File 1 is open" << endl;
	}
	else
	{
		fin.open("Results_2.txt");
		cout << " File 2 is open" << endl;
	}
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			istringstream s(line); 

			while (s >> search >> price )
			{
				if (search == symbol)
				{
					available = true;
					// Nw, check if whether user buys the stock at a higher price
					if (share_amount >price)                                             
					{
						cout << "The current value of each share is: $" << price << endl;
						double sum = cost*price;
						if (sum > cash_balance)
						{
							cout << "The transaction failed. You have insufficient funds in your account. Sorry for the incovienience.\n";
						}
						else
						{
							ofstream fout;
							fout.open("stock_transaction_history.txt", ios::app); //append to existing history / log file
							if (fout.is_open())
							{
								fout << "Buy\t";
								fout << symbol << "\t";
								fout << cost << "\t";
								fout << "$" << price << "\t";
								fout<< "$" << sum << "\t";
								fout << getTime() << endl;
								fout.close();
							}
							else
							{
								cout << "The transaction failed. Not able to open file" << endl;
								break;
							}

							ofstream fout2;
							fout2.open("bank_transaction_history.txt", ios::app); //recording the transaction in bank account
							if (fout2.is_open())
							{
								fout2 << "\nWithdraw\t$" << sum << "\t";
							}
							else
							{
								cout << "This transaction could not be recorded. File not found/ not open. Sorry for the incovienience.\n";
							}

							cout << "Buy\t";
							cout << symbol << "\t";
							cout << cost << "\t";
							cout << "$" << price << "\t";
							cout << "$" << sum << endl;

							cash_balance = cash_balance - sum; //to deduct the amount spent in buying from the bank account
							cout << "Cash Balance = $" << cash_balance << endl;

							ListNode *ptr = firstPtr;
							while (ptr != 0)
							{
								if (ptr->symbol == search) //if the node corresponding to the portfolio exists
								{
									ptr->number = cost + ptr->number; //adding the number of shares currently bought to already existing shares
									stock = true;
									break;
								}
								ptr = ptr->next;
							}
							if (stock == false) //if a new stock is bought
							{
								cout << "Created a new node for " << symbol << endl;
								ListNode *newNode = new ListNode(symbol, cost);
								addNode(newNode);
							}
							break;
						}


					}
					else
					{
						cout << "The transaction failed. The maximum amount entered is less than the price of the stock. Please change your quote." << endl;
						break;
					}
				}

			}
		}
	}

	if (available == false)
	{
		cout << "The transaction failed. The stock is not available\n";
	}
}

void StockAccount::addNode(ListNode *newNode) //function to add a new node to a list
{
	if (firstPtr == 0)
	{
		firstPtr = lastPtr = newNode;
	}
	else
	{
		
		newNode->next = firstPtr;
		firstPtr->prev = newNode;
		firstPtr = newNode;
		newNode->prev = NULL;
	}
}

void StockAccount::sell_shares() //function that implements selling of shares
{
	string ticker;
	int num;
	float min_pershare;
	float price;
	bool available = false;
	if (firstPtr != 0)
	{
		cout << "Please enter the ticker symbol of the stock you wish to sell: " << endl;
		cin >> ticker;
		cout << "Please enter the number of shares you wish to sell: " << endl;
		cin >> num;
		cout << "Please enter the minimum amount you want to sell each share of the stock for: " << endl;
		cin >> min_pershare;

		string bigTicker = ticker;
		std::transform(ticker.begin(), ticker.end(), bigTicker.begin(), toupper);
		
		ifstream fin; //creating a stream object
		string line, search;

		//randomly choosing one of the 2 files
		int i = rand() % 2;
		if (i == 0)
		{
			fin.open("Results_1.txt");
		}
		else
		{
			fin.open("Results_2.txt");
		}
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				istringstream s(line); 
			
				while (s >> search >> price)
				{
					ListNode *index = firstPtr;
					while (index != 0)
					{
						// Check if stock exists 
						if (search == bigTicker&&index->symbol == bigTicker) 
						{
							available = true;
							if (index->number<num) 
							{
								cout << "Transaction failed. You do not have enough shares to sell.\n";
							}
							else
							{
								if (min_pershare<price)
								{
									float total = num*price;
									ofstream fout;
									fout.open("stock_transaction_history.txt", ios::app); //recording a transaction in the history file
									if (fout.is_open())
									{
										fout << "Sell\t";
										fout << bigTicker << "\t";
										fout << num << "\t";
										fout << "$" << price << "\t";
										fout << "$" << total << "\t";
										fout << getTime() << endl;
										fout.close();
									}
									else
									{
										cout << "Transaction failed. Unable to open file" << endl;
										break;
									}

									ofstream fo1;
									fo1.open("bank_transaction_history.txt", ios::app); 
									if (fo1.is_open())
									{
										fo1 << "\nDeposit\t\t$" << total << "\t";
									}
									else
									{
										cout << "Cannot record this transaction. File opening failed.\n";
									}

									cout << "Sell\t";
									cout << bigTicker << "\t";
									cout << num << "\t";
									cout << "$" << price << "\t";
									cout << "$" << total << endl;

									cash_balance = cash_balance + total; 
									cout << "Cash Balance=" << cash_balance << endl;

									ListNode *ptr = firstPtr;
									while (ptr != 0)
									{
										if (ptr->symbol == bigTicker)
										{
											ptr->number = ptr->number - num;
											if (ptr->number == 0) 
											{
												delNode(search);
											}
										}
										ptr = ptr->next;
									}
								}
								else
								{
									cout << "The transaction failed. The amount you entered is greater than the price of the stock" << endl;
								}
							}

						}
						index = index->next;
					}
				}
			}
		}
		if (available == false)
		{
			cout << "The transaction failed. The stock you want to sell is not available\n";
		}
	}
	else
		cout << "You have no shares to sell\n";

}

void StockAccount::delNode(string node) //function to delete node when value is zero
{
	cout << "entering into delete\n";
	ListNode *ptr = firstPtr;
	ListNode *temp1 = 0;
	ListNode *temp2 = 0;
	if (firstPtr == 0)
	{
		cout << "Stock not found\n";
	}
	while (ptr != 0) 
	{
		if (ptr->symbol == node)
		{
			break;
		}
		else
		{
			ptr = ptr->next;
		}
	}
	temp1 = ptr->prev; 
	temp2 = ptr->next;
	if (ptr == 0)
	{
		cout << "Stock not found\n";
	}
	else
	{
		if (ptr == firstPtr)
		{
			if (ptr == lastPtr)
			{
				cout << "Selling the last stock you own\n";
				firstPtr = lastPtr = 0;
			}
			else
				firstPtr = firstPtr->next;

		}
		else
		{
			temp1->next = ptr->next;
			temp2->prev = ptr->prev;
		}
		delete ptr;
	}

}

void StockAccount::transac_history()
{
	ifstream myfile;
	string line;
	myfile.open("stock_transaction_history.txt");
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

float StockAccount::getBalance()
{
	return cash_balance;
}

void StockAccount::setBalance(double bal)
{
	cash_balance = bal;
}

void StockAccount::update_stocks() 
{
	bool stock = false;
	ifstream myfile;
	myfile.open("stock_transaction_history.txt");
	string line, event, stock_symb, date;
	int number_shares;
	float value_perShare, total_value;
	while (getline(myfile, line))
	{
		istringstream iss(line);
		if (myfile.eof())
			break;
		while (iss >> event >> stock_symb >> number_shares >> value_perShare >> total_value >> date)
		{

			if (event == "Buy") //if there is a transaction of buy
			{
				
				ListNode *ptr = firstPtr;
				
				while (ptr != 0)
				{
					if (ptr->symbol == stock_symb)
					{
						stock = true;
						ptr->number = number_shares + ptr->number;
						
					}
					else
						stock = false;
					ptr = ptr->next;
				}
				if (stock == false)
				{
					

					ListNode *newNode = new ListNode(stock_symb, number_shares);
					addNode(newNode); 
				}

			}
			else if (event == "Sell")
			{

				ListNode *ptr5 = firstPtr;
				stock = false;
				while (ptr5 != 0)
				{
					if (ptr5->symbol == stock_symb)
					{
						stock = true;
						ptr5->number = ptr5->number - number_shares;
						if (ptr5->number == 0)
						{
							delNode(stock_symb);
						}
					}
					ptr5 = ptr5->next;
				}
				
			}

		}


	}
}

ListNode *StockAccount::sortList(ListNode *first, ListNode *second)
{
	if (!first) 
		return second;
	if (!second) 
		return first;

	ifstream myfile;
	string line, sub;
	float temp_value1, temp_value2;
	

	int i = rand() % 2;
	if (i == 0)
	{
		myfile.open("Results_1.txt");
	}
	else
	{
		myfile.open("Results_2.txt");
	}
	while (getline(myfile, line))
	{
		istringstream s(line); 
		float val;

		while (s >> sub >> val)
		{
			if (sub == first->symbol)
			{
				temp_value1 = val;
				
			}
			if (sub == second->symbol)
			{
				temp_value2 = val;
				
			}
		}

	}

	if (((first->number)*temp_value1) > ((second->number)*temp_value2)) 
	{
	
		first->next = sortList(first->next, second);
		first->next->prev = first;
		first->prev = NULL;
	
		return first;
	}
	else
	{
		
		second->next = sortList(first, second->next);
		
		second->next->prev = second;
		second->prev = NULL;
		
		return second;
	}

}

ListNode *StockAccount::split(ListNode *first) //function to split the DLL recursively
{
	ListNode *temp1 = first;
	ListNode *temp2 = first;
	ListNode *temp;

	while (temp1->next&&temp1->next->next)
	{
		temp1 = temp1->next->next;
		temp2 = temp2->next;
	}
	temp = temp2->next;
	temp2->next = NULL;
	return temp;
}

ListNode *StockAccount::merge_sort(ListNode *firstN) //function to perform merge sort
{
	if (!firstN || !firstN->next)
	{
		return firstN;
	}
	ListNode *second = split(firstN);
	firstN = merge_sort(firstN);
	second = merge_sort(second);

	return sortList(firstN, second);
}

void StockAccount::sort_wrapper() 
{
	if (firstPtr == 0)
	{

	}
	else
	{
		firstPtr = merge_sort(firstPtr);
	}

}