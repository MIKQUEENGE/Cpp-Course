#include "../../include/sys.h"

DepositCard::DepositCard() {	// construct
	info.cardId = "\0";
	info.name = "\0";
	info.time = "\0";
}

DepositCard::DepositCard(DepositInfo inputInfo) {	// construct
	info.cardId = inputInfo.cardId;
	info.name = inputInfo.name;
	info.time = inputInfo.time;
}

DepositCard::DepositCard(DepositCard& inputDepositCard):Card(inputDepositCard) { // copy function   
	info.cardId = inputDepositCard.info.cardId;   
	info.name = inputDepositCard.info.name;       
	info.time = inputDepositCard.info.time;      
}

void DepositCard::pay(string forWhat, int expenditure) {
	if (balance + OVERDRAFT < expenditure) {
		cout<<"Sorry, you don't have enough balance or overdraft!"<<endl;
	} else {
		Card::balance-=expenditure;
		if (Card::count>=MAX) cout<<"this card's water warehouse full!"<<"\n"<<"This information will replace the last water information "<<endl;
		else Card::count++;
		Card::water[count-1].expenditure = expenditure;
		Card::water[count-1].forWhat = forWhat;
		Card::water[count-1].isPay = true;
		cout<<"Payment success! You cost "<<expenditure<<" yuan for "<<forWhat<<"!\n";
		if (balance < 0) cout<<"ATTENTION: Your deposit card is overdrawn!"<<endl;
	}
}

void DepositCard::deposit() {
	cout<<"1. from deposit card  2. from cash  \n"<<"Please enter your choice : ";
	string depositChoice = getFromClient();

	if (isNumber(depositChoice)&&stoi(depositChoice)==1) {		// if choose deposit card
		cout<<"Please input the card id of the deposit card deposit from : ";
		string infoInput = getFromClient();		// card id of the deposit card will deposit from
		int depositCardPos = -1;
		bool isCardItself = false;				// judge weather deposit from the card itself

		if (infoInput == this->info.cardId) isCardItself = true;	// is the card itself
		else for (int depositCardIndex = 0; depositCardIndex < depositCardCount; depositCardIndex++) {
			if (infoInput == depositCard[depositCardIndex].getInfo().cardId) {
				depositCardPos = depositCardIndex;		// get pos
				break;
			}
		}

		if (isCardItself) cout<<"Cannot deposit from the card itself!"<<endl;
		else if (depositCardPos != -1) {	// if the card id exists and is not the card itself
			cout<<"Please input how much you want to deposit: ";
			string depositAmount = getFromClient();

			if (isNumber(depositAmount)&&stoi(depositAmount)>0) {	// if is a positive number
				if (depositCard[depositCardPos].getBalance()-stoi(depositAmount) >= 0-OVERDRAFT) { // if money is enough
					Card::balance+=stoi(depositAmount);

					// if no space to store water info
					if (Card::count>=MAX) cout<<"this card's water warehouse full!"<<"\n"<<"This information will replace the last water information "<<endl;
					// if has space
					else Card::count++;

					// set water info
					Card::water[count-1].expenditure = stoi(depositAmount);
					Card::water[count-1].forWhat = "Deposit";
					Card::water[count-1].isPay = false;

					cout<<"Successful deposit! You get "<<depositAmount<<"yuan from Deposit"<<"!\n";
					if (Card::balance < 0) cout<<"ATTENTION: Your deposit card is overdrawn!"<<endl;	// if overdraft
					cout<<"Now your card balance is "<<Card::balance<<" yuan."<<endl;
					depositCard[depositCardPos].pay("Campus card recharge", stoi(depositAmount));		// substract money
					return;
				} else cout<<"Insufficient balance!"<<endl;
			} else cout<<"Input ERROR!"<<endl;

		} else cout<<"Card not found!"<<endl;
	} else if (isNumber(depositChoice)&&stoi(depositChoice)==2) {	// from cash
		cout<<"Please input how much you want to deposit: ";
		string depositAmount = getFromClient();
		if (isNumber(depositAmount)&&stoi(depositAmount)>0) {	// if is a positive number
			Card::balance+=stoi(depositAmount);

			// water space judge
			if (Card::count>=MAX) cout<<"this card's water warehouse full!"<<"\n"<<"This information will replace the last water information "<<endl;
			else Card::count++;

			// set water info
			Card::water[count-1].expenditure = stoi(depositAmount);
			Card::water[count-1].forWhat = "Deposit";
			Card::water[count-1].isPay = false;
			
			cout<<"Successful deposit! You get "<<depositAmount<<"yuan from Deposit "<<"!\n";
			if (Card::balance < 0) cout<<"ATTENTION: Your deposit card is overdrawn!"<<endl;	// if overtraft
			cout<<"Now your card balance is "<<Card::balance<<" yuan."<<endl;

			return;
		} else cout<<"Input ERROR!"<<endl;
	} else cout<<"Input ERROR!"<<endl;
	deposit();
}  

void DepositCard::transfer() {		// transfer money to aother deposit card or campus card
	cout<<"1. to deposit card  2. to campus card  \n"<<"Please enter your choice : ";
	string transferChoice = getFromClient();

	// choose transfer to a deposit card
	if (isNumber(transferChoice)&&stoi(transferChoice)==1) {
		string infoInput = getFromClient();
		int transferCardPos = -1;
		bool isCardItself = false;
		if (infoInput == this->info.cardId) isCardItself = true;
		else for (int depositCardIndex = 0; depositCardIndex < depositCardCount; depositCardIndex++) {
			if (infoInput == depositCard[depositCardIndex].getInfo().cardId) {
				transferCardPos = depositCardIndex;
				break;
			}
		}
		if (isCardItself) cout<<"Cannot transfer to the card itself!"<<endl;
		else if (transferCardPos != -1) {
			cout<<"Please input how much you want to transfer: ";
			string transferAmount = getFromClient();
			if (isNumber(transferAmount)&&stoi(transferAmount)>0) {
				if (getBalance()-stoi(transferAmount) >= 0-OVERDRAFT) {
					Card::balance-=stoi(transferAmount);
					if (Card::count>=MAX) cout<<"this card's water warehouse full!"<<"\n"<<"This information will replace the last water information "<<endl;
					else Card::count++;
					Card::water[count-1].expenditure = stoi(transferAmount);
					Card::water[count-1].forWhat = "Transfer";
					Card::water[count-1].isPay = false;
					cout<<"Successful transfer! You pay "<<transferAmount<<" yuan for transfer"<<"!\n";
					if (Card::balance < 0) cout<<"ATTENTION: Your deposit card is overdrawn!"<<endl;
					cout<<"Now your card balance is "<<Card::balance<<" yuan."<<endl;
					string transfer = "Transfer";
					depositCard[transferCardPos].Card::deposit(transfer, stoi(transferAmount));
					return;
				} else cout<<"Insufficient balance!"<<endl;
			} else cout<<"Input ERROR!"<<endl;
		} else cout<<"Card not found!"<<endl;

	// choose transfer to a campus card
	} else if (isNumber(transferChoice)&&stoi(transferChoice)==2) {
		cout<<"Transfered card info: Please input student id : ";
		string infoInput = getFromClient();
		int transferCardPos = -1;
		for (int campusCardIndex = 0; campusCardIndex < campusCardCount; campusCardIndex++) {
			if (infoInput == campusCard[campusCardIndex].getInfo().studentId) {
				transferCardPos = campusCardIndex;
				break;
			}
		}
		if (transferCardPos != -1) {
			cout<<"Please input how much you want to transfer: ";
			string transferAmount = getFromClient();
			if (isNumber(transferAmount)&&stoi(transferAmount)>0) {
				if (getBalance()-stoi(transferAmount) >= 0-OVERDRAFT) {
					Card::balance-=stoi(transferAmount);
					if (Card::count>=MAX) cout<<"this card's water warehouse full!"<<"\n"<<"This information will replace the last water information "<<endl;
					else Card::count++;
					Card::water[count-1].expenditure = stoi(transferAmount);
					Card::water[count-1].forWhat = "Transfer";
					Card::water[count-1].isPay = false;
					cout<<"Successful transfer! You pay "<<transferAmount<<" yuan for transfer"<<"!\n";
					if (Card::balance < 0) cout<<"ATTENTION: Your deposit card is overdrawn!"<<endl;
					cout<<"Now your card balance is "<<Card::balance<<" yuan."<<endl;
					string transfer = "Transfer";
					campusCard[transferCardPos].Card::deposit(transfer, stoi(transferAmount));
					return;
				} else cout<<"Insufficient balance!"<<endl;
			} else cout<<"Input ERROR!"<<endl;
		} else cout<<"Card not found!"<<endl;

	// wrong input
	} else cout<<"Input ERROR"<<endl;

	transfer();
}     

void DepositCard::inquireInfo() {            
	cout<<"CARD'S CARD ID            : "<<info.cardId<<endl;
	cout<<"CARD'S REGTIME            : "<<info.time<<endl;
	cout<<"CARDHOLDER'S NAME         : "<<info.name<<endl;
	cout<<"CARD'S BALANCE            : "<<Card::getBalance()<<endl<<endl; 
}

DepositInfo DepositCard::getInfo() {
	return this->info;
}

void DepositCard::setInfo(DepositInfo infoInput) {
	this->info = infoInput;
}

// in this order:
// info
// balance
// count
// water
ostream& operator<<(ostream& os, DepositCard& card) {
	os<<card.getInfo().cardId<<endl;
	os<<card.getInfo().name<<endl;
	os<<card.getInfo().time<<endl;
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

istream& operator>>(istream& is, DepositCard& card) {
	DepositInfo infoTemp;
	is>>infoTemp.cardId;
	is>>infoTemp.name;
	is>>infoTemp.time;
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
