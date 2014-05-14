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
	else if (mGameContext.GetLevel()==1)
	{
		//mMap.Load("level02.txt", "texturepack02.txt");
	}
	else if (mGameContext.GetLevel()==2)
	{
		//mMap.Load("mariolevel.txt", "mariopack.txt");
	}

	mPaddle.Load();
	mPaddle.SetPosition(SVector2(400.0f, 550.0f));
	mBall.Load();
	mBall.SetPosition(SVector2(400.0f, 500.0f));
}

void GameplayState::Unload()
{
	mMap.Unload();
	mPaddle.Unload();
	mBall.Unload();
}

GameState GameplayState::Update(float deltaTime)
{
	mMap.Update(deltaTime);
	mPaddle.Update(deltaTime, mMap);
	mBall.Update(deltaTime, mMap);
	
	GameState nextState = GameState::Invalid;

	if (Input_IsKeyPressed(Keys::ESCAPE))
	{
		nextState = GameState::Frontend;
	}
	return nextState;
}

void GameplayState::Render()
{
	const int kScreenWidth = IniFile_GetInt("WinWidth", 800);
	const int kScreenHeight = IniFile_GetInt("WinHeight", 600);

	SVector2 target = mPaddle.GetPosition();
	SVector2 offset;
	offset.x = (kScreenWidth* 0.5f) - target.x;
	offset.x = Clamp(offset.x, (float)kScreenWidth - mMap.GetWidth(), 0.0f);
	offset.y = (kScreenHeight * 0.5f) - target.y;
	offset.y = Clamp(offset.y, (float)kScreenHeight - mMap.GetHeight(), 0.0f);

	mMap.Render(offset);
	mPaddle.Render(offset);
	mBall.Render(offset);
}


void GameplayState::SetBallInPlay(bool inPlay)
{
	mBallInPlay = inPlay;
}

	
bool GameplayState::InPlay()
{
	return mBallInPlay;
}