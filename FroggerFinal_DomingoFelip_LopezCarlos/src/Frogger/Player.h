#pragma once
#include <vector>
#include "Grid.h"

using namespace std;

struct COOR {
	int x;
	int y; 
};


class Player {
private:
	//farem que el player sigui un vector al nomes tenir que afegir al final de la cua es millor utilitzar un vector que qualsevol altra estructura. 
	vector<COOR> v_player;
	int vides;
	COOR initPlayer;
	
public:

	Player(int player_x, int player_y ) {
		
		initPlayer.x = player_x;
		initPlayer.y = player_y;
		vides = 3;

		v_player.push_back(initPlayer);
		 
		
		



	}

	~Player() {

		//fer el destructor
	}

	void Player::augmentar_cua(COOR coor_player, COOR primer){

		
		v_player.push_back(coor_player);
		
		for (int i = v_player.size() - 2; i > 0; i--)
		{

			if (i==0) { v_player[i] = primer; }
			else { v_player[i] = v_player[i - 1]; }
			
			
			

		}
		std::cout << v_player[0].x << "   " << v_player[0].y << "\n";
		


	}

	COOR Player::Primera_posicio() {
	
		return v_player[0];
	
	
	
	}

	void Player::CanviaPrimera(COOR a) {
		v_player[v_player.size() - 1] = a;
	}

	int Player::Retorna_vides() {
	
	
		return vides;
	
	}

	void Player::Redueix_vides() {
		vides -= 1; 
	}

	void Player::Set_increment_x() {

		if(v_player[v_player.size() - 1].x > 0)
		v_player[v_player.size() - 1].x = v_player[v_player.size() - 1].x - 1;
		else { 
			
			vides -= 1;
			/*Reinicia_player();*/
			
		}
		
		
	}
	void Player::Set_increment_y() {

		if (v_player[v_player.size() - 1].y < 9) {

			v_player[v_player.size() - 1].y = v_player[v_player.size() - 1].y + 1;
			
		}
		else { 
			/*Reinicia_player();*/
			vides -= 1;
			
		}
	}
	void Player::Set_decrement_x() {

		if (v_player[v_player.size() - 1].x < 9)
		v_player[v_player.size() - 1].x = v_player[v_player.size() - 1].x + 1;
		else { 
			/*Reinicia_player();*/
			vides -= 1;
			
		}
	}
	void Player::Set_decrement_y() {
		
		if (v_player[v_player.size() - 1].y > 0)


			v_player[v_player.size() - 1].y = v_player[v_player.size() - 1].y - 1;


		else { /*
			Reinicia_player();*/
			vides -= 1;
			
			
		}
	}


	void Player::seguiment_cua(COOR anterior) {
	
		
		if (v_player.size() - 1 > 0) {
			for (int i = 0; i < v_player.size() - 2; i++)
			{

				v_player[i] = v_player[i + 1];



			}
			v_player[v_player.size() - 2] = anterior;
		}
	}
	
	COOR Player::Getplayer_coor() {


		return v_player[v_player.size()-1];

	}

	COOR Player::Getplayer_coor_i(int i) {


		return v_player[i];

	}
	int Player::LLargada_cua() {


		return v_player.size() - 1;

	}
	
	void Player::Creixer_cua(COOR coor) {
	
		
			v_player.push_back(coor);
	
	}


	void Player::printa() {


		std::cout << v_player.size() - 1;

	}

	void Player::Reinicia_player() {
		
		for (int i = v_player.size() - 1; i > 0 ; i--)
		{
			
			v_player.pop_back();
			
			

		}
		
		v_player[0] = initPlayer;
	
	}



	


	

		

};


