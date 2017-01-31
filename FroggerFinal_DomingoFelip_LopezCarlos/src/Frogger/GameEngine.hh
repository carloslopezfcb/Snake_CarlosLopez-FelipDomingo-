#pragma once
#include "System.hh"

#pragma region GAME_SCENES 
#include "GameMenu.h"
#include <iostream>
#include "GameScene.h"
#pragma endregion TODO

namespace GameEngine {

	// carreguem les imatges i les fonts de lletra 
	void LoadMedia(void) {
		//comensem a la carpeta fnt o gfx gracies al RESOURCE_PATH de Resource.h (fa el codi mes llegible)
		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 40);
		R.LoadFont<FontID::CANDY>("fnt/candy.ttf", 50);
		R.LoadFont<FontID::FACTORY>("fnt/candsb.ttf", 80);
	
		R.LoadTexture<ObjectID::BG_00>("gfx/bg.jpg");
		R.LoadTexture<ObjectID::POMA>("gfx/manzana.jpg");
		R.LoadTexture<ObjectID::SNAKE>("gfx/snake.png");
		R.LoadTexture<ObjectID::MUR>("gfx/Mur.png");
		R.LoadTexture<ObjectID::BARRA>("gfx/barra.jpg");
	}

	// affegim les escenes del joc

	void AddScenes(void) {
		SM.AddScene<GameMenu>();
		SM.AddScene<GameScene>();

		SM.SetCurScene<GameMenu>();
	
	
	
	
	}
	

	//run the game i especifica el nom de la finestra del joc i les dimensions
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		//Amb Window::Instance crea una finestra, aquesta finestra es un Singleton 
		Window::Instance(std::move(name), screenWidth, screenHeight); // Initialize window Singleton instance for the first time
		LoadMedia(); // Loads the resource assets
		AddScenes(); // Loads the scenes

		bool m_isRunning{ true }; // Decides if the game loop is running

		Scene *&m_curScene(SM.GetCurScene()); // Defines a reference to a pointer that points to the current scene pointer (mindblown)

		

		while (/*!IM.HasQuit() && */m_isRunning) { // Checks while game's still playable
			TM.FPSBegin(); // Calculates the time difference for deltaTime and FPS limiting purposes
		#pragma region GAME_UPDATE
			

				switch (m_curScene->GetState()) { // Check for the state of the screen
				case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; // Updates the InputManager and the current scene
				case SceneState::EXIT:		m_isRunning = false; std::cout << "exit"; break; // Triggers an end of the game looping
				case SceneState::SLEEP: default:;
				}


			

		#pragma endregion
		#pragma region GAME_DRAW
			TM.FPSEnd([&]() { // Limits the FPS rendering with a lambda function as the parameter that draws the whole game
				if (m_curScene->CheckState<SceneState::RUNNING>()) { // If screen object exists and its state is running
					R.Clear();			// Clear the screen buffer
					m_curScene->Draw(); // Call the draw method of the scene
					R.Render();			// Update the screen buffer with all sprites that were pushed
				}});
		#pragma endregion
		}
	
	
	
	
	}





}