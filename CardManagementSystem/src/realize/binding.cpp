#include "../../include/sys.h"


BindingCard::BindingCard(int campusBinding, int depositBinding) {
	campusBindingPos = campusBinding;
	binding[0] = depositBinding;
	depositBindingCount = 1;
} 


BindingCard::BindingCard(BindingCard& BindingCardCopy) {
	depositBindingCount = BindingCardCopy.depositBindingCount;
	campusBindingPos = BindingCardCopy.campusBindingPos;
	for (int bindingIndex = 0; bindingIndex < depositBindingCount; bindingIndex++) {
		binding[bindingIndex] = BindingCardCopy.binding[bindingIndex];
	}
}   

void BindingCard::bindingDepositCard(int depositPos) {
	binding[depositBindingCount] = depositPos;
	depositBindingCount++;
}

void BindingCard::unbindingDepositCard(int depositPos) {
	for (int bindingIndex = 0; bindingIndex < depositBindingCount; bindingIndex++) {
		if (binding[bindingIndex] == depositPos) {
			for (int i = bindingIndex; i < depositBindingCount-1; i++) {
				binding[i] = binding[i+1];
			}
			depositBindingCount--;
			break;
		}
	}
}

void BindingCard::pay(string forWhat, int expenditure) {

	// store each divide (by balance , and then by overtraft)
	int balanceSum[2*depositBindingCount+1];
	balanceSum[0] = campusCard[campusBindingPos].getBalance();
	for (int bindingIndex = 0; bindingIndex < depositBindingCount; bindingIndex++) {
		balanceSum[bindingIndex+1] = balanceSum[bindingIndex] + depositCard[binding[bindingIndex]].getBalance();
	}	// by balance
	for (int bindingIndex = 1+depositBindingCount; bindingIndex <= 2*depositBindingCount; bindingIndex++) {
		balanceSum[bindingIndex] = balanceSum[bindingIndex-1] + OVERDRAFT;
	}	// by overtraft

	if (balanceSum[depositBindingCount*2] < expenditure) {	// money is not enough
		cout<<"Sorry, you don't have enough balance!"<<endl;
	} else {
		int deductPos = 0; 		// balanceSum[deductPos-1] < expenditure <= balanceSum[deductPos];
		while (expenditure > balanceSum[deductPos]) deductPos++;

		// if the balance of the campus card is enough
		if (deductPos==0) campusCard[campusBindingPos].pay(forWhat, expenditure);
		// if not enough but don't need to overdraft
		else if (deductPos<=depositBindingCount) {
			campusCard[campusBindingPos].pay(forWhat, balanceSum[0]);
			for (int payIndex = 1; payIndex < deductPos; payIndex++) {
				depositCard[binding[payIndex-1]].pay(forWhat, balanceSum[payIndex]-balanceSum[payIndex-1]);
			}
			depositCard[binding[deductPos-1]].pay(forWhat, expenditure-balanceSum[deductPos-1]);
		// if not enough and even need to overdraft
		} else {
			campusCard[campusBindingPos].pay(forWhat, balanceSum[0]);
			for (int payIndex = 1; payIndex < deductPos-depositBindingCount; payIndex++) {
				depositCard[binding[payIndex-1]].pay(forWhat, balanceSum[payIndex]-balanceSum[payIndex-1]+OVERDRAFT);
			}
			depositCard[binding[deductPos-depositBindingCount-1]].pay(forWhat, expenditure-balanceSum[deductPos-1]+OVERDRAFT);
			for (int payIndex = deductPos-depositBindingCount+1; payIndex < depositBindingCount; payIndex++) {
				depositCard[binding[payIndex-1]].pay(forWhat, balanceSum[payIndex]-balanceSum[payIndex-1]);
			}
		}
		
	}
}

void BindingCard::inquire() {
	cout<<"1. water information 2. basic information\n"<<" please input your choice: ";
	string ans = getFromClient();
	if (isNumber(ans)) {
		if (stoi(ans) == 1) {
			inquireWater();
			return;
		} else if (stoi(ans) == 2) {
			inquireInfo();
			return;
		}
	}
	cout<<"input ERROR!"<<endl;
	inquire();
}

void BindingCard::inquireInfo() {
	cout<<campusCard[campusBindingPos].getInfo().studentId<<"\t(balance:  "<<campusCard[campusBindingPos].Card::getBalance()<<" yuan)"<<endl;
	for (int bindingIndex = 0; bindingIndex < depositBindingCount; bindingIndex++) {
		cout<<"--> "<<depositCard[binding[bindingIndex]].getInfo().cardId<<endl;
	}
}

void BindingCard::inquireWater() {
	if (campusCard[campusBindingPos].getCount() <= 0) {
		cout<<"no water information!"<<endl;
		return;
	}
	for (int waterIndex = 0; waterIndex < campusCard[campusBindingPos].getCount(); waterIndex++) {
		if (campusCard[campusBindingPos].getWater()[waterIndex].isPay)
			cout<<campusCard[campusBindingPos].getWater()[waterIndex].forWhat<<" cost you "<<campusCard[campusBindingPos].getWater()[waterIndex].expenditure<<" yuan"<<endl;
		else 
			cout<<"you get  "<<campusCard[campusBindingPos].getWater()[waterIndex].expenditure<<" yuan from "<<campusCard[campusBindingPos].getWater()[waterIndex].forWhat<<endl;
	}
}

int BindingCard::getCampusBindingPos() {
	return campusBindingPos;
}

int BindingCard::getDepositBindingCount() {
	return depositBindingCount;
}

int* BindingCard::getBinding() {
	return binding;
}

bool BindingCard::haveDepositCard(int pos) {
	for (int bindingIndex = 0; bindingIndex < depositBindingCount; bindingIndex++) {
		if (binding[bindingIndex] == pos) return true;
	}
	return false;
}


// in this order:
// campusBindingPos
// depositBindingCount
// binding[10]
ostream& operator<<(ostream& os, BindingCard& card) {
	os<<card.campusBindingPos<<endl;
	os<<card.depositBindingCount<<endl;
	for (int bindingIndex = 0; bindingIndex < card.depositBindingCount; bindingIndex++) 
		os<<card.binding[bindingIndex]<<endl;
	return os;
}

istream& operator>>(istream& is, BindingCard& card) {
	is>>card.campusBindingPos;
	is>>card.depositBindingCount;
	for (int bindingIndex = 0; bindingIndex < card.depositBindingCount; bindingIndex++) {
		is>>card.binding[bindingIndex];
	}
	return is;
} 
