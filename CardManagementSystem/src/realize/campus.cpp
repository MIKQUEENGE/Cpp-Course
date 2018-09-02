#include "../../include/sys.h"


CampusCard::CampusCard():Card() {       	// construct
	info.studentId = "\0";					// initial
	info.name = "\0";
	info.faculty = "\0";
}

CampusCard::CampusCard(CampusInfo c) {		// get basic information and make it card's info
	info.studentId = c.studentId;   
	info.name = c.name;         
	info.faculty = c.faculty;     
}

CampusCard::CampusCard(CampusCard& c):Card(c) {    // copy function
	info.studentId = c.info.studentId;    
	info.name = c.info.name;        
	info.faculty = c.info.faculty;      
}

void CampusCard::pay(string forWhat, int expenditure) {  // forWhat means pay for what, expenditure is how much it will pay
	if (balance<expenditure) {			// if balance is not enough
		cout<<"Sorry, you don't have enough balance!"<<endl;
	} else {							// if balance is enough
		Card::balance-=expenditure;		// substrat expenditure

		// if there is no space to store the water information
		if (Card::count>=MAX) cout<<"this card's water warehouse full!"<<"\n"<<"This information will replace the last water information "<<endl;
		// if has space
		else Card::count++;

		Card::water[count-1].expenditure = expenditure;
		Card::water[count-1].forWhat = forWhat;
		Card::water[count-1].isPay = true;

		// print infomation related of this activity
		cout<<"Payment success! You cost "<<expenditure<<" yuan for "<<forWhat<<"!\n";
		cout<<"Now your card balance is "<<Card::balance<<" yuan."<<endl;
	}
}

void CampusCard::deposit(string forWhat, int depositAmount) {		// forWhat means in which way get the money, deposit Amount means how much the card get
			Card::balance+=depositAmount;		// add depositAmount

			// if there is no space to store the water information
			if (Card::count>=MAX) cout<<"this card's water warehouse full!"<<"\n"<<"This information will replace the last water information "<<endl;
			// if has space
			else Card::count++;

			Card::water[count-1].expenditure = depositAmount;
			Card::water[count-1].forWhat = forWhat;
			Card::water[count-1].isPay = false;
}  

void CampusCard::deposit() {      // deposit from deposit card
	cout<<"Please input the card id of the deposit card deposit from : ";
	string infoInput = getFromClient();		// get the card id
	int depositCardPos = -1;				// the pos of the deposit card related the card id got
	for (int depositCardIndex = 0; depositCardIndex < depositCardCount; depositCardIndex++) {
		// if find the card id 
		if (infoInput == depositCard[depositCardIndex].getInfo().cardId) {
			depositCardPos = depositCardIndex;	
			break;
		}
	}
	if (depositCardPos != -1) {		// if the card id exists
		cout<<"Please input how much you want to deposit: ";
		string depositAmount = getFromClient();		// get how much client want to deposit
		if (isNumber(depositAmount)&&stoi(depositAmount)>0) {	// if what got is a positive number
			if (depositCard[depositCardPos].getBalance()-stoi(depositAmount) >= 0-OVERDRAFT) {		
				// if money in the deposit card is enough
				Card::balance+=stoi(depositAmount);		// add the depositAmount to the campus card

				// if there is no space to store the water information
				if (Card::count>=MAX) cout<<"this card's water warehouse full!"<<"\n"<<"This information will replace the last water information "<<endl;
				// if has space
				else Card::count++;

				Card::water[count-1].expenditure = stoi(depositAmount);
				Card::water[count-1].forWhat = "Deposit";
				Card::water[count-1].isPay = false;

				// print information related
				cout<<"Successful deposit! You get "<<depositAmount<<" yuan from Deposit"<<"!\n";
				cout<<"Now your card balance is "<<Card::balance<<" yuan."<<endl;

				depositCard[depositCardPos].pay("Campus card recharge", stoi(depositAmount));	// substract the money in the deposit card
				return;			// end the operation
			} else cout<<"Insufficient balance!"<<endl;	
		} else cout<<"Input ERROR!"<<endl;
	} else cout<<"Card not found!"<<endl;
	deposit();		// if operate error
}

void CampusCard::inquireInfo() {             // print basic information and balance
	cout<<"CARDHOLDER'S NAME         : "<<info.name<<endl;
	cout<<"CARDHOLDER'S FACULTY      : "<<info.faculty<<endl;
	cout<<"CARDHOLDER'S STUDENT ID   : "<<info.studentId<<endl;
	cout<<"CARD'S BALANCE            : "<<Card::getBalance()<<endl<<endl;
}

CampusInfo CampusCard::getInfo() {			// return basic information
	return this->info;
}

void CampusCard::setInfo(CampusInfo infoInput) {	// change info
	this->info = infoInput;
}

// in this order:
// info
// balance
// count
// water
ostream& operator<<(ostream& os, CampusCard& card) {
	os<<card.getInfo().studentId<<endl;
	os<<card.getInfo().name<<endl;
	os<<card.getInfo().faculty<<endl;
	os<<card.Card::balance<<endl;
	os<<card.Card::count<<endl;
	WATER* waterTemp = card.Card::getWater();
	for (int waterIndex = 0; waterIndex < card.Card::count; waterIndex++) {
		os<<waterTemp[waterIndex].forWhat<<endl;
		os<<waterTemp[waterIndex].expenditure<<endl;
		os<<waterTemp[waterIndex].isPay<<endl;
	}
	return os;
}

istream& operator>>(istream& is, CampusCard& card) {
	CampusInfo infoTemp;
	is>>infoTemp.studentId;
	is>>infoTemp.name;
	is>>infoTemp.faculty;
	card.setInfo(infoTemp);
	is>>card.Card::balance;
	is>>card.Card::count;
	WATER waterTemp[card.Card::count];
	for (int waterIndex = 0; waterIndex < card.Card::count; waterIndex++) {
		is>>waterTemp[waterIndex].forWhat;
		is>>waterTemp[waterIndex].expenditure;
		is>>waterTemp[waterIndex].isPay;
	}
	card.Card::setWater(waterTemp);
	return is;
}
