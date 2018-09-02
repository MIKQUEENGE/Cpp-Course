#ifndef _CARD_H
#define _CARD_H

#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include "founctions.h"
using namespace std;

#define MAX 20						// the max of water sum , each kind of cards

extern int campusCardCount;			// the count of campus cards
extern int depositCardCount;		// the count of deposit cards
extern int bindingCardCount;		// the count of binding cards
extern int depositCardIdMax;		// used to create deposit card id

struct WATER {						// store water information
	string forWhat;	
	int expenditure;
	bool isPay;						// true->cost  false->get
};

class Card {
	protected:
		int balance;       			
		WATER water[MAX];   
		int count;          		// the count of water infomation
	public:
		Card():balance(0),count(0) {}		// construct founction
		Card(int b):balance(b),count(0) {}
		Card(Card& inputCard):balance(inputCard.balance),count(inputCard.count) {	// copy founction
			for (int waterIndex = 0; waterIndex < count; waterIndex++) {
				water[waterIndex].forWhat = inputCard.water[waterIndex].forWhat;
				water[waterIndex].expenditure = inputCard.water[waterIndex].expenditure;
				water[waterIndex].isPay = inputCard.water[waterIndex].isPay;
			}
		} 
		virtual int getBalance() {			// return the balance of the card
			return balance;
		}
		virtual int getCount() {			// return the count of the water information
			return count;
		}
		virtual void setBalance(int b) {
			balance = b;
		}
		virtual WATER* getWater() {
			return water;
		}
		virtual void setWater(WATER* waterTemp) {
			for (int waterIndex = 0; waterIndex < count; waterIndex++) 
				water[waterIndex] = waterTemp[waterIndex];
		}
		virtual void delWater() {			// delete all water infoamation
			this->count = 0;				// count = 0 means no water information
		}
		virtual void pay(string, int) {}	// pay
		virtual void deposit(string forWhat, int depositAmount) {
			Card::balance+=depositAmount;	// balance add the money deposited

			// if no space to store more water information
			if (Card::count>=MAX) cout<<"this card's water warehouse full!"<<"\n"<<"This information will replace the last water information "<<endl;
			else Card::count++;

			// store water information
			Card::water[count-1].expenditure = depositAmount;
			Card::water[count-1].forWhat = forWhat;
			Card::water[count-1].isPay = false;
		}  
		virtual void inquire() {      		// inquire information, mainly used to make client choose and call the founction related  
			cout<<"1. water information 2. basic information  3. all information"<<endl;
			cout<<"please input your choice: ";
			string ans = getFromClient();
			if (isNumber(ans)) {
				if (stoi(ans) == 1) {
					inquireWater();
					return;
				} else if (stoi(ans) == 2) {
					inquireInfo();
					return;
				} else if (stoi(ans) == 3) {
					inquireAll();
					return;
				}
			}
			cout<<"input ERROR!"<<endl;		// if client does not input 1 or 2 or 3
			inquire();						// recall the inquire and make client choose
		}
		virtual void deposit() {}       
		virtual void inquireWater() {		// inquire water information
			if (count <= 0) {				// if there is no water information
				cout<<"no water information!"<<endl;
				return;
			}
			for (int waterIndex = 0; waterIndex < count; waterIndex++) {
				// print every water information stored 
				if (water[waterIndex].isPay)
					cout<<water[waterIndex].forWhat<<" cost you "<<water[waterIndex].expenditure<<" yuan"<<endl;
				else 
					cout<<"you get "<<water[waterIndex].expenditure<<" yuan from "<<water[waterIndex].forWhat<<endl;
			}
		}
		virtual void inquireInfo() {}             
		virtual void inquireAll() {
			inquireInfo();
			inquireWater();
		}
};

#endif
