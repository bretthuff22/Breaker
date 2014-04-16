#include "Fighter.h"


Fighter::Fighter()
{
}
Fighter::~Fighter()
{
}
void Fighter::Load()
{
	mSprite.Load("fighter.png");
}
void Fighter::Unload()
{
	mSprite.Unload();
}
void Fighter::Update(float deltaTime)
{
	const float kSpeed = 100.0f;
	if (Input_IsKeyDown(Keys::RIGHT))
	{
		mPosition.x += kSpeed * deltaTime;
	}
	if (Input_IsKeyDown(Keys::LEFT))
	{
		mPosition.x -= kSpeed * deltaTime;
	}

	if (Input_IsKeyDown(Keys::UP))
	{
		mPosition.y -= kSpeed * deltaTime;
	}
	if (Input_IsKeyDown(Keys::DOWN))
	{
		mPosition.y += kSpeed * deltaTime;
	}
}
void Fighter::Render()
{
	const float kHalfWidth = mSprite.GetWidth() * 0.5f;
	const float kHalfHeight = mSprite.GetHeight() * 0.5f;
	SVector2 renderPos(mPosition.x - kHalfWidth, mPosition.y - kHalfHeight);
	mSprite.SetPosition(renderPos);
	mSprite.Render();
}