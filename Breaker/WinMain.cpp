#include <SGE.h>
using namespace SGE;

#include "Paddle.h"


#include "FrontendState.h"
#include "GameplayState.h"
#include "GameContext.h"
#include "ScoreState.h"
#include "LevelSelectState.h"

AppState* currentState = nullptr;
GameState nextState = GameState::Invalid;
GameContext gameContext;
SGE_Sound music;
float musicTime;
bool mute;

//Paddle paddle;

void SGE_Initialize()
{
	currentState = new FrontendState(gameContext);
	currentState->Load();
	music.Load("music2.wav");
	musicTime = 0.0f;
	mute = false;
}

void SGE_Terminate()
{
	currentState->Unload();
	delete currentState;
	currentState = nullptr;
	music.Unload();
}

bool SGE_Update(float deltaTime)
{
	if (musicTime >= 7.0f)
	{
		musicTime = 0.0f;
	}

	if (musicTime == 0.0f && nextState != GameState::Gameplay && mute == false)
	{
		music.Play();
	}
	
	musicTime += deltaTime;

	if (nextState != GameState::Invalid)
	{
		currentState->Unload();
		delete currentState;

		switch(nextState)
		{
		case GameState::Frontend:
			currentState = new FrontendState(gameContext);
			if (mute)
			{
				mute = false;
				music.Play();
				musicTime = 0.0f;
			}
			break;
		case GameState::LevelSelect:
			currentState = new LevelSelectState(gameContext);
			if (mute)
			{
				mute = false;
				music.Play();
				musicTime = 0.0f;
			}
			break;
		case GameState::Gameplay:
			currentState = new GameplayState(gameContext);
			music.Stop();
			mute = true;
			break;
		case GameState::Score:
			currentState = new ScoreState(gameContext);
			if (mute)
			{
				mute = false;
				music.Play();
				musicTime = 0.0f;
			}
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

