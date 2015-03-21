#include <string>
#include "galik_socketstream.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "stock.h"
#include "interact.h"
#include <pthread.h>

using namespace std;
using namespace galik;
using namespace galik::net;

Stock S1 = Stock("AAPL",1); Stock S2 = Stock("ATVI",2);
Stock S3 = Stock("EA",3); Stock S4 = Stock("FB",4);
Stock S5 = Stock("GOOG",5); Stock S6 = Stock("MSFT",6);
Stock S7 = Stock("SNY",7); Stock S8 = Stock("TSLA",8);
Stock S9 = Stock("TWTR",9); Stock S10 = Stock("XOM",10);

vector<Stock> stockCol;

int curTime;

string get_stockName(int i) {
	string stockName;
	for(int m = 0; m < 10; m ++) {
		if(stockCol[m].getID() == i) {
			stockName = stockCol[m].getName();
		}
	}
	return stockName;
}

int highestDividend(vector<Stock> &collection) {
	
	long double maxDiv = 0;
	int maxid = 0;
	for (int id = 0; id < 10; id++) {
		long double divRatio = *(collection[id].getdivRatio().end()-1);
		long double netWorth = *(collection[id].getnetWorth().end()-1);
		long double divv = divRatio * netWorth;
		if (divv > maxDiv) {
			maxDiv = divv;
			maxid = id;
		}
	}
	return maxid;	
}

void buy_stocks(vector<Stock> stockCol, Interact* it) {
	for(int i = 0; i < 10; i++) {
		//buy the stock if it keeps decreasing in three periods and suddenly start to up
		if(stockCol[i].getAsk().size() > 8) {
			long double cur_ask_price = *(stockCol[i].getAsk().end() - 1);
			long double prev_ask_price_1 = *(stockCol[i].getAsk().end() - 2);
			long double prev_ask_price_2 = *(stockCol[i].getAsk().end() - 4);
			long double prev_ask_price_3 = *(stockCol[i].getAsk().end() - 6);
			long double prev_ask_price_4 = *(stockCol[i].getAsk().end() - 8);
			if(prev_ask_price_1 < prev_ask_price_2 && prev_ask_price_2 < prev_ask_price_3 && 
			   prev_ask_price_3 < prev_ask_price_4) {
				if(cur_ask_price > prev_ask_price_1) {
					it->buy(get_stockName(i), it->cash() * 0.9, stockCol);
					stockCol[i].setboughtTime(curTime);
				}
			}
		}	
		//
	}
}

void sell_stock(vector<Stock> stockCol, Interact* it) {
	for(int i = 0; i < 10; i++) {
		//sell the stock when the price has decreased by a certain percentage
		long double cur_ask_price = *(stockCol[i].getAsk().end() - 1);
		long double initial_bought_price = (stockCol[i].getBid()[stockCol[i].getboughtTime()]);
		long double decrease_rate = (initial_bought_price - cur_ask_price) / initial_bought_price;
		if(decrease_rate >= 0.1) {
			it->sell(get_stockName(i), *(stockCol[i].getBid().end() - 1), stockCol[i].getShare(),stockCol);
		}
		//sell the stock when the price has increased too dramatically in the last second
		long double prev_ask_price = *(stockCol[i].getBid().end() - 2);
		long double period_increase_rate = (cur_ask_price - prev_ask_price) / prev_ask_price;
		if(period_increase_rate > 0.1) {
			it->sell(get_stockName(i), *(stockCol[i].getBid().end() - 1), stockCol[i].getShare(), stockCol);
		}
		//sell the stock if it keeps increasing in three periods and suddenly start to fall
		if(stockCol[i].getAsk().size() > 8) {
			cur_ask_price = *(stockCol[i].getAsk().end() - 1);
			long double prev_ask_price_1 = *(stockCol[i].getAsk().end() - 2);
			long double prev_ask_price_2 = *(stockCol[i].getAsk().end() - 4);
			long double prev_ask_price_3 = *(stockCol[i].getAsk().end() - 6);
			long double prev_ask_price_4 = *(stockCol[i].getAsk().end() - 8);
			if(prev_ask_price_1 < prev_ask_price_2 && prev_ask_price_2 < prev_ask_price_3 && prev_ask_price_3 < prev_ask_price_4) {
				if(cur_ask_price > prev_ask_price_1) {
					it->sell(get_stockName(i), *(stockCol[i].getBid().end() - 1), stockCol[i].getShare(), stockCol);
				}
			}
		}				
	}
}

int main() {
	curTime = 0;
	time_t cur = time(0);
	time_t last = cur;
	stockCol.push_back(S1); stockCol.push_back(S6);
	stockCol.push_back(S2); stockCol.push_back(S7);
	stockCol.push_back(S3); stockCol.push_back(S8);
	stockCol.push_back(S4); stockCol.push_back(S9);
	stockCol.push_back(S5); stockCol.push_back(S10);
	
	for(int n = 0;n < 10; n++) {
		stockCol[n].getInfo();
	}	

	Interact* it = new Interact();
	it->buy("AAPL", 100, stockCol); it->buy("ATVI", 100, stockCol);
	it->buy("EA", 100, stockCol);   it->buy("FB", 100, stockCol);
	it->buy("GOOG", 100, stockCol); it->buy("MSFT", 100, stockCol);
	it->buy("SNY", 100, stockCol);  it->buy("TSLA", 100, stockCol);
	it->buy("TWTR", 100, stockCol); it->buy("XOM", 100, stockCol);
	
	while (curTime < 300) {
		if (cur != last) {

			for(int n = 0; n < 10; n++) {
				stockCol[n].getInfo();
			}

			last = cur;
			sleep(15);
			cout << "cash: " << it->cash() << endl;
			//Transfer 100 for dividends;
			long double min_return = 0; 
			string stockName;
			long double price;
			for(int i = 0; i < 10; i++) {
				//sell the stock when the price has decreased by a certain percentage
				long double cur_ask_price =   *(stockCol[i].getAsk().end() - 1);
				long double initial_bought_price = (stockCol[i].getBid()[stockCol[i].getboughtTime()]);
				long double increase_rate = (cur_ask_price - initial_bought_price) / initial_bought_price;	
				if(i == 0) {
					min_return = increase_rate;
					stockName = stockCol[i].getName();
				} else {
					if(increase_rate < min_return) {
						min_return = increase_rate;
						stockName = stockCol[i].getName();
						price = *(stockCol[i].getAsk().end() - 1);
					}
				}
			}
	
			it->sell(stockName, price, 100, stockCol);
	
			buy_stocks(stockCol,it);
			sell_stock(stockCol,it);
			curTime++;
		}
		cur = time(0);
	}

}
