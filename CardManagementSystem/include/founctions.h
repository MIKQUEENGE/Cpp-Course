#ifndef _FOUNCTIONS_H
#define _FOUNCTIONS_H

#include <iostream>
#include <string>
using namespace std;

bool isNumber(string);		// if is number return true, else return false
int stoi(string);			// string to int
string itos(int);			// int to string
void DAS(string&);    	     // delete all spaces and \t
string getFromClient();		// get line and DAS
void funcPrint();			// print main interface
void pauseForRead();		// realize "enter any key to continue"

#endif
