#include "Paddle.h"

Paddle::Paddle()
	: mPosition(250.0f, 500.0f)
{
}

Paddle::~Paddle()
{
}

SRect Paddle::GetBoundingBox() const
{
	return SRect
	(
		mPosition.x - 128.0f,
		mPosition.y - 56.0f, 
		mPosition.x + 128.0f,
		mPosition.y
	);
}

void Paddle::Load()
{
	mSprite.Load("paddle.png");
}
void Paddle::Unload()
{
	mSprite.Unload();
}
void Paddle::Update(float deltaTime, const Map& map)
{
	const float kSpeed = 800.0f;

	//Check horizontal movement
	if (Input_IsKeyDown(Keys::RIGHT))
	{
		mPosition.x += kSpeed * deltaTime;
	}
	else if (Input_IsKeyDown(Keys::LEFT))
	{
		mPosition.x += -kSpeed * deltaTime;
	}

	// Check collision
	SRect bb = GetBoundingBox();
	//SRect newbb = bb + SVector2(mVelocity.x, 0.0f);
	SRect rightbb = map.GetBoundingBoxFromSegment(bb.GetRightSegment()) ;
	SRect leftbb = map.GetBoundingBoxFromSegment(bb.GetLeftSegment());

	// Right collision
	if (rightbb.IsValid())
	{
		mPosition.x += (int)(rightbb.min.x - bb.max.x) - 1.0f;
	}
	// Left collision
	else if (leftbb.IsValid())
	{
		mPosition.x += (int)(leftbb.max.x - bb.min.x) + 1.0f;
	}
	//else
	//{
	//	mPosition.x += (int)mVelocity.x;
	//}


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

	
	// Check collision
	//newbb =  bb + SVector2(0.0f, mVelocity.y);
	//SRect bottombb = map.GetBoundingBoxFromSegment(newbb.GetBottomSegment());
	//SRect topbb = map.GetBoundingBoxFromSegment(newbb.GetTopSegment());

	// Bottom collision
	//if(mVelocity.y > 0.0f && bottombb.IsValid())
	//{
	//	mPosition.y += (int)(bottombb.min.y - bb.max.y) - 1.0f;
	//	mVelocity.y = 0.0f;
	//	mJumping = false;
	//}
	// Top collision
	//else if(mVelocity.y < 0.0f && topbb.IsValid())
	//{
	//	mPosition.y += (int)(topbb.max.y - bb.min.y) + 1.0f;
	//	mVelocity.y = 0.0f;
	//}

}
void Paddle::Render(const SVector2& offset)
{
	const int kTextureWidth = mSprite.GetWidth();
	const int kTextureHeight = mSprite.GetHeight();
	SVector2 renderPos(mPosition.x - (kTextureWidth * 0.5f), mPosition.y - kTextureHeight);
	mSprite.SetPosition(renderPos/* + offset*/);
	mSprite.Render();
}