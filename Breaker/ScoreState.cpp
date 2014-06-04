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
	mBackground.Load("ScoreScreen.png");
	
	mScoreFont.Load(120, true);
	mScoreFont.SetColor(255, 255, 255);

	mCursor.Load("pointer.png");

	mStartButton.Load("button_off.png", "button_on.png");
	mStartButton.SetPosition(414.0f, 400.0f);
	mStartButton.SetText("Main Menu", 255, 255, 255);

}

void ScoreState::Unload()
{
	mBackground.Unload();
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
	mBackground.Render();
	int score = mGameContext.GetScore();
	string scoreString = to_string(score);
	mScoreFont.Print(scoreString.c_str(), 380, 200);
	mStartButton.Render();
	mCursor.Render();
}