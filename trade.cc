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

Stock S1 = new Stock; Stock S2 = new Stock;
Stock S3 = new Stock; Stock S4 = new Stock;
Stock S5 = new Stock; Stock S6 = new Stock;
Stock S7 = new Stock; Stock S8 = new Stock;
Stock S9 = new Stock; Stock S10 = new Stock;
vector<Stock> collection;
collection.push_back(S1); collection.push_back(S6);
collection.push_back(S2); collection.push_back(S7);
collection.push_back(S3); collection.push_back(S8);
collection.push_back(S4); collection.push_back(S9);
collection.push_back(S5); collection.push_back(S10);

void buy_stocks(vector<Stock> collection) {
	for(int i = 0; i < 10; i++) {
		if()
	}
}

void sell_stock(vector<Stock> collection) {
	for(int i = 0; i < 10; i++) {
		//sell the stock when the price has decreased by a certain percentage
		cur_ask_price =   *(collection[i].ask.end() - 1);
		initial_bought_price = collection[i].bid[last_time_buy];
		decrese_rate = (cur_ask_price - initial_bought_price) / initial_bought_price;
		if(decrease_rate >= 0.2) {
			sell(#i stock, all);
		}
		prev_ask_price = *(collection[i].ask.end() - 2);
		period_increase_rate = (cur_ask_price - prev_ask_price) / prev_ask_price;
		if(period_increase_rate > 0.2) {
			sell(#i stock, all);
		}
	}
}

int main() {
	Use 1000 dollars buy each of the stock;
	sleep(30);
	Transfer 800 of them; 700 for trading; 100 for dividends;
	
	while(true) {
		buy_stocks(collection);
		sell_stock(collection);
	}
	
}