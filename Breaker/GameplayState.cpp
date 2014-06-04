#include "GameplayState.h"
#include <iostream>
using namespace std;

GameplayState::GameplayState(GameContext& gc)
	: AppState(gc)
	, mNumBalls(3)
{
	mPaddle = new Paddle();
	mBall = new Ball();
	mCollManager =  new CollisionManager();
}
	
GameplayState::~GameplayState()
{

}

void GameplayState::Load()
{
	mScoreFont.Load(20, true);
	mScoreFont.SetColor(255, 0, 0);

	if (mGameContext.GetLevel()==0)
	{
		mMap.Load("level01.txt", "level01bricks.txt", "texturepack01.txt", "texturepackbricks01.txt");
	}
	else if (mGameContext.GetLevel()==1)
	{
		//mMap.Load("level02.txt", "texturepack02.txt");
	}
	else if (mGameContext.GetLevel()==2)
	{
		//mMap.Load("mariolevel.txt", "mariopack.txt");
	}

	
	mPaddle->SetPosition(SVector2(400.0f, 550.0f));
	mBall->SetPosition(SVector2(400.0f, 484.0f));

	mCollManager->Register(mPaddle);
	mCollManager->Register(mBall);
	mCollManager->Load(mMap);
}

void GameplayState::Unload()
{
	mCollManager->Unload();
	mCollManager->UnRegister(mPaddle);
	mPaddle->Unload();
	mCollManager->UnRegister(mBall);
	mBall->Unload();
	mMap.Unload();
	mScoreFont.Unload();
}

GameState GameplayState::Update(float deltaTime)
{
	mMap.Update(deltaTime);
	mPaddle->Update(deltaTime);
	mBall->Update(deltaTime);
	int scoreChange = mCollManager->Update(deltaTime, mMap);

	if (scoreChange)
	{
		mGameContext.SetScore( scoreChange + mGameContext.GetScore());
		mMap.SetBrickCount(mMap.GetBrickCount() - scoreChange/10);
	}

	GameState nextState = GameState::Invalid;

	const int kWinHeight = IniFile_GetInt("WinHeight", 600);
	if (mBall->GetPosition().y > kWinHeight)
	{
		mNumBalls--;
		if (mNumBalls > 0)
		{
			mBall->SetAlive(false);
			mBall->SetPosition(SVector2(400.0f, 484.0f));
			mBall->SetVelocity(SVector2(0.0f, 0.0f));
			//mBall->SetRandomVelocity();
		}
		else
		{
			nextState = GameState::Score;
		}
	}

	if (mMap.GetBrickCount() == 0)
	{
		nextState = GameState::Score;
	}

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

	SVector2 target = mPaddle->GetPosition();
	SVector2 offset;
	offset.x = (kScreenWidth* 0.5f) - target.x;
	offset.x = Clamp(offset.x, (float)kScreenWidth - mMap.GetWidth(), 0.0f);
	offset.y = (kScreenHeight * 0.5f) - target.y;
	offset.y = Clamp(offset.y, (float)kScreenHeight - mMap.GetHeight(), 0.0f);

	mMap.Render(offset);
	//mPaddle->Render(offset);
	//mBall->Render(offset);
	mCollManager->Render(offset);

	int score = mGameContext.GetScore();
	string scoreString = "Score: " + to_string(score);
	mScoreFont.Print(scoreString.c_str(), 800, 0);
}


void GameplayState::SetBallInPlay(bool inPlay)
{
	mBallInPlay = inPlay;
}

	
bool GameplayState::InPlay()
{
	return mBallInPlay;
}