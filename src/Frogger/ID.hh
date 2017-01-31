/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : int {
	POMA,
	SNAKE,/*TERRA,*/ /*PARET,*/
	BG_00,
	MUR,
	BARRA,// Background IDs
	 //de tots els objectes i personatge
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator >> (std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering
enum class FontID : int {
	ARIAL,
	CANDY,
	FACTORY,
	MAX
};
