#ifndef INCLUDED_GameplaySTATE_H
#define INCLUDED_GameplaySTATE_H

#include "AppState.h"
#include "Map.h"

class GameplayState : public AppState
{
public: 
	GameplayState(GameContext& gc);
	
	virtual ~GameplayState();

	virtual void Load();
	virtual void Unload();
	virtual GameState Update(float deltaTime);
	virtual void Render();

private:
	Map mMap;
};

#endif // #ifndef INCLUDED_GameplayState_H