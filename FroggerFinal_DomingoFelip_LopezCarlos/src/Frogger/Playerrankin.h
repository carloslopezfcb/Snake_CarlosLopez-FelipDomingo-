#pragma once

#include <string>
#include <exception>			//Management of exceptions
#include <iostream>				//Management of cin and cout
#include <stdlib.h>				//Management of random numbers: srand, rand 
#include <cstdlib>				//Management of system functions such as pause
#include <fstream>				//Management of files
class PlayerR
{
	char _name[100];
	int _score;


public:
	PlayerR();

	PlayerR(std::string name, int score);
	PlayerR(PlayerR & p);

	int ReturnScore();
	void UpdateScore(int score);
	void UpdateName(std::string name);
	std::string ReturnName();

	friend std::ostream& operator<<(std::ostream& os, const PlayerR& p);
	friend std::istream& operator>>(std::istream& is, PlayerR& p);

	
	friend std::ofstream& operator<<(std::ofstream& os, const PlayerR & p);
	friend std::ifstream& operator>>(std::ifstream& is, PlayerR & p);

	~PlayerR();
};

