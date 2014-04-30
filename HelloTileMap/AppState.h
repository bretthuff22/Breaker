#ifndef INCLUDED_APPSTATE_H
#define INCLUDED_APPSTATE_H

#include "GameContext.h"
#include "GameStates.h"

class AppState
{
public: 
	AppState(GameContext& gc);
	
	virtual ~AppState();

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual GameState Update(float deltaTime) = 0;
	virtual void Render() = 0;

protected:
	GameContext& mGameContext;
};

#endif // #ifndef INCLUDED_AppState_H