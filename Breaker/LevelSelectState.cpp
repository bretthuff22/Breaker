#include "LevelSelectState.h"

LevelSelectState::LevelSelectState(GameContext& gc)
	: AppState(gc)
{

}
	
LevelSelectState::~LevelSelectState()
{

}

void LevelSelectState::Load()
{
	mGameContext.SetScore(0);
	mBackground.Load("MainMenu.png");

	mCursor.Load("pointer.png");

	mLevel01.Load("button_off.png", "button_on.png");
	mLevel01.SetPosition(314.0f, 400.0f);
	mLevel01.SetText("Level 1", 255, 255, 255);
	mLevel02.Load("button_off.png", "button_on.png");
	mLevel02.SetPosition(314.0f, 440.0f);
	mLevel02.SetText("Level 2", 255, 255, 255);
	mLevel03.Load("button_off.png", "button_on.png");
	mLevel03.SetPosition(314.0f, 480.0f);
	mLevel03.SetText("Level 3", 255, 255, 255);
	mLevel04.Load("button_off.png", "button_on.png");
	mLevel04.SetPosition(314.0f, 520.0f);
	mLevel04.SetText("Level 4", 255, 255, 255);
	mLevel05.Load("button_off.png", "button_on.png");
	mLevel05.SetPosition(314.0f, 560.0f);
	mLevel05.SetText("Level 5", 255, 255, 255);
	mLevel06.Load("button_off.png", "button_on.png");
	mLevel06.SetPosition(514.0f, 400.0f);
	mLevel06.SetText("Level 6", 255, 255, 255);
	mLevel07.Load("button_off.png", "button_on.png");
	mLevel07.SetPosition(514.0f, 440.0f);
	mLevel07.SetText("Level 7", 255, 255, 255);
	mLevel08.Load("button_off.png", "button_on.png");
	mLevel08.SetPosition(514.0f, 480.0f);
	mLevel08.SetText("Level 8", 255, 255, 255);
	mLevel09.Load("button_off.png", "button_on.png");
	mLevel09.SetPosition(514.0f, 520.0f);
	mLevel09.SetText("Level 9", 255, 255, 255);
	mLevel10.Load("button_off.png", "button_on.png");
	mLevel10.SetPosition(514.0f, 560.0f);
	mLevel10.SetText("Level 10", 255, 255, 255);

	mClick.Load("blip.wav");
}

void LevelSelectState::Unload()
{
	mBackground.Unload();
	mCursor.Unload();
	
	mLevel01.Unload();
	mLevel02.Unload();
	mLevel03.Unload();
	mLevel04.Unload();
	mLevel05.Unload();
	mLevel06.Unload();
	mLevel07.Unload();
	mLevel08.Unload();
	mLevel09.Unload();
	mLevel10.Unload();

	mClick.Unload();
}

GameState LevelSelectState::Update(float deltaTime)
{
	mCursor.Update(deltaTime);

	mLevel01.Update(deltaTime);
	mLevel02.Update(deltaTime);
	mLevel03.Update(deltaTime);
	mLevel04.Update(deltaTime);
	mLevel05.Update(deltaTime);
	mLevel06.Update(deltaTime);
	mLevel07.Update(deltaTime);
	mLevel08.Update(deltaTime);
	mLevel09.Update(deltaTime);
	mLevel10.Update(deltaTime);

	GameState nextState = GameState::Invalid;

	if (mLevel01.IsPressed())
	{
		mGameContext.SetLevel(0);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (mLevel02.IsPressed())
	{
		mGameContext.SetLevel(1);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (mLevel03.IsPressed())
	{
		mGameContext.SetLevel(2);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (mLevel04.IsPressed())
	{
		mGameContext.SetLevel(3);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (mLevel05.IsPressed())
	{
		mGameContext.SetLevel(4);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (mLevel06.IsPressed())
	{
		mGameContext.SetLevel(5);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (mLevel07.IsPressed())
	{
		mGameContext.SetLevel(6);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (mLevel08.IsPressed())
	{
		mGameContext.SetLevel(7);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (mLevel09.IsPressed())
	{
		mGameContext.SetLevel(8);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (mLevel10.IsPressed())
	{
		mGameContext.SetLevel(9);
		nextState = GameState::Gameplay;
		mClick.Play();
	}
	else if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		nextState = GameState::Quit;
	}
	return nextState;
}

void LevelSelectState::Render()
{
	mBackground.Render();

	mLevel01.Render();
	mLevel02.Render();
	mLevel03.Render();
	mLevel04.Render();
	mLevel05.Render();
	mLevel06.Render();
	mLevel07.Render();
	mLevel08.Render();
	mLevel09.Render();
	mLevel10.Render();

	mCursor.Render();
}