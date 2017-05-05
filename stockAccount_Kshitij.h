
#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef STOCKACCOUNT_KSHITIJ_H
#define STOCKACCOUNT_KSHITIJ_H

#include "account_kshitij.h"
#include<string>
using namespace std;
/*
Code written and developed by kshitij Chhatwani
*/


class ListNode                                                    //implementation of list nodes
{
	friend class StockAccount;                                    //declaring stockaccount as friend
public:                                                           //pubic member functions
	ListNode(string& name, int numb)
		:symbol(name), number(numb)
	{
		this->next = NULL;
		this->prev = NULL;
	}

private:
	string symbol;
	int number;
	ListNode *next;                                  
	ListNode *prev;
};

class StockAccount :public Account //public inheritance from class account
{
public:
	StockAccount();
	static double total_portfolio;
	void DisplayStock();
	void current_portfolio();
	void BuyShares();
	void addNode(ListNode *);
	void sell_shares();
	void delNode(string node);
	void transac_history();
	void update_stocks();
	string getTime();

	//functions that constitute the merge sort operation
	ListNode *split(ListNode *);
	ListNode *merge_sort(ListNode *);
	ListNode *sortList(ListNode *first, ListNode *second);
	void sort_wrapper();
	virtual float getBalance();
	virtual void setBalance(double);
private:
	ListNode *firstPtr;                                 //pointer to first node
	ListNode *lastPtr;                                 //pointer to second node
	int size_list;                                    //size of the doubly linked list
};
#endif 