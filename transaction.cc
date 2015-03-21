#include <string>
#include "galik_socketstream.h"
#include "interact.h"
#include "stock.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include "pthread.h"
#include <map>

using namespace std;

int highestDividend(vector<Stock> &collection) {
	
	long double maxDiv = 0;
	int maxid = 0;
	for (int id = 0; id < 10; id++) {
		long double divRatio = (collection[id].getdivRatio())[collection[id].getdivRatio().size()-1];
		long double netWorth = (collection[id].getnetWorth())[collection[id].getnetWorth().size()-1];
		long double divv = divRatio * netWorth;
		if (divv > maxDiv) {
			macDiv = divv;
			maxid = id;
		}
	}
	return id;	
}

bool dividend(Interact &it, vector<Stock> &collection) {
	time_t cur = time(0);
	time_t last = cur;
	
	int i = 0;
	while (i < 3) {
		if (cur != last) {
			sleep(2);
			last = cur;
			it.buy(highestDividend(), )
			i++;
		}
		cur = time(0);
	}
	return true;
}

/*int main() {
	Interact* it = new Interact();
	//it->buy("AAPL", 19.09, 20);
	//it->sell("AAPL", 20, 10);
	//it->clearBid("APPL");
	//it->clearAsk("APPL");
	cout << it->cash();
	
	//system("./codeb ShakeItOff_MLC weareyoung codebb.cloudapp.net 17429 SECURITIES > securities.txt");
	
	//dividend(it);
}*/
