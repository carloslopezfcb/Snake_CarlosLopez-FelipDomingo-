#pragma once
#include "Scene.h"
#include "Grid.h"
#include "Mur.h"
#include "Player.h"
#include "Leaderboard.h"
#include "GameMenu.h"

// GameScene class with the main gameplay mode
class GameScene : public Scene {
public:
	explicit GameScene();
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	int readXML(int i);
	
private:
	//Grid m_grid;
	Sprite s2_background;
	Sprite poma;
	Sprite snake;
	Sprite barra;

	Grid malla;
	Player _player;
	COOR _player_anterior;
	Mur _murs;
	bool hi_ha_poma;
	int direccio;
	int num_pomes;
	float _nexTime;
	float pppp;
	COOR inici;
	int temps;
	int t_inicial;
	int m_score{ 0 };
	Leaderboard ranking;
	char scoreDataFile[100] = "scores.bin";
	int velocitat_inicial;
	int rang_pomes;
	int rang_pomes_inicials;
	float _nexTime_barra;
	COOR anterior;
	int vides_anterior;
	int level;
	bool start;
	bool colisio_paret;

	int score_lvl;

	vector<COOR> pas_de_lvl;

};