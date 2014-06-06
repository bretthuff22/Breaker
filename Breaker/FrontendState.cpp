#include "FrontendState.h"

FrontendState::FrontendState(GameContext& gc)
	: AppState(gc)
{

}
	
FrontendState::~FrontendState()
{

}

void FrontendState::Load()
{
	mGameContext.SetScore(0);
	mBackground.Load("MainMenu.png");

	mCursor.Load("pointer.png");

	mStartButton.Load("button_off.png", "button_on.png");
	mStartButton.SetPosition(414.0f, 400.0f);
	mStartButton.SetText("Start", 255, 255, 255);

	mClick.Load("blip.wav");
}

void FrontendState::Unload()
{
	mBackground.Unload();
	mCursor.Unload();
	mStartButton.Unload();
	mClick.Unload();
}

GameState FrontendState::Update(float deltaTime)
{
	mCursor.Update(deltaTime);
	mStartButton.Update(deltaTime);

	GameState nextState = GameState::Invalid;

	if (mStartButton.IsPressed())
	{
		mClick.Play();
		mGameContext.SetLevel(0);
		nextState = GameState::LevelSelect;
	}
	else if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		nextState = GameState::Quit;
	}
	return nextState;
}

void FrontendState::Render()
{
	mBackground.Render();
	mStartButton.Render();
	mCursor.Render();
}