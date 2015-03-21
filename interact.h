#ifndef _INTERACT_H
#define _INTERACT_H

#include <string>
#include <iostream>
#include <vector>

class Interact {
	
	const std::string username;
	const std::string password;
	const std::string host;
	const std::string port;
	std::string command;
	
public:	
	
	Interact(): username("ShakeItOff_MLC"), password("weareyoung"), host("codebb.cloudapp.net"), port("17429"), command("./codeb "){
		command += username;
		command += " ";
		command += password;
		command += " ";
		command += host;
		command += " ";
		command += port;
		command += " ";
		system("g++ client.m.cpp -o codeb");
	}
	
	double cash();
	
	// bid
	void buy(std::string stock, double price, int amount);
	
	void buy(std::string stock, double money, std::vector<Stock> &collection);
	
	//ask
	void sell(std::string stock, double price, int amount);
	
	void clearBid(std::string stock);
	
	void clearAsk(std::string stock);

};

#endif