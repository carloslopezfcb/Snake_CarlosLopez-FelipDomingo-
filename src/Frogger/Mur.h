#pragma once
#include <vector>
#include "Grid.h"
#include "Player.h"

using namespace std;


//MURS
class Mur {
private:
	COOR *Murs;

public:

	Mur(int num, int caselles) {

		Murs = new COOR[num];
		for (int i = 0; i < num; i++)
		{
			
			Murs[i].x = 1 + rand() % (caselles - 2);
			Murs[i].y = 1 + rand() % (caselles - 2);


		}





	}

	~Mur() {


	}

	COOR Mur::Get_coor(int i) {
	
		return Murs[i];
	
	}
};




	