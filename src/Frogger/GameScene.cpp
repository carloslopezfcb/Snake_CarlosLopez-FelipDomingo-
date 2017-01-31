#include "GUI.h"
#include "System.hh"
#include "Logger.h"
#include "GameScene.h"
#include "IOManager.hh"
//#include "GameEngine.hh"
//#include "GameMenu.h"

#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 40
#define CELL_HEIGHT 40
#define CELL_INIT_PLAYERX 1
#define CELL_INIT_PLAYERY 5



GameScene::GameScene(void) : malla(SM.GetScene<GameMenu>()->difficulty, CELL_WIDTH, CELL_WIDTH, IOManager::LLegirXML(SM.GetScene<GameMenu>()->difficulty,1) ), _player(CELL_INIT_PLAYERX, CELL_INIT_PLAYERY), _murs(IOManager::LLegirXML(SM.GetScene<GameMenu>()->difficulty, 4),IOManager::LLegirXML(SM.GetScene<GameMenu>()->difficulty,1)) {

	

	_nexTime = TM.GetDeltaTime();
	num_pomes = 0;
	hi_ha_poma = false;
	s2_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
	poma = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::POMA };
	snake = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::SNAKE };
	
	/*t_inicial = IOManager::LLegirXML(SM.GetScene<GameMenu>()->difficulty,5);
	temps = t_inicial;
	cout << temps << "--------";*/
	velocitat_inicial = IOManager::LLegirXML(SM.GetScene<GameMenu>()->difficulty, 3);
	
	rang_pomes = IOManager::LLegirXML(SM.GetScene<GameMenu>()->difficulty, 1);

	ranking.CreateLeadBoard(20);
	//REINICIA TABLA 

	/*for (int i = 0; i <= 10; i++) {

		ranking.AddPlayer(scoreDataFile, "empty", 0);


	}*/
	level = 0;
	_nexTime_barra = 400;

	start = false;
	
}

GameScene::~GameScene(void) {

}



void GameScene::OnEntry(void) {

	
	malla.ChangeSprite_a_snake(_player.Getplayer_coor());
	for (size_t i = 0; i < 7; i++)
	{
		malla.ChangeSprite_a_MUR(_murs.Get_coor(i));
	}
	
	rang_pomes_inicials = IOManager::LLegirXML(SM.GetScene<GameMenu>()->difficulty, 2);
	cout << rang_pomes_inicials << "--------";
	/*IOManager::TestXML("XMLFile.xml");*/
	t_inicial = IOManager::LLegirXML(SM.GetScene<GameMenu>()->difficulty, 5);
	temps = t_inicial;
	/*cout << temps << "--------";*/

	colisio_paret = false;

	

}

void GameScene::OnExit(void) {
	
	string name;
	cout << '\n' << "Write your name: " << endl;
	cin >> name;
	
	//ranking.CreateAPopulationFile(scoreDataFile);//vacia el array
	
	ranking.ShowScore(scoreDataFile, false); 
	ranking.AddPlayer(scoreDataFile, name, m_score);
	ranking.ShowScore(scoreDataFile, true);
	system("pause");

}

void GameScene::Update(void) {
	

	vides_anterior = _player.Retorna_vides();


	if (SM.GetScene<GameMenu>()->difficulty =="easy")
	{
		if (num_pomes == (level*1+1))
		{
			temps = t_inicial;
			level++;
			num_pomes = 0;
			cout << level << endl;
			pas_de_lvl = _player.retorna_player();
			score_lvl = m_score;
			/*for (size_t i = 0; i < pas_de_lvl.size(); i++)
			{
				std::cout << pas_de_lvl[i].x <<"," << pas_de_lvl[i].y << endl;
			}*/
	
		}
	}
	else if (SM.GetScene<GameMenu>()->difficulty == "medium")
	{
		if (num_pomes == (level*2 + 2))
		{
			temps = t_inicial;
			level++;
			num_pomes = 0;
			cout << level << endl;
			pas_de_lvl = _player.retorna_player();
			score_lvl = m_score;
		}
	}
	else if (SM.GetScene<GameMenu>()->difficulty == "hard")
	{
		if (num_pomes == (level*3 + 3))
		{
			temps = t_inicial;
			level++;
			num_pomes = 0;
			/*cout << level << endl;*/
			pas_de_lvl = _player.retorna_player();
			score_lvl = m_score;

			
		}
	}




	
	barra = { { W.GetWidth() / 4, 10, temps/5, 40 }, ObjectID::BARRA };
	
	
	malla.ChangeSprite_a_snake(_player.Getplayer_coor());
	

	if (_player.Getplayer_coor_i(0).x != _player_anterior.x || _player.Getplayer_coor_i(0).y != _player_anterior.y) {
		
		malla.ChangeSprite_a_bg(_player_anterior);
		_player_anterior = _player.Getplayer_coor_i(0);
	}

	if (TM.GetDeltaTime() >= _nexTime_barra) {
		temps -= 6;
		if (temps <= 0) {
			_player.Redueix_vides();
			
			temps = t_inicial;
			vides_anterior = vides_anterior + 10;



			for (int i = 0; i <= _player.LLargada_cua(); i++)
			{
				if (i == _player.LLargada_cua()) { /*std::cout << _player.Getplayer_coor().x << _player.Getplayer_coor().y;*/ }

				malla.ChangeSprite_a_bg(_player.Getplayer_coor_i(i));
				malla.ChangeSprite_a_bg(anterior);

			}


			if (level == 0) {
				_player.Reinicia_player();
				m_score = 0;
				num_pomes = 0;
			}
			else {
				_player.dona_player(pas_de_lvl);
				m_score = score_lvl;
				num_pomes = 0;
			}

			vides_anterior = _player.Retorna_vides();
			direccio = 0;
		}
		_nexTime_barra = TM.GetDeltaTime() + 400;
		

	}
	if (start == false) {
		COOR tmp;
		for (size_t i = 0; i < rang_pomes_inicials; i++)
		{
			tmp.x = 3 + rand() % (rang_pomes - 3);
			tmp.y = 2 + rand() % (rang_pomes - 3);

			while (malla.Retorna_sprite(tmp) == ObjectID::MUR || malla.Retorna_sprite(tmp) == ObjectID::SNAKE) {
				tmp.x = rand() % 10 - 1;
				tmp.y = rand() % 10 - 1;
			}
			

			malla.Add_poma(tmp);
		}
		
		hi_ha_poma = true;
		start = true;
	}


	if (hi_ha_poma == false) {
		COOR tmp;

		tmp.x =  3 + rand() % (rang_pomes - 3);
		tmp.y = 2 + rand() % (rang_pomes - 3);
		
		while (malla.Retorna_sprite(tmp) == ObjectID::MUR || malla.Retorna_sprite(tmp) == ObjectID::SNAKE) {
			tmp.x = rand() % 10 - 1;
			tmp.y = rand() % 10 - 1;
		}
		std::cout<< "------" << tmp.x << tmp.y << endl; 
		
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

		

		anterior=_player.Getplayer_coor();
		/*vides_anterior = _player.Retorna_vides() ;*/

		if (direccio == 1) {
			_player.Set_decrement_x(malla.Setnum());
			
			for (int i = 0; i < _player.LLargada_cua(); i++)
			{

				if (_player.Getplayer_coor().x == _player.Getplayer_coor_i(i).x && _player.Getplayer_coor().y == _player.Getplayer_coor_i(i).y) {

					bool colisio_snake = malla.Player_collision_snake(_player.Getplayer_coor_i(i), _player.Getplayer_coor());
					if (colisio_snake) {
						_player.Redueix_vides();
						temps = t_inicial;
					}
				}
			}
		}
			
		if (direccio == 2) { 
			_player.Set_increment_x();
			
			for (int i = 0; i < _player.LLargada_cua(); i++)
			{

				if (_player.Getplayer_coor().x == _player.Getplayer_coor_i(i).x && _player.Getplayer_coor().y == _player.Getplayer_coor_i(i).y) {

					bool colisio_snake = malla.Player_collision_snake(_player.Getplayer_coor_i(i), _player.Getplayer_coor());
					if (colisio_snake) {
						_player.Redueix_vides();
						temps = t_inicial;
					}
				}
			}
		}
			
		if (direccio == 3) {
			_player.Set_decrement_y();
			
			for (int i = 0; i < _player.LLargada_cua(); i++)
			{

				if (_player.Getplayer_coor().x == _player.Getplayer_coor_i(i).x && _player.Getplayer_coor().y == _player.Getplayer_coor_i(i).y) {

					bool colisio_snake = malla.Player_collision_snake(_player.Getplayer_coor_i(i), _player.Getplayer_coor());
					if (colisio_snake) {
						_player.Redueix_vides();
						temps = t_inicial;
					}
				}
			}
		}
			
		if (direccio == 4) {
			 _player.Set_increment_y(malla.Setnum());
			
			for (int i = 0; i < _player.LLargada_cua(); i++)
			{

				if (_player.Getplayer_coor().x == _player.Getplayer_coor_i(i).x && _player.Getplayer_coor().y == _player.Getplayer_coor_i(i).y) {

					bool colisio_snake = malla.Player_collision_snake(_player.Getplayer_coor_i(i), _player.Getplayer_coor());
					if (colisio_snake) {
						_player.Redueix_vides();
						temps = t_inicial;
					}
				}
			}
		}
			


		bool colisio = malla.Player_collision(_player.Getplayer_coor());
		if (colisio) {
			_player.Redueix_vides();
			temps = t_inicial;
			/*_player.CanviaPrimera(anterior);*/
		
		}




		

		/*for (int i = 0; i < _player.LLargada_cua(); i++)
		{

			if (_player.Getplayer_coor().x == _player.Getplayer_coor_i(i).x && _player.Getplayer_coor().y == _player.Getplayer_coor_i(i).y) {
				
				bool colisio_snake = malla.Player_collision_snake(_player.Getplayer_coor_i(i), _player.Getplayer_coor());
				if (colisio_snake) {
					_player.Redueix_vides();
				}
			}
		}*/

		if (vides_anterior != _player.Retorna_vides()) {



			for (int i = 0; i <= _player.LLargada_cua(); i++)
			{
				if (i == _player.LLargada_cua()) { std::cout << _player.Getplayer_coor().x << _player.Getplayer_coor().y; }

				malla.ChangeSprite_a_bg(_player.Getplayer_coor_i(i));
				malla.ChangeSprite_a_bg(anterior);

			}


			if (level == 0) {
				_player.Reinicia_player();
				m_score = 0;
				num_pomes = 0;
			}
			else {
				_player.dona_player(pas_de_lvl);
				m_score = score_lvl;
				num_pomes = 0;
			}
			
			for (size_t i = 0; i < pas_de_lvl.size(); i++)
			{
			std::cout << "\n"<< _player.Getplayer_coor_i(i).x <<"," << _player.Getplayer_coor_i(i).y << endl;
			}

			
			vides_anterior = _player.Retorna_vides();
			direccio = 0;
		}

		
			
		
		
		bool poma = malla.Player_poma(_player.Getplayer_coor());

		if (poma) {
			num_pomes++;
			_player.augmentar_cua(_player.Getplayer_coor(), _player_anterior);
			hi_ha_poma = false;
			m_score = m_score + 100;

		}

		
		/*std::cout << temps <<endl;*/


		if (_player.Retorna_vides() <= 0) {
			OnExit();

		}
		_player.seguiment_cua(anterior);

		
		/*_nexTime = TM.GetDeltaTime() + velocitat_inicial - 20- m_score/3;*/// (tiempo que quieres que espere)
		_nexTime = TM.GetDeltaTime() + velocitat_inicial - (m_score / 8);
		/*cout << "Time : " << _nexTime << endl;*/
	
	}
	//cout << "Time : " << TM.GetDeltaTime() << endl;

	

	
	

	


}

void GameScene::Draw(void) {
	
	s2_background.Draw();
	
	string score;	// number to be converted to a string
	ostringstream convert;   // stream used for the conversion
	convert << m_score;      // insert the textual representation of 'Number' in the characters in the stream
	score = convert.str(); // set 'Result' to the contents of the stream
	//cout << score;


	GUI::DrawTextSolid<FontID::CANDY>(score,
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 115, 0, 180 });



	string level_;	// number to be converted to a string
	ostringstream convert2;   // stream used for the conversion
	convert2 << level;      // insert the textual representation of 'Number' in the characters in the stream
	level_ = convert2.str();
	
	GUI::DrawTextSolid<FontID::CANDY>("Level:",
	{ int(W.GetHeight()*.85f), int(W.GetHeight()*.1f), 1, 1 },
	{ 115, 0, 180 });


	GUI::DrawTextSolid<FontID::CANDY>(level_,
	{ int(W.GetHeight()*.95f), int(W.GetHeight()*.1f), 1, 1 },
	{ 115, 0, 180 });
	
	barra.Draw();
	
	malla.Draw();
	

}
