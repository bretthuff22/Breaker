#include "GameplayState.h"

GameplayState::GameplayState(GameContext& gc)
	: AppState(gc)
{

}
	
GameplayState::~GameplayState()
{

}

void GameplayState::Load()
{
	if (mGameContext.GetLevel()==0)
	{
		mMap.Load("level01.txt", "texturepack01.txt");
	}
	else
	{
		mMap.Load("level02.txt", "texturepack02.txt");
	}
}

void GameplayState::Unload()
{
	mMap.Unload();
}

GameState GameplayState::Update(float deltaTime)
{
	mMap.Update(deltaTime);
	
	GameState nextState = GameState::Invalid;

	if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		nextState = GameState::Frontend;
	}
	return nextState;
}

void GameplayState::Render()
{
	mMap.Render();
}