#include "ScoreState.h"
#include <iostream>
using namespace std;

ScoreState::ScoreState(GameContext& gc)
	: AppState(gc)
{

}
	
ScoreState::~ScoreState()
{

}

void ScoreState::Load()
{
	mFont.Load(120, true);
	mFont.SetColor(0, 200, 255);
	mScoreFont.Load(120, true);
	mScoreFont.SetColor(0, 200, 255);

	mCursor.Load("sword.png");

	mStartButton.Load("button_on.png", "button_off.png");
	mStartButton.SetPosition(200.0f, 500.0f);
	mStartButton.SetText("Main Menu", 255, 255, 255);

}

void ScoreState::Unload()
{
	mFont.Unload();
	mScoreFont.Unload();
	mCursor.Unload();
	mStartButton.Unload();
}

GameState ScoreState::Update(float deltaTime)
{
	mCursor.Update(deltaTime);
	mStartButton.Update(deltaTime);


	GameState nextState = GameState::Invalid;

	if (mStartButton.IsPressed())
	{
		mGameContext.SetLevel(0);
		nextState = GameState::Frontend;
	}
	else if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		nextState = GameState::Quit;
	}
	return nextState;
}

void ScoreState::Render()
{
	mFont.Print("Score: ", 100, 100);
	int score = mGameContext.GetScore();
	string scoreString = to_string(score);
	mScoreFont.Print(scoreString.c_str(), 200, 300);
	mStartButton.Render();
	mCursor.Render();
}