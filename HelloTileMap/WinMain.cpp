#include <SGE.h>
using namespace SGE;

#include "FrontendState.h"
#include "GameplayState.h"
#include "GameContext.h"

AppState* currentState = nullptr;
GameState nextState = GameState::Invalid;
GameContext gameContext;


void SGE_Initialize()
{
	currentState = new FrontendState(gameContext);
	currentState->Load();
}

void SGE_Terminate()
{
	currentState->Unload();
	delete currentState;
	currentState = nullptr;
}

bool SGE_Update(float deltaTime)
{
	if (nextState != GameState::Invalid)
	{
		currentState->Unload();
		delete currentState;

		switch(nextState)
		{
		case GameState::Frontend:
			currentState = new FrontendState(gameContext);
			break;
		case GameState:: Gameplay:
			currentState = new GameplayState(gameContext);
			break;
		}

		currentState->Load();
	}
	nextState = currentState->Update(deltaTime);
	return (nextState == GameState::Quit);
}

void SGE_Render()
{
	currentState->Render();
}

