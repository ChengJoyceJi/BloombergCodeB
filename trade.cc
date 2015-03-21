#include <string>
#include "galik_socketstream.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stock.h>
#include <pthread.h>

using namespace std;
using namespace galik;
using namespace galik::net;

Stock S1 = new Stock("AAPL",1); Stock S2 = new Stock("ATVI",2);
Stock S3 = new Stock("EA",3); Stock S4 = new Stock("FB",4);
Stock S5 = new Stock("GOOG",5); Stock S6 = new Stock("MSFT",6);
Stock S7 = new Stock("SNY",7); Stock S8 = new Stock("TSLA",8);
Stock S9 = new Stock("TWTR",9); Stock S10 = new Stock("XOM",10);
vector<Stock> collection;
collection.push_back(S1); collection.push_back(S6);
collection.push_back(S2); collection.push_back(S7);
collection.push_back(S3); collection.push_back(S8);
collection.push_back(S4); collection.push_back(S9);
collection.push_back(S5); collection.push_back(S10);

string get_stockName(int i) {
	for(int m = 0; m < 10; m ++) {
		if(collection[m].getID() == i) {
			stockName = collection[m].getName();
		}
	}
	return stockName;
}

void buy_stocks(vector<Stock> collection, Interact* it) {
	for(int i = 0; i < 10; i++) {
		//buy the stock if it keeps decreasing in three periods and suddenly start to up
		if(collection[i].ask.size() > 16) {
			cur_ask_price = *(collection[i].ask.end() - 1);
			prev_ask_price_1 = *(collection[i].ask.end() - 2);
			prev_ask_price_2 = *(collection[i].ask.end() - 4);
			prev_ask_price_3 = *(collection[i].ask.end() - 6);
			prev_ask_price_4 = *(collection[i].ask.end() - 8);
			if(prev_ask_price_1 < prev_ask_price_2 && prev_ask_price_2 < prev_ask_price_3 && 
			   prev_ask_price_3 < prev_ask_price_4) {
				if(cur_ask_price > prev_ask_price_1) {
					buy(get_stockName[i], it->cash());
				}
			}
		}	
		//
	}
}

void sell_stock(vector<Stock> collection, Interact* it) {
	for(int i = 0; i < 10; i++) {
		//sell the stock when the price has decreased by a certain percentage
		cur_ask_price = *(collection[i].ask.end() - 1);
		initial_bought_price = collection[i].bid[last_time_buy];
		decrese_rate = (initial_bought_price - cur_ask_price) / initial_bought_price;
		if(decrease_rate >= 0.1) {
			it->sell(get_stockName[i], collection[i].getShare());
		}
		//sell the stock when the price has increased too dramatically in the last second
		prev_ask_price = *(collection[i].ask.end() - 2);
		period_increase_rate = (cur_ask_price - prev_ask_price) / prev_ask_price;
		if(period_increase_rate > 0.1) {
			it->sell(get_stockName[i], collection[i].getShare());
		}
		//sell the stock if it keeps increasing in three periods and suddenly start to fall
		if(collection[i].ask.size() > 16) {
			cur_ask_price = *(collection[i].ask.end() - 1);
			prev_ask_price_1 = *(collection[i].ask.end() - 2);
			prev_ask_price_2 = *(collection[i].ask.end() - 4);
			prev_ask_price_3 = *(collection[i].ask.end() - 6);
			prev_ask_price_4 = *(collection[i].ask.end() - 8);
			if(prev_ask_price_1 < prev_ask_price_2 && prev_ask_price_2 < prev_ask_price_3 && prev_ask_price_3 < prev_ask_price_4) {
				if(cur_ask_price > prev_ask_price_1) {
					sell(get_stockName[i], collection[i].getShare())
				}
			}
		}				
	}
}

int main() {
	Interact* it = new Interact();
	it->buy("AAPL", 100); it->buy("ATVI", 100);
	it->buy("EA", 100);   it->buy("FB", 100);
	it->buy("GOOG", 100); it->buy("MSFT", 100);
	it->buy("SNY", 100);  it->buy("TSLA", 100);
	it->buy("TWTR", 100); it->buy("XOM", 100);
	sleep(30);
	//Transfer 100 for dividends;
	min_return = 0; string stockName;
	for(int i = 0; i < 10; i++) {
		//sell the stock when the price has decreased by a certain percentage
		cur_ask_price =   *(collection[i].ask.end() - 1);
		initial_bought_price = collection[i].bid[last_time_buy];
		increase_rate = (cur_ask_price - initial_bought_price) / initial_bought_price;	
		if(i == 0) {
			min_return = increase_rate;
			stockName = collection[i].getName();
		} else {
			if(increase_rate < min_return) {
				min_return = increase_rate;
				stockName = collection[i].getName();
			}
		}
	}
	
	sell(stockName, 100)
	
	while(true) {
		buy_stocks(collection,it);
		sell_stock(collection,it);
	}
	
}