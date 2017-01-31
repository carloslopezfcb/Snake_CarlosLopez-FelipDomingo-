#pragma once


#pragma once
#include "scene.h"
#include "Assert.hh"
#include <typeindex>
#include <unordered_map>

#define SM SceneManager::Instance()

// SceneManager class to store and control the whole game scenes
class SceneManager {
public:

	template<class S> S *GetScene(void) {
		auto scene = m_scenes.find(typeid(S));
		return (scene != m_scenes.end()) ? dynamic_cast<S*>(scene->second) : nullptr;
	}

	//Destructor
	~SceneManager() { for (auto &scene : m_scenes) delete scene.second; }
	//singleton del SceneManager
	inline static SceneManager &Instance() {
		static SceneManager sceneManager;
		return sceneManager;
	}

	template<class S> void AddScene(void) {

		//static_assert: si devuelve true no hace nada, de lo contrario hace una declaracion de error
		static_assert(std::is_base_of<Scene, S>::value, "Can't add scene that doesn't inherit from IScene");
		//Inserta un nuevo elemento en el contenedor construido en el lugar con los args dados si no hay ningún elemento con la clave en el contenedor.
		//m_scenes es un MAP
		m_scenes.emplace(typeid(S), new S);
	}

	//aquesta funcio SetCurScene serveix per canviar d'escena
	template<class S> void SetCurScene(void) {
		//static_assert: si devuelve true no hace nada, de lo contrario hace una declaracion de error
		static_assert(std::is_base_of<Scene, S>::value, "Can't add scene that doesn't inherit from IScene");
		if (m_curScene != nullptr)
			m_curScene->OnExit(),
			m_curScene->SetState<SceneState::SLEEP>();

		////????????
		ASSERT((m_curScene = GetScene<S>()) != nullptr);
		//canvies la m_currState a RUNNING
		m_curScene->SetState<SceneState::RUNNING>();
		//entres a la funcio OnEntry del m_curScene
		m_curScene->OnEntry();
	}

	//dona directament el m_curScene actual
	inline Scene *&GetCurScene(void) { return m_curScene; }
private:
	//constructor 
	SceneManager() = default;
	SceneManager(const SceneManager &rhs) = delete;
	//???????????EL SINGLETON QUE ENCARA NO ENTENC Q FA...?????????????
	SceneManager &operator=(const SceneManager &rhs) = delete;
	/*template<class S> S *GetScene(void) {
		auto scene = m_scenes.find(typeid(S));
		return (scene != m_scenes.end()) ? dynamic_cast<S*>(scene->second) : nullptr;
	}*/
private:
	std::unordered_map<std::type_index, Scene*> m_scenes;	// Array of screens
	Scene *m_curScene{ nullptr };							// Pointer to the current scene escena actual 
};