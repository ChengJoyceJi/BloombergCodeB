#include <string>
#include "galik_socketstream.h"
#include "interact.h"
#include "stock.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

double Interact::cash() {
	
	ofstream outputfile;
	outputfile.open("temp_cash_amount.txt", fstream::out | fstream::trunc);
	string str = command;
	str += "MY_CASH > temp_cash_amount.txt";
	const char* chr= str.c_str();
	system(chr);
	ifstream myfile("temp_cash_amount.txt");
	double cash;
	myfile >> str;
	myfile >> cash;
	return cash;
}

void Interact::buy(string stock, double price, int amount, vector<Stock> &stockCol) {
	
	string str = command;
	str += "BID";
	str += " ";
	str += stock;
	str += " ";
	str += to_string(price);
	str += " ";
	str += to_string(amount);
	const char* chr= str.c_str();
	system(chr);	
	int id = 0;
	vector<Stock>::iterator it;
	for (it = stockCol.begin(); it != stockCol.end(); it++) {
		if (it->getName() == stock) {
			id = it->getID();
			break;
		}
	}
	(stockCol[id]).bought();
}


void Interact::buy(std::string stock, double money, vector<Stock> &stockCol) {
	
	long double curPrice;
	vector<Stock>::iterator it;
	int id = 0;
	for (it = stockCol.begin(); it != stockCol.end(); it++) {
		if (it->getName() == stock) {
			id = it->getID();
			curPrice = (stockCol[id].getAsk())[stockCol[id].getAsk().size()-1];
			break;
		}
	}
	
	cout.precision(15);
	cout << curPrice << endl;
	int amount = (int)(money/curPrice);
	string str = command;
	str += "BID";
	str += " ";
	str += stock;
	str += " ";
	str += to_string(curPrice);
	str += " ";
	str += to_string(amount);
	const char* chr= str.c_str();
	system(chr);
	(stockCol[id]).bought();
}

void Interact::sell(string stock, double price, int amount, vector<Stock> &stockCol) {
	
	string str = command;
	str += "ASK";
	str += " ";
	str += stock;
	str += " ";
	str += to_string(price);
	str += " ";
	str += to_string(amount);
	const char* chr= str.c_str();
	system(chr);
	vector<Stock>::iterator it;
	int id = 0;
	for (it = stockCol.begin(); it != stockCol.end(); it++) {
		if (it->getName() == stock) {
			id = it->getID();
			break;
		}
	}
	(stockCol[id]).sold(amount);
}

void Interact::clearBid(string stock) {
	
	string str = command;
	str += "CLEAR_BID";
	str += " ";
	str += stock;
	const char* chr= str.c_str();
	system(chr);
}

void Interact::clearAsk(string stock) {
	
	string str = command;
	str += "CLEAR_ASK";
	str += " ";
	str += stock;
	const char* chr= str.c_str();
	system(chr);
}
