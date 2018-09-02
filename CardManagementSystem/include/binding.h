#ifndef _BINDING_H
#define _BINDING_H

#include "deposit.h"

class BindingCard:public CampusCard,public DepositCard { 		// inherit CampusCard and DepositCard
	private:
		int campusBindingPos;			// the pos in campusCard[] of the camupus card of the binding card
		int binding[10];				// store the pos of all deposit cards bindinged
		int depositBindingCount;		// the count of all deposit cards bindinged
	public:
		BindingCard() {}			// construct
		BindingCard(int, int);           // construct
		BindingCard(BindingCard&);    // copy function
		void bindingDepositCard(int);	// binding a deposit card
		void unbindingDepositCard(int);	// unbinding a deposit card
		void pay(string,int);
		void inquire();
		void inquireInfo();
		void inquireWater();
		int getCampusBindingPos();		// return campusBindingPos
		int getDepositBindingCount();	// return depositBindingCount
		int* getBinding();
		bool haveDepositCard(int);		// if have return true else return false
		friend ostream& operator<<(ostream&, BindingCard&);
		friend istream& operator>>(istream&, BindingCard&); 
};

extern BindingCard bindingCard[MAX];	// store all binding cards

#endif
