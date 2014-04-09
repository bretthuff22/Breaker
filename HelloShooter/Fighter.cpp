#include "Fighter.h"


Fighter::Fighter()
{
}
Fighter::~Fighter()
{
}
void Fighter::Load()
{
	mSprite.Load("Cyclops.png");
	mPosition.x = 100.0f;
	mPosition.y = 100.0f;
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
	mSprite.SetPosition(mPosition);
	mSprite.Render();
}