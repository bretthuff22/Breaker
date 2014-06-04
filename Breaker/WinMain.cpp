#include <SGE.h>
using namespace SGE;

#include "Paddle.h"


#include "FrontendState.h"
#include "GameplayState.h"
#include "GameContext.h"
#include "ScoreState.h"

AppState* currentState = nullptr;
GameState nextState = GameState::Invalid;
GameContext gameContext;

//Paddle paddle;

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
		case GameState::Gameplay:
			currentState = new GameplayState(gameContext);
			break;
		case GameState::Score:
			currentState = new ScoreState(gameContext);
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

