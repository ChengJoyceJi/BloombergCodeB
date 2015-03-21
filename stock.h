#ifndef _STOCK_H
#define _STOCK_H

#include <iostream>
#include <vector>
#include <string>

int curTime = 0;



class Stock {
	int ID;
	std::string name;
	std::vector<long double> myDiv;
	int share;
	
	
	std::vector<long double> netWorth;
	std::vector<long double> bidPrice;
	std::vector<long double> askPrice;
	std::vector<long double> divRatio;
	
public:
	Stock(std::string s, int x) {
		name = s; 
		ID = x;
		share = 0;
	}
	
	~Stock() {}
	
	int getID() {return ID;}
	int getShare() {return share;}
	void setShare(int x) {share = x;}
	std::string getName() {return name;}
	std::vector<long double> getmyDiv() {return myDiv;}
	
	
	std::vector<long double> getnetWorth() {return netWorth;}
	std::vector<long double> getBid() {return bidPrice;} 
	std::vector<long double> getAsk() {return askPrice;}
	std::vector<long double> getdivRatio() {return divRatio;}
	
	void getInfo();
	
	void bought();
	
	void sold();
};

#endif