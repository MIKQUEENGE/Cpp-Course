#include "../../include/sys.h"
using namespace std;

//initial
int campusCardCount = 0;
int depositCardCount = 0;
int bindingCardCount = 0;
int depositCardIdMax = 0;

CampusCard campusCard[MAX] = {};
DepositCard depositCard[MAX] = {};
BindingCard bindingCard[MAX] = {};


void loopMain();	// the main loop of the main interface


int main() {
	read();
	loopMain();
	write();
	return 0;
}


void choice1();		// choose 1 inquire information
void choice2();		// choose 2 print all card
void choice3();		// choose 3 cards management
void choice4();		// choose 4 (un)binding to binding card
void choice5();		// choose 5 use a card
void choice9();		// choose 9 exit the system
void choice0();		// choose 0 return to the main interface

void loopMain() {
	while (1) {
		funcPrint();
		string mainChoice = getFromClient();
		system("cls");
		if (isNumber(mainChoice)) {
			int choice = stoi(mainChoice);
			switch(choice) {
				case 1:
					choice1();
					break;
				case 2:
					choice2();
					break;
				case 3:
					choice3();
					break;
				case 4:
					choice4();
					break;
				case 5:
					choice5();
					break;
				case 9:
					choice9();
					break;
				default:
					cout<<"Input ERROR!"<<endl;
			}
		} else {
			system("cls");
			cout<<"Input ERROR!"<<endl;
		}
		pauseForRead();
	}
}

void choice1() {	// choose 1 inquire information
	cout<<"1. campus card  2. deposit card"<<"\n"<<"3. binding card  0. return the main interface"<<endl;
	cout<<"Your choice is : ";
	string infoChoice = getFromClient();
	int choice = -1;
	if (isNumber(infoChoice)) choice = stoi(infoChoice);
	switch(choice) {
		case 1: 
			{
				if (campusCardCount==0) cout<<"No campus card now!"<<endl;
				else {
					printAllCampusCard();
					while (1) {
						cout<<"Input the student id of the card you want to inquire : ";
						string idInput = getFromClient();
						int pos = campusCardPos(idInput);
						if (pos==-1) {
							cout<<"card not found!"<<endl;
							continue;
						}
						campusCard[pos].Card::inquire();
						break;
					}
				}
			}
			break;
		case 2:
			{
				if (depositCardCount==0) cout<<"No deposit card now!"<<endl;
				else {
					printAllDepositCard();
					while (1) {
						cout<<"Input the card id of the card you want to inquire : ";
						string idInput = getFromClient();
						int pos = depositCardPos(idInput);
						if (pos==-1) {
							cout<<"card not found!"<<endl;
							continue;
						}
						depositCard[pos].Card::inquire();
						break;
					}
				}
			}
			break;
		case 3:
			{
				if (bindingCardCount==0) cout<<"No binding card now!"<<endl;
				else {
					printAllBindingCard();
					while (1) {
						cout<<"Input the student id of the card you want to inquire : ";
						string idInput = getFromClient();
						int pos = bindingCardPos(idInput);
						if (pos==-1) {
							cout<<"card not found!"<<endl;
							continue;
						}
						bindingCard[pos].inquire();
						break;
					}
				}
			}
			break;
		case 0:
			choice0();
			break;
		default:
			cout<<"Input ERROR"<<endl;
			choice1();
	}
}

void choice2() {	// choose 2 print all card
	cout<<"1. campus card  2. deposit card"<<"\n"<<"3. binding card  0. return the main interface"<<endl;
	cout<<"Your choice is : ";
	string infoChoice = getFromClient();
	int choice = -1;
	if (isNumber(infoChoice)) choice = stoi(infoChoice);
	switch(choice) {
		case 1: 
			{
				printAllCampusCard();
				if (campusCardCount==0) break;
				cout<<"If you want to see all the information of the cards, input 1 : ";
				string infoPrint = getFromClient();
				if (infoPrint == "1") printAllCampusCardInfo();
			}
			break;
		case 2:
			{
				printAllDepositCard();
				if (depositCardCount==0) break;
				cout<<"If you want to see all the information of the cards, input 1 : ";
				string infoPrint = getFromClient();
				if (infoPrint == "1") printAllDepositCardInfo();
			}
			break;
		case 3:
			{
				printAllBindingCard();
				if (bindingCardCount==0) break;
				cout<<"If you want to see all the information of the cards, input 1 : ";
				string infoPrint = getFromClient();
				if (infoPrint == "1") printAllBindingCardInfo();
			}
			break;
		case 0:
			choice0();
			break;
		default:
			cout<<"Input ERROR"<<endl;
			choice2();
	}
}

void choice3() {	// choose 3 cards management
	cout<<"1. campus card  2. deposit card"<<"\n"<<"3. binding card  0. return the main interface\n";
	cout<<"Your choice is : ";
	string infoChoice = getFromClient();
	int choice = -1;
	if (isNumber(infoChoice)) choice = stoi(infoChoice);
	switch(choice) {
		case 1: 
			{
				printAllCampusCard();
				while (1) {
					cout<<"1. add a campus card  2. delete a campus card  0. return the main interface\nYour choice is : ";
					string manageChoice = getFromClient();
					if (manageChoice == "1") {
						if (campusCardCount>=MAX) {
							cout<<"Campus card warehouse full ! you can delete some campus cards !"<<endl;
							break;
						}
						CampusInfo info;
						while (1) {
							cout<<"studentId(must consist of numbers) : ";
							info.studentId = getFromClient();  
							if (!isNumber(info.studentId)) {
								cout<<"not in the right form!"<<endl;
								continue;
							}
							break;
						}
						cout<<"name : ";
						info.name = getFromClient();       
						cout<<"faculty : ";
						info.faculty = getFromClient();     
						CampusCard card(info);
						addCampusCard(card);
					} else if (manageChoice == "2") {
						cout<<"Input the student id of the card you want to delete : ";
						string idInput = getFromClient();
						delCampusCard(idInput);
					} else if (manageChoice == "0") {
						choice0();
					} else {
						cout<<"Input ERROR!"<<endl;
						continue;
					}
					break;
				}
			}
			break;
		case 2:
			{
				printAllDepositCard();
				while (1) {
					cout<<"1. add a deposit card  2. delete a deposit card"<<"\n"<<"0. return the main interface\nYour choice is : ";
					string manageChoice = getFromClient();
					if (manageChoice == "1") {
						if (depositCardCount>=MAX) {
							cout<<"deposit card warehouse full ! you can delete some deposit cards !"<<endl;
							break;
						}
						DepositInfo info;
						cout<<"name : ";
						info.name = getFromClient(); 
						while (1) {
							cout<<"time(in the shape of 20000101, must have 8 numbers) : ";
							info.time = getFromClient();   
							if (info.time.length()!=8||(!isNumber(info.time))) {
								cout<<"not in the right form!"<<endl;
								continue;
							}
							break;
						}  
						info.cardId = itos(depositCardIdMax);
						for (int idIndex = info.cardId.length()+1; idIndex <= 15; idIndex++) {
							info.cardId = "0"+info.cardId;
						}
						info.cardId = "1024"+info.cardId;
						depositCardIdMax++;
						DepositCard card(info);
						addDepositCard(card);
						cout<<"card id is : "<<info.cardId<<endl;
					} else if (manageChoice == "2") {
						cout<<"Input the card id of the card you want to delete : ";
						string idInput = getFromClient();
						delDepositCard(idInput);
					} else if (manageChoice == "0") {
						choice0();
					} else {
						cout<<"Input ERROR!"<<endl;
						continue;
					}
					break;
				}
			}
			break;
		case 3:
			{
				printAllBindingCard();
				while (1) {
					cout<<"1. add a Binding card  2. unbinding a Binding card"<<endl;
					cout<<"0. return the main interface\nYour choice is : ";
					string manageChoice = getFromClient();
					if (manageChoice == "1") {
						if (bindingCardCount>=MAX) {
							cout<<"binding card warehouse full ! you can delete some binding cards !"<<endl;
							break;
						}
						printAllCampusCard();
						cout<<"Input the student id of the campus card you want to binding : ";
						string idCampus = getFromClient();
						int posCampus = campusCardPos(idCampus);
						if (posCampus == -1) {
							cout<<"no card found!"<<endl;
							continue;
						}
						printAllDepositCard();
						cout<<"Input the card id of the deposit card you want to binding : ";
						string idDeposit = getFromClient();
						int posDeposit = depositCardPos(idDeposit);
						if (posDeposit == -1) {
							cout<<"no card found!"<<endl;
							continue;
						}
						BindingCard card(posCampus, posDeposit);
						addBindingCard(card);
					} else if (manageChoice == "2") {
						cout<<"Input the card id of the card you want to delete : ";
						string idInput = getFromClient();
						delBindingCard(idInput);
					} else if (manageChoice == "0") {
						choice0();
					} else {
						cout<<"Input ERROR!"<<endl;
						continue;
					}
					break;
				}
			}
			break;
		case 0:
			choice0();
			break;
		default:
			cout<<"Input ERROR"<<endl;
			choice3();
	}
}

void choice4() {	// choose 4 (un)binding to binding card
	printAllBindingCard();
	cout<<"Input the student id of the binding card you want to binding : ";
	string idBinding = getFromClient();
	int posBinding = bindingCardPos(idBinding);
	if (posBinding == -1) {
		cout<<"no card found!"<<endl;
	} else {
		cout<<"1. binding  2. unbinding"<<"\n"<<"0. return the main interface\n";
		cout<<"Your choice is : ";
		string bindingChoice = getFromClient();
		if (bindingChoice=="1") {
			printAllDepositCard();
			cout<<"Input the card id of the deposit card you want to binding : ";
			string idDeposit = getFromClient();
			int posDeposit = depositCardPos(idDeposit);
			if (posDeposit == -1) {
				cout<<"no card found!"<<endl;
			} else {
				if (bindingCard[posBinding].haveDepositCard(posDeposit)) {
					cout<<"the deposit card has been already binding on the binding card!"<<endl;
				} else {
					bindingCard[posBinding].bindingDepositCard(posDeposit);
					cout<<"Binding successfully!"<<endl;
				}
			}
		} else if (bindingChoice=="2") {
			bindingCard[posBinding].inquireInfo();
			cout<<"Input the card id of the deposit card you want to unbinding : ";
			string idDeposit = getFromClient();
			int posDeposit = depositCardPos(idDeposit);
			if (posDeposit == -1) {
				cout<<"no card found!"<<endl;
			} else {
				if (!bindingCard[posBinding].haveDepositCard(posDeposit)) {
					cout<<"the deposit card has not been binding on the binding card!"<<endl;
				} else {
					bindingCard[posBinding].unbindingDepositCard(posDeposit);
					cout<<"Unbinding successfully!"<<endl;
				}
			}
		} else if (bindingChoice=="0") {
			choice0();
		} else {
			cout<<"Input ERROR!"<<endl;
		}		
	}
}

void choice5() {	// choose 5 use a card
	cout<<"1. campus card(include binding card)  2. deposit card"<<"\n"<<"0. return the main interface\n";
	cout<<"Your choice is : ";
	string infoChoice = getFromClient();
	int choice = -1;
	if (isNumber(infoChoice)) choice = stoi(infoChoice);
	switch(choice) {
		case 1: 
			{
				printAllCampusCard();
				while (1) {
					cout<<"please input the student id of the card you want to use : ";
					string id = getFromClient();
					if (campusCardPos(id) == -1) {
						cout<<"no card found!"<<endl;
						continue;
					}
  					if (bindingCardPos(id) != -1) {
						BindingCard* card = &bindingCard[bindingCardPos(id)];
						cout<<"it's a binding card."<<endl;
						cout<<"1. pay  2. deposit  3. delete all water information"<<"\n"<<"0. return the main interface\n";
						cout<<"Your choice is : ";
						string useChoice = getFromClient();
						if (useChoice=="1") {
							cout<<"for what : ";
							string forWhat = getFromClient();
							cout<<"expenditure : ";
							string expenditure = getFromClient();
							if (!isNumber(expenditure)) {
								cout<<"please input correct number!"<<endl;
								continue;
							}
							int expen = stoi(expenditure);
							card->pay(forWhat,expen);
						} else if (useChoice=="2") {
							card->CampusCard::deposit();
						} else if (useChoice=="3") {
							campusCard[card->getCampusBindingPos()].Card::delWater();
						} else if (useChoice=="0") {
							choice0();
						} else {
							cout<<"Input ERROR!"<<endl;
							continue;
						}
					} else {
						CampusCard* card = &campusCard[campusCardPos(id)];
						cout<<"1. pay  2. deposit  3. delete all water information"<<"\n"<<"0. return the main interface\n";
						cout<<"Your choice is : ";
						string useChoice = getFromClient();
						if (useChoice=="1") {
							cout<<"for what : ";
							string forWhat = getFromClient();
							cout<<"expenditure : ";
							string expenditure = getFromClient();
							if (!isNumber(expenditure)) {
								cout<<"please input correct number!"<<endl;
								continue;
							}
							int expen = stoi(expenditure);
							card->pay(forWhat,expen);
						} else if (useChoice=="2") {
							card->deposit();
						} else if (useChoice=="3") {
							card->Card::delWater();
						} else if (useChoice=="0") {
							choice0();
						} else {
							cout<<"Input ERROR!"<<endl;
							continue;
						}
					}
					break;
				}
			}
			break;
		case 2:
			{
				printAllDepositCard();
				while (1) {
					cout<<"please input the card id of the card you want to use : ";
					string id = getFromClient();
					if (depositCardPos(id) == -1) {
						cout<<"no card found!"<<endl;
						continue;
					}
					DepositCard* card = &depositCard[depositCardPos(id)];
					cout<<"1. pay  2. deposit 3. transfer"<<"\n"<<"4. delete all water information  0. return the main interface\n";
					cout<<"Your choice is : ";
					string useChoice = getFromClient();
					if (useChoice=="1") {
						cout<<"for what : ";
						string forWhat = getFromClient();
						cout<<"expenditure : ";
						string expenditure = getFromClient();
						if (!isNumber(expenditure)) {
							cout<<"please input correct number!"<<endl;
							continue;
						}
						int expen = stoi(expenditure);
						card->pay(forWhat,expen);
					} else if (useChoice=="2") {
						card->deposit();
					} else if (useChoice=="3") {
						card->transfer();
					} else if (useChoice=="4") {
						card->Card::delWater();
					} else if (useChoice=="0") {
						choice0();
					} else {
						cout<<"Input ERROR!"<<endl;
						continue;
					}
					break;
				}
			}
			break;
		case 0:
			choice0();
			break;
		default:
			cout<<"Input ERROR"<<endl;
			choice5();
	}
}

void choice9() {	// choose 9 exit the system
	system("cls");
	cout<<"****************************************************"<<endl;
	cout<<"**                 TAHNKS FOR USING               **"<<endl;
	cout<<"****************************************************"<<endl;
	write();
	exit(0);                
}

void choice0() {	// choose 0 return to the main interface
	system("cls");
	loopMain();
	write();
	exit(0);
}
