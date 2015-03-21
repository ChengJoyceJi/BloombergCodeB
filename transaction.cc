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

map<string, double> divi;

string highestDividend(vector<Stock> &collection) {
	
	
}

/*bool dividend(Interact &it, vector<Stock> &collo) {
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
}*/

int main() {
	Interact* it = new Interact();
	//it->buy("AAPL", 19.09, 20);
	//it->sell("AAPL", 20, 10);
	//it->clearBid("APPL");
	//it->clearAsk("APPL");
	
	//system("./codeb ShakeItOff_MLC weareyoung codebb.cloudapp.net 17429 SECURITIES > securities.txt");
	
	//dividend(it);
}
