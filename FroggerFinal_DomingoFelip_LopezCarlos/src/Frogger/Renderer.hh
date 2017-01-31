

#pragma once
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <unordered_map>
#include "Resource.h"
#include "Transform.hh"
#include "Window.hh"
#include "Assert.hh"
#include "Color.h"
#include "ID.hh"

#define R Renderer::Instance()

//Enumeració de les fonts
enum FontStyle {
	FONT_STYLE_BOLD = TTF_STYLE_BOLD,
	FONT_STYLE_ITALIC = TTF_STYLE_ITALIC,
	FONT_STYLE_UNDERLINE = TTF_STYLE_UNDERLINE,
	FONT_STYLE_NORMAL = TTF_STYLE_NORMAL
};

// Biblical Renderer class to manage the View of the Game
class Renderer {
	Renderer() {
		//Create renderer for window
		//m_SDLRenderer: es el punter que es crea baix de tot
		// SDL_ CreateRenderer: Retorna un context valid renderitzable o un missatge de error
		//SDL_RENDERER_ACCELERATED: El render utilitza acceleracio del hardware
		m_SDLRenderer = SDL_CreateRenderer(W(), -1, SDL_RENDERER_ACCELERATED);
		//EN cas de que m_SDLRenderer sigui null torna un missatge de error. 
		ASSERT(m_SDLRenderer != nullptr);
		//Utilice esta función para configurar el color utilizado para las operaciones de dibujo 
		SDL_SetRenderDrawColor(m_SDLRenderer, 255, 255, 255, 255);
		//Initialize PNG loading // para poder cargar imagenes png o jpg
		constexpr int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		//dar codigo de error si no hemos hecho bien la operacion anterior
		ASSERT((IMG_Init(imgFlags) & imgFlags));
		ASSERT(TTF_Init() != -1);
	}
	//??????????????????????
	Renderer(const Renderer &rhs) = delete;
	Renderer &operator=(const Renderer &rhs) = delete;
public:
	//?????????????????????????????????
	inline static Renderer &Instance(void) {
		static Renderer renderer;
		return renderer;
	}

	//Destructor de la classe 
	~Renderer() {
		//SDL_DestroyTexture:destrueix la textura
		for (auto &t : m_textureData) SDL_DestroyTexture(t.second), t.second = nullptr;
		//TTF_CloseFont: acaba amb la font
		for (auto &f : m_fontData) TTF_CloseFont(f.second), f.second = nullptr;
		//SDL_DestroyRenderer: destrueix el render i despres posa el punter m_SDLRenderer a null
		SDL_DestroyRenderer(m_SDLRenderer), m_SDLRenderer = nullptr;
		
		IMG_Quit();
		TTF_Quit();
	}


	template<ObjectID objectID> void LoadTexture(std::string &&filename) {
		//Load image at specified path
		auto loadedSurface = IMG_Load(RESOURCE_FILE(filename));
		//En cas que no es pugui carregar la imatge dona missatge de error. 
		ASSERT_MSG(loadedSurface != nullptr, "Unable to load image " + filename);
		//Create texture from surface pixels
		ASSERT_MSG(m_textureData.emplace(objectID, SDL_CreateTextureFromSurface(m_SDLRenderer, loadedSurface)).second, "Unable to create texture from " + filename);
		//SDL_FreeSurface: Libera la textura, en este caso loadedSurface
		SDL_FreeSurface(loadedSurface); //Get rid of loaded surface
	}
	template<FontID fontID> void LoadFont(std::string &&filename, int size) {
		//Funcion que Carrga Font 
		ASSERT_MSG(m_fontData.emplace(fontID, TTF_OpenFont(RESOURCE_FILE(filename), size)).second, "Unable to create font from " + filename);
	}
	template<FontID fontID> inline TTF_Font *GetFont() {
		//Dona la Font, de la posicion fontID
		return m_fontData[fontID];
	}
	template<FontID fontID, FontStyle style> void SetFontStyle() {
		//en aquest cas li canvia la font de la posicio fontID
		TTF_SetFontStyle(m_fontData[fontID], style);
	}
	//SDL_Surface:A structure that contains a collection of pixels used in software blitting. BLITTING: dos mapas de bits son combinados en uno.
	void Push(SDL_Surface *surface, Transform &transform) {
		ASSERT(surface != nullptr);
		//SDL_CreateTextureFromSurface: crea una textura a partir del surface(estructura que conte una coleccio de pixels).
		auto texture = SDL_CreateTextureFromSurface(m_SDLRenderer, surface);
		transform.x -= surface->w / 2;
		transform.y -= surface->h / 2;
		transform.w *= surface->w;
		transform.h *= surface->h;
		ASSERT(!SDL_RenderCopy(m_SDLRenderer, texture, nullptr, &transform()));

		//Destrueix el Surface i la textura
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
	void Push(const ObjectID &objectID, const Transform &transform) {
		//SDL_RenderCopy:Utilice esta función para copiar una parte de la textura al destino de renderización actual.
		ASSERT(!SDL_RenderCopy(m_SDLRenderer, m_textureData[objectID], nullptr, &transform()));
	}

	//SDL_RenderClear: Utilice esta función para borrar el destino de renderizado actual con el color del dibujo.
	void Clear(void) const { SDL_RenderClear(m_SDLRenderer); };

	//SDL_RenderPresent: Utilice esta función para actualizar la pantalla con cualquier representación realizada desde la llamada anterior.
	void Render(void) const { SDL_RenderPresent(m_SDLRenderer); };
private:

	//Dos maps anidados    
	std::unordered_map<ObjectID, SDL_Texture*> m_textureData;
	std::unordered_map<FontID, TTF_Font*> m_fontData;
	
	//Punter de tipo SDL_Renderer
	SDL_Renderer* m_SDLRenderer{ nullptr };
};