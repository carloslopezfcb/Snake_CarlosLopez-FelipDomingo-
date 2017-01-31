#pragma once
#include "Scene.h"
#include "Grid.h"
#include "Mur.h"
#include "Player.h"

// GameScene class with the main gameplay mode
class GameScene : public Scene {
public:
	explicit GameScene();
	~GameScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
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
};