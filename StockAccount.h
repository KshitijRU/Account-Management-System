#pragma once
#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H

#include"Account.h"

// Class StockAccount inherits from class Account
class StockAccount :public Account
{
public:
	StockAccount();                      // To intialise the balance to $10,000
	void DisplayPrice();                 // To display the price of a Stock
	void DisplayCurrentPortfolio();      // To display the current portfolio
	void BuyShares();                    // To buy shares
    void SellShares();                   // To sell shares
	void viewGraph();                    // To view graph for the protfolio value
	void TransactionHistory();           // To view the transaction history
};
#endif // !STOCKACCOUNT_H

