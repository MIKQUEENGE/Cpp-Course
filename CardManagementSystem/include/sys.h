#ifndef _SYS_H
#define _SYS_H

#include "binding.h"


void addCampusCard(CampusCard);
void addDepositCard(DepositCard);
void addBindingCard(BindingCard);
void delCampusCard(string);
void delDepositCard(string);
void delBindingCard(string);
void printAllCampusCard();
void printAllDepositCard();
void printAllBindingCard();
void printAllCampusCardInfo();
void printAllDepositCardInfo();
void printAllBindingCardInfo();
void writeCampusCard();
void writeDepositCard();
void writeBindingCard();
void readCampusCard();
void readDepositCard();
void readBindingCard();
void read();							// read all
void write();							// write all
int campusCardPos(string);				// return the pos of the card by getting its id, if the card not exists, return -1
int depositCardPos(string);
int bindingCardPos(string);



#endif
