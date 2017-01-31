#include "GUI.h"
#include "System.hh"
#include "Logger.h"
#include "GameMenu.h"
#include "GameScene.h"

#pragma region TODO



using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

GameMenu::GameMenu(void) {
	// carguem els sprits 
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

GameMenu::~GameMenu(void) {
}

void GameMenu::OnEntry(void) {

	
}

void GameMenu::OnExit(void) {
	
	Println("exit");
	

}

void GameMenu::Update(void) {



	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();




	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());

		if (mouseCoords.x > 536 && mouseCoords.x < 671 && mouseCoords.y>852 && mouseCoords.y < 927) {
			OnExit();
		}
		else if (mouseCoords.x > 503 && mouseCoords.x < 693 && mouseCoords.y>259 && mouseCoords.y < 350) {
			Println("easy");

			SM.SetCurScene<GameScene>();
		}
		else if (mouseCoords.x > 495 && mouseCoords.x < 709 && mouseCoords.y>466 && mouseCoords.y < 536) {
			Println("medium");

		}
		else if (mouseCoords.x > 513 && mouseCoords.x < 694 && mouseCoords.y>660 && mouseCoords.y < 728) {
			Println("hard");

		}

	}

	// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");
	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
}

void GameMenu::Draw(void) {

	// pinta el backgraund 
	m_background.Draw();


	//pinta els text 
	//DrawTextBlended: hi ha diferents utilitzo aquet perque no te color de fondo i queda millor
	//en el GUI.h hi esta tot

	GUI::DrawTextBlended<FontID::CANDY>("SNAKE",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.05f), 1, 1 },
	{ 0, 255, 0 });
	GUI::DrawTextBlended<FontID::CANDY>("Easy",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 },
	{ 115, 0, 180 });
	GUI::DrawTextBlended<FontID::CANDY>("Medium",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.5f), 1, 1 },
	{ 115, 0, 180 });
	GUI::DrawTextBlended<FontID::CANDY>("Hard",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.7f), 1, 1 },
	{ 115, 0, 180 });
	GUI::DrawTextBlended<FontID::CANDY>("Exit",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 });
}
