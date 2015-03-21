#include <string>
#include "galik_socketstream.h"
#include "interact.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

void Interact::buy(string stock, double price, int amount) {
	string str = command;
	str += "BID";
	str += " ";
	str += stock;
	str += " ";
	str += to_string(price);
	str += " ";
	str += to_string(amount);
	const char* chr= str.c_str();
	system(chr);
	
}

void Interact::sell(string stock, double price, int amount) {
	string str = command;
	str += "ASK";
	str += " ";
	str += stock;
	str += " ";
	str += to_string(price);
	str += " ";
	str += to_string(amount);
	const char* chr= str.c_str();
	system(chr);
}

void Interact::clearBid(string stock) {
	string str = command;
	str += "CLEAR_BID";
	str += " ";
	str += stock;
	const char* chr= str.c_str();
	system(chr);
}

void Interact::clearAsk(string stock) {
	string str = command;
	str += "CLEAR_ASK";
	str += " ";
	str += stock;
	const char* chr= str.c_str();
	system(chr);
}
