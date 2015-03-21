#ifndef _STOCK_H
#define _STOCK_H

#include <iostream>
#include <vector>
#include <string>

int curTime = 0;



class Stock {
	std::string name;
	std::vector<long double> netWorth;
	std::vector<long float> bidPrice;
	std::vector<long float> askPrice;
	std::vector<long float> divRatio;
	
public:
	Stock(std::string s) {name = s;}
	std::string getName() {return name;}
	std::vector<long double> getnetWorth() {return netWorth;}
	std::vector<long float> getBid() {return bidPrice;} 
	std::vector<long float> getAsk() {return askPrice;}
	std::vector<long float> getdivRatio() {return divRatio;}
	
	void getInfo();
	
};

#endif