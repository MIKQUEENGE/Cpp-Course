#ifndef _DEPOSIT_H
#define _DEPOSIT_H

#include "campus.h"

#define OVERDRAFT 100		// how much client can overdraft using a deposit card
	
struct DepositInfo {		// the struct store the basic information of the deposit card
	string cardId;   // card id of the card
	string name;     // cardholder's name
	string time;     // card's registration time
};

class DepositCard:public Card {	// inherit class card
	protected:
		DepositInfo info;   // basic information
	public:
		DepositCard();
		DepositCard(DepositInfo);
		DepositCard(DepositCard&);
		virtual void transfer();               
		DepositInfo getInfo();		// return basic info
		virtual void setInfo(DepositInfo);
		virtual void pay(string, int);
		virtual void deposit();
		virtual void inquireInfo();
		friend ostream& operator<<(ostream&, DepositCard&);
		friend istream& operator>>(istream&, DepositCard&);
};

extern DepositCard depositCard[MAX];	// store deposit cards

#endif
