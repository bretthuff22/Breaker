#ifndef INCLUDED_GameplaySTATE_H
#define INCLUDED_GameplaySTATE_H

#include "AppState.h"
//#include "Map.h"
#include "Paddle.h"
#include "Ball.h"
//#include "Collider.h"
#include "CollisionManager.h"


class GameplayState : public AppState
{
public: 
	GameplayState(GameContext& gc);
	
	virtual ~GameplayState();

	virtual void Load();
	virtual void Unload();
	virtual GameState Update(float deltaTime);
	virtual void Render();

	void SetBallInPlay(bool inPlay);

	bool InPlay();

private:
	Map mMap;
	Paddle* mPaddle;
	bool mBallInPlay;
	Ball* mBall;
	int mNumBalls;
	SGE_Font mScoreFont;
	SGE_Font mLivesFont;

	SGE_Sound mMusic;
	float mMusicTime;

	CollisionManager* mCollManager;

};

#endif // #ifndef INCLUDED_GameplayState_H