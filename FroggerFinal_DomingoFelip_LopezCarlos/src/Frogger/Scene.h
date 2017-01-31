#pragma once

#include "sprite.h"

enum class SceneState {
	NONE,		
	RUNNING,	
	EXIT,		
	SLEEP		
};


class Scene {
	friend class SceneManager;
public:
	//explicit: no permet conversions implicites o inizialitzacions de copia. 
	explicit Scene() = default;
	virtual ~Scene() = default;

	//VIRTUALS: obliga a les classes que ereden de scene a tenir aquestes funcions 
	virtual void OnEntry(void) = 0;
	virtual void OnExit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	//fa un set al currentState
	template <SceneState state> inline void SetState(void) { currentState = state; };
	//fa el get del current State
	inline SceneState GetState(void) const { return currentState; };
	//comprova que currentStat==state
	template <SceneState state> inline bool CheckState(void) const { return currentState == state; };
protected:
	SceneState currentState{ SceneState::NONE }; 
};