#include "Enemy.h"


Enemy::Enemy()
	: mPosition(0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f)
	, mActive(false)
{
}
Enemy::~Enemy()
{
}
void Enemy::Load()
{
	mSprite.Load("fighter.png");
	mSprite.SetFlipV(true);
	mSprite.SetScale(0.6f, 0.6f, true);
}	
void Enemy::Unload()
{
	mSprite.Unload();
}
void Enemy::Update(float deltaTime)
{
	if (mActive)
	{
		// Update Enemy position
		mPosition += mVelocity * deltaTime;

		// Check if Enemy is outside the screen boundary
		const int kWinHeight = IniFile_GetInt("WinHeight", 600);

		if ( mPosition.y > kWinHeight + 100.0f)
		{
			Kill();
		}
	}
}
void Enemy::Render()
{
	if (mActive)
	{
		const float kHalfWidth = mSprite.GetWidth() * 0.5f;
		const float kHalfHeight = mSprite.GetHeight() * 0.5f;
		SVector2 renderPos(mPosition.x - kHalfWidth, mPosition.y - kHalfHeight);
		mSprite.SetPosition(renderPos);
		mSprite.Render();
	}
}

void Enemy::Spawn(const SVector2& pos)
{
	mPosition = pos;
	mVelocity.x = RandomFloat(-100.0f, 100.0f);
	mVelocity.y = RandomFloat(50.0f, 100.0f);
	mActive = true;
}
	
void Enemy::Kill()
{
	mActive = false;
}