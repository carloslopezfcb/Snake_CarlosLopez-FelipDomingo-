

#pragma once
#include "Sprite.h"
#include "InputManager.h"
#include "Player.h"


class Grid {
private:
	Sprite** cela;
	int num;
public:

	Grid(std::string dificultat, int cellWidth , int cellHeight)  {

		


		if (dificultat == "easy") num = 10;
		if (dificultat == "medium") num = 50;
		if (dificultat == "hard") num = 100;

		cela = new Sprite*[num];
		for (int i = 0; i < num; i++)
		{
			cela[i] = new Sprite[num];
		}

		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < num; j++)
			{
				//ser
				cela[i][j].transform = { j * ( + 50) + ((W.GetWidth() - cellWidth*num) >> 1),
								i * (cellHeight + 5) + ((W.GetHeight() - cellHeight*num) >> 1),
								cellWidth, cellHeight };
				cela[i][j].objectID = ObjectID::BG_00;


			}


		}




	
	}
	
	~Grid() {
		
	//fer el destructor
	}
	
	void Grid::ChangeSprite_a_snake(COOR player) {
	
		cela[player.x][player.y].objectID = ObjectID::SNAKE;

	}
	void Grid::ChangeSprite_a_POMA(COOR coor) {

		cela[coor.x][coor.y].objectID = ObjectID::POMA;

	}

	void Grid::ChangeSprite_a_MUR(COOR coor) {

		cela[coor.x][coor.y].objectID = ObjectID::MUR;

	}

	void Grid::ChangeSprite_a_bg(COOR coor) {

		cela[coor.x][coor.y].objectID = ObjectID::BG_00;

	}
	int Grid::Setnum() {

		return num;

	}
	
	void Grid::Draw() {

		for (int i = 0; i < num; ++i) {
			for (int j = 0; j < num; ++j) {

				cela[i][j].Draw();


			}
		}

	}


	bool Grid::Player_collision(COOR coor) {
	
		if (cela[coor.x][coor.y].objectID == ObjectID::MUR ) { return true; }
		else return false;
	
	}
	bool Grid::Player_collision_snake( COOR coordenada_actual, COOR cap) {

		if (coordenada_actual.x == cap.x && coordenada_actual.y == cap.y) { return true; }
		else { return false; }

	}


	bool Grid::Player_poma(COOR coor) {

		if (cela[coor.x][coor.y].objectID == ObjectID::POMA) { return true; }
		else return false;

	}

	void Grid::Add_poma(COOR coor) {
	
		cela[coor.x][coor.y].objectID = ObjectID::POMA;
		
	}



};


