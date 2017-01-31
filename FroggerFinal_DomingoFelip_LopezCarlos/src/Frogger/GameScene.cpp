#include "GUI.h"
#include "System.hh"
#include "Logger.h"
#include "GameScene.h"
#include "IOManager.hh"


#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 40
#define CELL_HEIGHT 40
#define CELL_INIT_PLAYERX 1
#define CELL_INIT_PLAYERY 5

GameScene::GameScene(void) : malla("easy", CELL_WIDTH, CELL_HEIGHT),_player(CELL_INIT_PLAYERX,CELL_INIT_PLAYERY), _murs(7){


	_nexTime = TM.GetDeltaTime();
	num_pomes = 0;
	hi_ha_poma = false;
	s2_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	poma = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::POMA };
	snake = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::SNAKE };
	
	t_inicial = 500;
	temps = t_inicial;
	
	
}

GameScene::~GameScene(void) {

}

void GameScene::OnEntry(void) {

	

	malla.ChangeSprite_a_snake(_player.Getplayer_coor());
	for (size_t i = 0; i < 7; i++)
	{
		malla.ChangeSprite_a_MUR(_murs.Get_coor(i));
	}
	

	
	IOManager::TestXML("XMLFile.xml");
	

	

	

}

void GameScene::OnExit(void) {


	system("pause");

}

void GameScene::Update(void) {
	
	
	
	barra = { { W.GetWidth() / 4, 859, temps, 40 }, ObjectID::BARRA };
	
	/*for (int i = _player.LLargada_cua(); i > 0; i--)
	{
		
		malla.ChangeSprite_a_snake(_player.Getplayer_coor_i(i)); 

	}*/
	malla.ChangeSprite_a_snake(_player.Getplayer_coor());
	/*
	_player.printa();*/

	if (_player.Getplayer_coor_i(0).x != _player_anterior.x || _player.Getplayer_coor_i(0).y != _player_anterior.y) {
		
		malla.ChangeSprite_a_bg(_player_anterior);
		_player_anterior = _player.Getplayer_coor_i(0);
	}

	if (hi_ha_poma == false) {
		COOR tmp;

		tmp.x = rand() % 10 - 1;
		tmp.y = rand() % 10 - 1;
		/*std::cout << tmp.x << ' ';
		std::cout << tmp.y;*/

		malla.Add_poma(tmp);
		hi_ha_poma = true;
	}
	
	

	if (IM.IsKeyDown<KEY_BUTTON_DOWN>() && direccio !=2 )
		direccio = 1;
	if (IM.IsKeyDown<KEY_BUTTON_UP>() && direccio != 1)
		direccio = 2;
	if (IM.IsKeyDown<KEY_BUTTON_LEFT>() && direccio != 4)
		direccio = 3;
	if (IM.IsKeyDown<KEY_BUTTON_RIGHT>() && direccio != 3)
		direccio = 4;
	
	//std::cout << direccio;

	if (TM.GetDeltaTime() >= _nexTime) {

		

		COOR anterior=_player.Getplayer_coor();
		int vides_anterior = _player.Retorna_vides() ;

		if (direccio == 1)
			_player.Set_decrement_x();
		if (direccio == 2) 
			_player.Set_increment_x();
		if (direccio == 3)
			_player.Set_decrement_y();
		if (direccio == 4)
			_player.Set_increment_y();


		bool colisio = malla.Player_collision(_player.Getplayer_coor());
		if (colisio) {
			_player.Redueix_vides();
			_player.CanviaPrimera(anterior);
		
		}




		

		for (int i = 0; i < _player.LLargada_cua(); i++)
		{

			if (_player.Getplayer_coor().x == _player.Getplayer_coor_i(i).x && _player.Getplayer_coor().y == _player.Getplayer_coor_i(i).y) {
				
				bool colisio_snake = malla.Player_collision_snake(_player.Getplayer_coor_i(i), _player.Getplayer_coor());
				if (colisio_snake) {
					_player.Redueix_vides();
				}
			}
		}

		if (vides_anterior != _player.Retorna_vides()) {



			for (int i = 0; i <= _player.LLargada_cua(); i++)
			{
				if (i == _player.LLargada_cua()) { std::cout << _player.Getplayer_coor().x << _player.Getplayer_coor().y; }

				malla.ChangeSprite_a_bg(_player.Getplayer_coor_i(i));
				malla.ChangeSprite_a_bg(anterior);

			}



			_player.Reinicia_player();

			direccio = 0;
		}

		
			
		
		
		bool poma = malla.Player_poma(_player.Getplayer_coor());

		if (poma) {
			num_pomes++;
			_player.augmentar_cua(_player.Getplayer_coor(), _player_anterior);
			hi_ha_poma = false;
		}

		temps -= 2;
		if (temps == 0) {
			_player.Redueix_vides();
			temps = t_inicial;
		}



		if (_player.Retorna_vides() <= 0) {
			OnExit();

		}
		_player.seguiment_cua(anterior);

		
		_nexTime = TM.GetDeltaTime() + 200;// (tiempo que quieres que espere)

		/*cout << "Time : " << _nexTime << endl;*/
	
	}
	//cout << "Time : " << TM.GetDeltaTime() << endl;

	

	
	

	


}

void GameScene::Draw(void) {
	
	
	
	
	s2_background.Draw();
	barra.Draw();
	
	malla.Draw();
	

}
