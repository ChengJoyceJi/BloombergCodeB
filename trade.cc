#include <string>
#include "galik_socketstream.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "stock.h"
#include "interact.h"
#include <pthread.h>
#include <fstream>

using namespace std;
using namespace galik;
using namespace galik::net;


vector<string> nameCol;
vector<Stock> stockCol;

int curTime;

string get_stockName(int i) {
	string stockName;
	for(int m = 0; m < nameCol.size(); m ++) {
		if(stockCol[m].getID() == i) {
			stockName = stockCol[m].getName();
		}
	}
	return stockName;
}

int highestDividend(vector<Stock> &collection) {
	
	long double maxDiv = 0;
	int maxid = 0;
	for (int id = 0; id < nameCol.size(); id++) {
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
	for(int i = 0; i < nameCol.size(); i++) {
		//buy the stock if it keeps decreasing in three periods and suddenly start to up
		if(stockCol[i].getAsk().size() > 8) {
			long double cur_ask_price = *(stockCol[i].getAsk().end() - 1);
			long double prev_ask_price_1 = *(stockCol[i].getAsk().end() - 2);
			long double prev_ask_price_2 = *(stockCol[i].getAsk().end() - 4);
			long double prev_ask_price_3 = *(stockCol[i].getAsk().end() - 5);
			long double prev_ask_price_4 = *(stockCol[i].getAsk().end() - 6);
			if(prev_ask_price_1 < prev_ask_price_2 && prev_ask_price_2 < prev_ask_price_3 && 
			   prev_ask_price_3 < prev_ask_price_4) {
				if(cur_ask_price > prev_ask_price_1) {
					it->buy(get_stockName(i), it->cash() * 0.9, stockCol);
					stockCol[i].setboughtTime(curTime);
					int current_shares = stockCol[i].getShare() + it->cash() * 0.9 / *(stockCol[i].getAsk().end() - 1);
					stockCol[i].setShare(current_shares);
				}
			}
		}	
		//
	}
}

void sell_stock(vector<Stock> stockCol, Interact* it) {
	for(int i = 0; i < nameCol.size(); i++) {
		//sell the stock when the price has decreased by a certain percentage
		long double cur_ask_price = *(stockCol[i].getAsk().end() - 1);
		long double initial_bought_price = (stockCol[i].getAsk()[stockCol[i].getboughtTime()]);
		long double decrease_rate = (initial_bought_price - cur_ask_price) / initial_bought_price;
		if(decrease_rate >= 0.05) {
			cout << "sell: " << stockCol[i].getShare() << endl;
			it->sell(get_stockName(i), *(stockCol[i].getBid().end() - 1), stockCol[i].getShare(),stockCol);
			stockCol[i].setShare(0);
		}
		//sell the stock when the price has increased too dramatically in the last second
		long double prev_ask_price = *(stockCol[i].getAsk().end() - 2);
		long double period_increase_rate = (cur_ask_price - prev_ask_price) / prev_ask_price;
		if(period_increase_rate > 0.05) {
			cout << "sell: " << stockCol[i].getShare() << endl;
			it->sell(get_stockName(i), *(stockCol[i].getBid().end() - 1), stockCol[i].getShare(), stockCol);
			stockCol[i].setShare(0);
		}
		//sell the stock if it keeps increasing in three periods and suddenly start to fall
		if(stockCol[i].getAsk().size() > 8) {
			cout << "sell: " << stockCol[i].getShare() << endl;
			cur_ask_price = *(stockCol[i].getAsk().end() - 1);
			long double prev_ask_price_1 = *(stockCol[i].getAsk().end() - 2);
			long double prev_ask_price_2 = *(stockCol[i].getAsk().end() - 4);
			long double prev_ask_price_3 = *(stockCol[i].getAsk().end() - 6);
			long double prev_ask_price_4 = *(stockCol[i].getAsk().end() - 8);
			if(prev_ask_price_1 < prev_ask_price_2 && prev_ask_price_2 < prev_ask_price_3 && prev_ask_price_3 < prev_ask_price_4) {
				if(cur_ask_price > prev_ask_price_1) {
					it->sell(get_stockName(i), *(stockCol[i].getBid().end() - 1), stockCol[i].getShare(), stockCol);
					stockCol[i].setShare(0);
				}
			}
		}				
	}
}

int main() {
	system("./codeb ShakeItOff_MLC weareyoung codebb.cloudapp.net 17429 SECURITIES > s.txt");
	string temp;
	ifstream S("s.txt");
	if (S.is_open()) {
		S >> temp;
		while (S >> temp) {

			//S >> temp;

			nameCol.push_back(temp);
			cout << temp;
			S >> temp;
			S >> temp;
			S >> temp;
		}
	}
	S.close();

	
	cout << "gg" << endl;
	/*Stock S1 = Stock(nameCol[0],1); Stock S2 = Stock(nameCol[1],2);
	Stock S3 = Stock(nameCol[2],3); Stock S4 = Stock(nameCol[3],4);
	Stock S5 = Stock(nameCol[4],5); Stock S6 = Stock(nameCol[5],6);
	Stock S7 = Stock(nameCol[6],7); Stock S8 = Stock(nameCol[7],8);
	Stock S9 = Stock(nameCol[8],9); Stock S10 = Stock(nameCol[9],10);*/
		

	curTime = 0;
	time_t cur = time(0);
	time_t last = cur;

	
	for(int l = 0; l < nameCol.size();l++) {
		stockCol.push_back(Stock(nameCol[l],l + 1));
	}
	

	
	for (int i = 0; i < nameCol.size(); i++) {
		stockCol.push_back(Stock(nameCol[i],i + 1)); 
	}
	
	cout << stockCol[1].getName() << endl;

	for(int n = 0;n < nameCol.size(); n++) {
		stockCol[n].getInfo();
	}	
	

	Interact* it = new Interact();
	for(int k = 0; k < nameCol.size();k++) {
		it->buy(nameCol[k], 100, stockCol);
		int current_shares = 100 / *(stockCol[k].getAsk().end() - 1);
		stockCol[k].setShare(current_shares);
	}
	
	while (curTime < 300) {
		if (cur != last) {
			
			for(int n = 0; n < nameCol.size(); n++) {
				stockCol[n].getInfo();
			}

			last = cur;
			//sleep(15);
			cout << "cash: " << it->cash() << endl;
			//Transfer 100 for dividends;
			long double min_return = 0; 
			string stockName;
			long double price;
			for(int i = 0; i < nameCol.size(); i++) {
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
