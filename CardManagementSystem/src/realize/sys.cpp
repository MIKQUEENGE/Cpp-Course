#include "../../include/sys.h"
using namespace std;


void addCampusCard(CampusCard card) {
	string id = card.getInfo().studentId;
	for (int campusCardIndex = 0; campusCardIndex < campusCardCount; campusCardIndex++) {
		if (campusCard[campusCardIndex].getInfo().studentId == id) {
			cout<<"ERROR!The student id has already been included in the system!"<<endl;
			return;
		}
	}
	campusCard[campusCardCount] = card;
	campusCardCount++;
	cout<<"add successfully!"<<endl;
}

void addDepositCard(DepositCard card) {
	depositCard[depositCardCount] = card;
	depositCardCount++;
	cout<<"add successfully!"<<endl;
}

void addBindingCard(BindingCard card) {
	string id = campusCard[card.getCampusBindingPos()].getInfo().studentId;
	for (int bindingCardIndex = 0; bindingCardIndex < bindingCardCount; bindingCardIndex++) {
		if (campusCard[bindingCard[bindingCardIndex].getCampusBindingPos()].getInfo().studentId == id) {
			cout<<"ERROR!The binding card has already been included in the system!"<<endl;
			return;
		}
	}
	bindingCard[bindingCardCount] = card;
	bindingCardCount++;
	cout<<"add successfully!"<<endl;
}

void delCampusCard(string id) {
	int pos = campusCardPos(id);
	if (pos == -1) {
		cout<<"The campus card not found !"<<endl;
	} else {
		int posBinding = bindingCardPos(id);
		if (pos != -1) delBindingCard(id);
		for (int campusCardIndex = pos; campusCardIndex < campusCardCount-1; campusCardIndex++) {
			campusCard[campusCardIndex] = campusCard[campusCardIndex+1];
		}
		campusCardCount--;
		cout<<"Delete successfully !"<<endl;
		cout<<"NOW the number of all campus cards:   "<<campusCardCount<<endl;
	}
}

void delDepositCard(string id) {
	int pos = depositCardPos(id);
	if (pos == -1) {
		cout<<"The deposit card not found !"<<endl;
	} else {
		for (int bindingCardIndex = 0; bindingCardIndex < bindingCardCount; bindingCardIndex++) {
			bindingCard[bindingCardIndex].unbindingDepositCard(pos);
		}
		for (int depositCardIndex = pos; depositCardIndex < depositCardCount-1; depositCardIndex++) {
			depositCard[depositCardIndex] = depositCard[depositCardIndex+1];
		}
		depositCardCount--;
		cout<<"Delete successfully !"<<endl;
		cout<<"NOW the number of all deposit cards:   "<<depositCardCount<<endl;
	}
}

void delBindingCard(string id) {
	int pos = bindingCardPos(id);
	if (pos == -1) {
		cout<<"The binding card not found !"<<endl;
	} else {
		for (int bindingCardIndex = pos; bindingCardIndex < bindingCardCount-1; bindingCardIndex++) {
			bindingCard[bindingCardIndex] = bindingCard[bindingCardIndex+1];
		}
		bindingCardCount--;
		cout<<"Unbinding successfully !"<<endl;
		cout<<"NOW the number of all binding cards:   "<<bindingCardCount<<endl;
	}
}

void printAllCampusCard() {
	cout<<"The number of all campus cards:   "<<campusCardCount<<endl;
	for (int campusCardIndex = 0; campusCardIndex < campusCardCount; campusCardIndex++)
		cout<<campusCard[campusCardIndex].getInfo().studentId<<endl;
}

void printAllDepositCard() {
	cout<<"The number of all deposit cards:   "<<depositCardCount<<endl;
	for (int depositCardIndex = 0; depositCardIndex < depositCardCount; depositCardIndex++)
		cout<<depositCard[depositCardIndex].getInfo().cardId<<endl;
}

void printAllBindingCard() {
	cout<<"The number of all binding cards:   "<<bindingCardCount<<endl;
	for (int bindingCardIndex = 0; bindingCardIndex < bindingCardCount; bindingCardIndex++) {
		cout<<campusCard[bindingCard[bindingCardIndex].getCampusBindingPos()].getInfo().studentId<<endl;
	}
}

void printAllCampusCardInfo() {
	cout<<"The number of all campus cards:   "<<campusCardCount<<endl;
	for (int campusCardIndex = 0; campusCardIndex < campusCardCount; campusCardIndex++) {
		cout<<campusCard[campusCardIndex].getInfo().studentId<<endl;
		cout<<"--> "<<campusCard[campusCardIndex].getInfo().name<<"  (name)"<<endl;
		cout<<"--> "<<campusCard[campusCardIndex].getInfo().faculty<<"  (faculty)"<<endl;
		cout<<"--> "<<campusCard[campusCardIndex].getBalance()<<"  (balance)"<<endl;
	}
}

void printAllDepositCardInfo() {
	cout<<"The number of all deposit cards:   "<<depositCardCount<<endl;
	for (int depositCardIndex = 0; depositCardIndex < depositCardCount; depositCardIndex++) {
		cout<<depositCard[depositCardIndex].getInfo().cardId<<endl;
		cout<<"--> "<<depositCard[depositCardIndex].getInfo().name<<"  (name)"<<endl;
		cout<<"--> "<<depositCard[depositCardIndex].getInfo().time<<"  (time)"<<endl;
		cout<<"--> "<<depositCard[depositCardIndex].getBalance()<<"  (balance)"<<endl;
	}
}

void printAllBindingCardInfo() {
	cout<<"The number of all binding cards:   "<<bindingCardCount<<endl;
	for (int bindingCardIndex = 0; bindingCardIndex < bindingCardCount; bindingCardIndex++) {
		cout<<campusCard[bindingCard[bindingCardIndex].getCampusBindingPos()].getInfo().studentId<<endl;
		for (int bindingIndex = 0; bindingIndex < bindingCard[bindingCardIndex].getDepositBindingCount(); bindingIndex++) {
			cout<<"--> "<<depositCard[bindingCard[bindingCardIndex].getBinding()[bindingIndex]].getInfo().cardId<<endl;
		}
	}
}

void writeCampusCard() {
	fclose(fopen("info/CampusCard.txt", "w"));
	ofstream out("info/CampusCard.txt");
	out.clear();
	out<<campusCardCount<<endl;
	for (int campusCardIndex = 0; campusCardIndex < campusCardCount; campusCardIndex++)
		out<<campusCard[campusCardIndex];
	out.close();
}

void writeDepositCard() {
	fclose(fopen("info/DepositCard.txt", "w"));
	ofstream out("info/DepositCard.txt");
	out.clear();
	out<<depositCardIdMax<<endl;
	out<<depositCardCount<<endl;
	for (int depositCardIndex = 0; depositCardIndex < depositCardCount; depositCardIndex++)
		out<<depositCard[depositCardIndex];
	out.close();
}

void writeBindingCard() {
	fclose(fopen("info/BindingCard.txt", "w"));
	ofstream out("info/BindingCard.txt");
	out.clear();
	out<<bindingCardCount<<endl;
	for (int bindingCardIndex = 0; bindingCardIndex < bindingCardCount; bindingCardIndex++)
		out<<bindingCard[bindingCardIndex];
	out.close();
}

void readCampusCard() {
	ifstream in("info/CampusCard.txt");
	int campusCardIndex = 0;
	in>>campusCardCount;
	while (1)
	{
		in>>campusCard[campusCardIndex];
		if (!in) break;
		campusCardIndex++;
	}
	in.close();
}

void readDepositCard() {
	ifstream in("info/DepositCard.txt");
	int depositCardIndex = 0;
	in>>depositCardIdMax;
	in>>depositCardCount;
	while (1)
	{
		in>>depositCard[depositCardIndex];
		if (!in) break;
		depositCardIndex++;
	}
	in.close();
}

void readBindingCard() {
	ifstream in("info/BindingCard.txt");
	int bindingCardIndex = 0;
	in>>bindingCardCount;
	while (1)
	{
		in>>bindingCard[bindingCardIndex];
		if (!in) break;
		bindingCardIndex++;
	}
	in.close();
}

void read() {
	readCampusCard();
	readDepositCard();
	readBindingCard();
}

void write() {
	writeCampusCard();
	writeDepositCard();
	writeBindingCard();
}

int campusCardPos(string id) {
	for (int campusCardIndex = 0; campusCardIndex < campusCardCount; campusCardIndex++) {
		if (campusCard[campusCardIndex].getInfo().studentId.compare(id) == 0) return campusCardIndex;
	}
	return -1;
}

int depositCardPos(string id) {
	for (int depositCardIndex = 0; depositCardIndex < depositCardCount; depositCardIndex++) {
		if (depositCard[depositCardIndex].getInfo().cardId == id) return depositCardIndex;
	}
	return -1;
}

int bindingCardPos(string id) {
	for (int bindingCardIndex = 0; bindingCardIndex < bindingCardCount; bindingCardIndex++) {
		if (campusCard[bindingCard[bindingCardIndex].getCampusBindingPos()].getInfo().studentId == id)
			return bindingCardIndex;
	}
	return -1;
}

