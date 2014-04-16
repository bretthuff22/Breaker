#include "Bullet.h"


Bullet::Bullet()
	: mPosition(0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f)
	, mActive(false)
{
}
Bullet::~Bullet()
{
}
void Bullet::Load()
{
	mSprite.Load("bullet1.png");
}	
void Bullet::Unload()
{
	mSprite.Unload();
}
void Bullet::Update(float deltaTime)
{
	if (mActive)
	{
		// Update bullet position
		mPosition += mVelocity * deltaTime;

		// Check if bullet is outside the screen boundary
		const int kWinWidth = IniFile_GetInt("WinWidth", 800);
		const int kWinHeight = IniFile_GetInt("WinHeight", 600);

		if (mPosition.x < 0 || mPosition.x > kWinWidth || 
			mPosition.y < 0 || mPosition.y > kWinHeight)
		{
			Kill();
		}
	}
}
void Bullet::Render()
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

void Bullet::Fire(const SVector2& pos, const SVector2& vel)
{
	mPosition = pos;
	mVelocity = vel;
	mActive = true;

}
	
void Bullet::Kill()
{
	mActive = false;
}