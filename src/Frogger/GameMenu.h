#pragma once


#include "Scene.h"


// GameScene class with the main gameplay mode
class GameMenu : public Scene {
public:
	std::string difficulty;
	explicit GameMenu();
	~GameMenu() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:

	Sprite m_background;
	int m_score{ 0 };
};