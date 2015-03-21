#ifndef _STOCK_H
#define _STOCK_H

#include <iostream>
#include <vector>
#include <string>

int curTime = 0;



class Stock {
	std::string name;
	std::vector<long double> netWorth;
	std::vector<long double> bidPrice;
	std::vector<long double> askPrice;
	std::vector<long double> divRatio;
	
public:
	Stock(std::string s) {name = s;}
	~Stock() {}
	
	
	std::string getName() {return name;}
	std::vector<long double> getnetWorth() {return netWorth;}
	std::vector<long double> getBid() {return bidPrice;} 
	std::vector<long double> getAsk() {return askPrice;}
	std::vector<long double> getdivRatio() {return divRatio;}
	
	void getInfo();
	
};

#endif