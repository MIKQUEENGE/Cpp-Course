#ifndef _CAMPUS_H
#define _CAMPUS_H

#include "card.h"

struct CampusInfo {		// the struct store the basic information of campus card
	string studentId;    // student id of the campus card
	string name;         // student name of the campus card
	string faculty;      // student faculty of the campus card
};

class CampusCard:public Card {	// inherit class Card
	protected:
		CampusInfo info;        // basic information
	public:
		CampusCard();           // construct founction 
		CampusCard(CampusInfo);		// counstruct founction
		CampusCard(CampusCard&);    // copy founction
		CampusInfo getInfo();		// return basic information
		virtual void setInfo(CampusInfo);	// change basic information
		virtual void pay(string, int);		// realize : use the campus card pay for something
		virtual void deposit();
		virtual void deposit(string, int);
		virtual void inquireInfo();			// print basic information
		friend ostream& operator<<(ostream&, CampusCard&);		
		friend istream& operator>>(istream&, CampusCard&);
};

extern CampusCard campusCard[MAX];		// store all campus cards

#endif
