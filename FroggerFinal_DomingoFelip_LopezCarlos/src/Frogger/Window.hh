//Aquesta classe es un singleton ja que en el joc només i pot haver una finestra. 
#pragma once
#include <string>
#include <SDL/SDL.h>
#include "Assert.hh"

//garantizar que una clase sólo tenga una instancia y proporcionar un punto de acceso global a ella.
#define W Window::Instance()

// Clase ventana para almacenar toda la información relacionada con la interfaz de la pantalla del juego
class Window {
	//CONSTRUCTOR: nom, amplada i llargada
	//CONSTRUCTOR: fa us de la classe ASSERT

	Window(const std::string &&name, int &&screenWidth, int &&screenHeight) : m_name(name), m_screenWidth(screenWidth), m_screenHeight(screenHeight) {
		
		//SDL_Init: serveix per inicialitzar funcions de SDL, no tenim per a que inicialitzau tot.
		//SDL_INIT_EVERYTHING: en aquest cas ho inicialitzem tot, no tenim perque, podem fer nomes video etc...
		ASSERT(!SDL_Init(SDL_INIT_EVERYTHING));
		ASSERT(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"));

		//Creem una finestra
		// SDL_CreateWindow: creem una finestra(part gràfica del joc), 
		//SDL_WINDOW_SHOWN: hi ha de diferents, Pantalla completa etc.. 
		m_SDLWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		//EN el cas que m_SDLWindow sigui nulla dona codi de error. 
		ASSERT(m_SDLWindow != nullptr);
	}
	//???????????????????????
	Window(const Window &rhs) = delete;
	Window &operator=(const Window &rhs) = delete;
public:
	inline static Window &Instance(std::string &&name = "", int &&screenWidth = 0, int &&screenHeight = 0) {
		static Window window(std::move(name), std::move(screenWidth), std::move(screenHeight));
		return window;
	}

	//Destructor de la classe
	~Window() {
		SDL_DestroyWindow(m_SDLWindow), m_SDLWindow = nullptr; //Destrueix la finestra 
		SDL_Quit(); //Tanca-ho tot.
	}
	//INLINE: accelera el programa si la funcion inline es llamada regularmente, no se utiliza en funciones muy largas. 
	//En el moment de cridar-ho sempre retornara m_SDLWindow
	inline SDL_Window* operator()(void) const { return m_SDLWindow; }
	//Retorna l'amplada i la llargada de la pantalla
	inline int GetWidth(void) const { return m_screenWidth; };
	inline int GetHeight(void) const { return m_screenHeight; };
	//retorna el nom de la pantalla 
	inline const std::string &GetName(void) const { return m_name; };
private:

	// crea un punter que no apunta a res de moment, despres apuntara a la finestra. 
	SDL_Window* m_SDLWindow{ nullptr };

	//init variables width height i nom 
	const int m_screenWidth, m_screenHeight;
	const std::string m_name;
};