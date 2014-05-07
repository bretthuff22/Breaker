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
	mFont.Load(120, true);
	mFont.SetColor(0, 200, 255);

	mCursor.Load("sword.png");

	mStartButton.Load("button_on.png", "button_off.png");
	mStartButton.SetPosition(200.0f, 500.0f);
	mStartButton.SetText("Level 1", 255, 255, 255);

	mStartButton2.Load("button_on.png", "button_off.png");
	mStartButton2.SetPosition(200.0f, 550.0f);
	mStartButton2.SetText("Level 2", 255, 255, 255);

	mStartButton3.Load("button_on.png", "button_off.png");
	mStartButton3.SetPosition(200.0f, 600.0f);
	mStartButton3.SetText("Mario", 255, 255, 255);
}

void FrontendState::Unload()
{
	mFont.Unload();
	mCursor.Unload();
	mStartButton.Unload();
	mStartButton2.Unload();
	mStartButton3.Unload();
}

GameState FrontendState::Update(float deltaTime)
{
	mCursor.Update(deltaTime);
	mStartButton.Update(deltaTime);
	mStartButton2.Update(deltaTime);
	mStartButton3.Update(deltaTime);

	GameState nextState = GameState::Invalid;

	if (mStartButton.IsPressed())
	{
		mGameContext.SetLevel(0);
		nextState = GameState::Gameplay;
	}
	else if (mStartButton2.IsPressed())
	{
		mGameContext.SetLevel(1);
		nextState = GameState::Gameplay;
	}
	else if (mStartButton3.IsPressed())
	{
		mGameContext.SetLevel(2);
		nextState = GameState::Gameplay;
	}
	else if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		nextState = GameState::Quit;
	}
	return nextState;
}

void FrontendState::Render()
{
	mFont.Print("Zelda Game", 100, 100);
	mStartButton.Render();
	mStartButton2.Render();
	mStartButton3.Render();
	mCursor.Render();
}