#include <string>
#include "stock.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

time_t cur = time(0);
time_t last = cur;

void Stock::getInfo() {
	string s = "";
	string s1 = "";
	string s2 = "";
	long double worth = 0.0;
	long double dividend = 0.0;
	long double bid = 0.0;
	long double ask = 0.0;
	
			
	system("./codeb ShakeItOff_MLC weareyoung codebb.cloudapp.net 17429 SECURITIES > securities.txt");
	ifstream SECURITIES("securities.txt");
	if (SECURITIES.is_open()) {
		while (s != name) {
			SECURITIES >> s;
		}
		SECURITIES >> s1; // get net_worth
		SECURITIES >> s2; // get dividend_ratio
		istringstream ss1(s1);
		ss1 >> worth;
		netWorth.push_back(worth);
		istringstream ss2(s2);
		ss2 >> dividend;
		divRatio.push_back(dividend);
	}
	SECURITIES.close();
	s = "done";
			
	s1 = "./codeb ShakeItOff_MLC weareyoung codebb.cloudapp.net 17429 ORDERS " + name + " > orders.txt";
	const char* chr = s1.c_str();
	system(chr);
	ifstream ORDERS("orders.txt");
	if (ORDERS.is_open()) {
		while (s != "ASK") {
			ORDERS >> s;
			if (s == "BID") {
				ORDERS >> s;
				ORDERS >> s;
				istringstream ss(s);
				int x;
				ss >> x;
				if (x > bid) {bid = x;}
			}
		}
		bidPrice.push_back(bid);
				
		if (s == "ASK") {
			ORDERS >> s;
			ORDERS >> s;
			istringstream ss(s);
			int x;
			ss >> x;
			if (x < ask) {ask = x;}
		}
		while (ORDERS >> s) {
			if (s == "ASK") {
				ORDERS >> s;
				ORDERS >> s;
				istringstream ss(s);
				int x;
				ss >> x;
				if (x < ask) {ask = x;}
			}
		}
		askPrice.push_back(ask);
				
	}
	ORDERS.close();
}

void Stock::bought() {
	string s = "";
	long double mydiv = 0.0;
	
	system("./codeb ShakeItOff_MLC weareyoung codebb.cloudapp.net 17429 MY_SECURITIES > mysecurities.txt");
	ifstream MYSECURITIES("mysecurities.txt");
	if (MYSECURITIES.is_open()) {
		while (s != name) {
			MYSECURITIES >> S;
		}
		MYSECURITIES >> s;
		MYSECURITIES >> s;
		istringstream ss(s);
		ss >> mydiv;
		myDiv.push_back(mydiv);
	}
	MYSECURITIES.close();
}

void Stock::sold() {
	myDiv.clear();
	share = 0;
}


int main() {
	cout.precision(15);
	Stock AAPL = Stock("AAPL");
	AAPL.getInfo();
	for (vector<long double>::iterator it = AAPL.getnetWorth().begin(); it != AAPL.getnetWorth().end(); it++) {
		cout << *it << endl;
	}
}
















