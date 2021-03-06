#include "Playerrankin.h"



PlayerR::PlayerR()
{
	_name[0] = '\0';
	_score = 0;
}

PlayerR::PlayerR(std::string name, int score)
{

	strcpy_s(_name, name.c_str());
	_score = score;
}

PlayerR::PlayerR(PlayerR & p)
{

	strcpy_s(_name, p._name);
	_score = p._score;
}

int PlayerR::ReturnScore()
{
	return _score;
}

void PlayerR::UpdateScore(int score)
{
	_score = score;
}

void PlayerR::UpdateName(std::string name)
{
	strcpy_s(_name, name.c_str());
}

std::string PlayerR::ReturnName()
{


	return std::string(_name);
}


std::ostream& operator<<(std::ostream& os, const PlayerR & p) {
	os << "Name:" << p._name << ", score:" << p._score;
	return os;
}

/**
* Input operator is overloaded to allow you to use "cin>>p;". In this implementation we write inside the question that is asked to the user.
* @param is is the input operator
* @param p is the object (person) that will be used inside the function
*/
std::istream& operator>>(std::istream& is, PlayerR & p) {
	//Ask data to the user
	std::cout << "What's your name?";
	is >> p._name;
	is >> p._score;
	return is;
}


std::ofstream& operator<<(std::ofstream& os, const PlayerR & p) {
	os << p._name << " ";
	os << p._score;
	return os;
}

/**
* Input operator is overloaded to allow you to use "ifstream>>p"
* @param is is the input operator
* @param p is the object (person) that will be used inside the function
*/
std::ifstream& operator>>(std::ifstream& is, PlayerR & p) {
	is >> p._name;
	is >> p._score;

	return is;
}

PlayerR::~PlayerR()
{
}
