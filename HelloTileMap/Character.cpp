#include "Character.h"

Character::Character()
	: mPosition(0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f)
	, mJumping(true)
{
}

Character::~Character()
{
}

SRect Character::GetBoundingBox() const
{
	return SRect
	(
		mPosition.x - 16.0f,
		mPosition.y - 56.0f, 
		mPosition.x + 16.0f,
		mPosition.y
	);
}

void Character::Load()
{
	mSprite.Load("mario_idle_01.png");
}
void Character::Unload()
{
	mSprite.Unload();
}
void Character::Update(float deltaTime, const Map& map)
{
	const float kSpeed = 500.0f;

	//Check horizontal movement
	if (Input_IsKeyDown(Keys::RIGHT))
	{
		mVelocity.x = kSpeed * deltaTime;
	}
	else if (Input_IsKeyDown(Keys::LEFT))
	{
		mVelocity.x = -kSpeed * deltaTime;
	}
	else
	{
		mVelocity.x = 0.0f;
	}

	// Check collision
	SRect bb = GetBoundingBox();
	SRect newbb = bb + SVector2(mVelocity.x, 0.0f);
	SRect rightbb = map.GetBoundingBoxFromSegment(newbb.GetRightSegment());
	SRect leftbb = map.GetBoundingBoxFromSegment(newbb.GetLeftSegment());

	// Right collision
	if (mVelocity.x > 0.0f && rightbb.IsValid())
	{
		mPosition.x += (int)(rightbb.min.x - bb.max.x) - 1.0f;
	}
	// Left collision
	else if (mVelocity.x < 0.0f && leftbb.IsValid())
	{
		mPosition.x += (int)(leftbb.max.x - bb.min.x) + 1.0f;
	}
	else
	{
		mPosition.x += (int)mVelocity.x;
	}


	//Check vertical movement
	//if (Input_IsKeyDown(Keys::DOWN))
	//{
	//	mVelocity.y = kSpeed * deltaTime;
	//}
	//else if (Input_IsKeyDown(Keys::UP))
	//{
	//	mVelocity.y = -kSpeed * deltaTime;
	//}
	//else
	//{
	//	mVelocity.y = 0.0f;
	//}

	if(!mJumping && Input_IsKeyPressed(Keys::UP))
	{
		mVelocity.y = -30.0f;
		mJumping = true;
	}
	else
	{
		mVelocity.y += 100.0f * deltaTime;
	}

	mVelocity.y = Min(mVelocity.y, 30.0f);

	// Check collision
	newbb =  bb + SVector2(0.0f, mVelocity.y);
	SRect bottombb = map.GetBoundingBoxFromSegment(newbb.GetBottomSegment());
	SRect topbb = map.GetBoundingBoxFromSegment(newbb.GetTopSegment());

	// Bottom collision
	if(mVelocity.y > 0.0f && bottombb.IsValid())
	{
		mPosition.y += (int)(bottombb.min.y - bb.max.y) - 1.0f;
		mVelocity.y = 0.0f;
		mJumping = false;
	}
	// Top collision
	else if(mVelocity.y < 0.0f && topbb.IsValid())
	{
		mPosition.y += (int)(topbb.max.y - bb.min.y) + 1.0f;
		mVelocity.y = 0.0f;
	}
	else
	{
		mPosition.y += (int)mVelocity.y;
	}



}
void Character::Render(const SVector2& offset)
{
	const int kTextureWidth = mSprite.GetWidth();
	const int kTextureHeight = mSprite.GetHeight();
	SVector2 renderPos(mPosition.x - (kTextureWidth * 0.5f), mPosition.y - kTextureHeight);
	mSprite.SetPosition(renderPos + offset);
	mSprite.Render();
}