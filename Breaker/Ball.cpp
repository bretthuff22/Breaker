#include "Ball.h"


Ball::Ball()
	: mActive(false)
	, Collider(Collider::circle, 0)
{
	Collider::SetPosition(SVector2(0.0f, 0.0f));
	Collider::SetVelocity(SVector2 (0.0f, 0.0f));
}
Ball::~Ball()
{
}
void Ball::Load()
{
	mSprite.Load("ball.png");
	CreateBoundingBox();
}	
void Ball::Unload()
{
	mSprite.Unload();
}
void Ball::Update(float deltaTime)
{
	//if (mActive)
	//{
	//	// Update Ball position
	//	//mPosition += mVelocity * deltaTime;

	//	// Check collision
	//	SRect bb = GetBoundingBox() + mVelocity*deltaTime;
	//	SRect rightbb = map.GetBoundingBoxFromSegment(bb.GetRightSegment());
	//	SRect leftbb = map.GetBoundingBoxFromSegment(bb.GetLeftSegment());
	//	SRect bottombb = map.GetBoundingBoxFromSegment(bb.GetBottomSegment());
	//	SRect topbb = map.GetBoundingBoxFromSegment(bb.GetTopSegment());

	//	// Right collision
	//	if (rightbb.IsValid() 
	//		&& rightbb.min.x < bb.max.x 
	//		&& topbb.max.y < bb.min.y 
	//		&& bottombb.min.y > bb.max.y)
	//	{
	//		mVelocity.x *= -1;
	//		mPosition.x += ((int)(rightbb.min.x - bb.max.x - 1.0f));
	//	}
	//	// Left collision
	//	else if (leftbb.IsValid() 
	//		&& leftbb.max.x > bb.min.x 
	//		&& topbb.max.y < bb.min.y 
	//		&& bottombb.min.y > bb.max.y)
	//	{
	//		mVelocity.x *= -1;
	//		mPosition.x -= ((int)(leftbb.max.x - bb.min.x - 1.0f));
	//	}
	//	else
	//	{
	//		mPosition.x += mVelocity.x*deltaTime;
	//	}

	//	// Top collision
	//	if(topbb.IsValid() 
	//		&& topbb.max.y > bb.min.y
	//		&& rightbb.min.x > bb.max.x 
	//		&& leftbb.max.x < bb.min.x)
	//	{
	//		mVelocity.y *= -1;
	//		mPosition.y -= ((int)(topbb.max.y - bb.min.y - 1.0f));
	//	}
	//	// Bottom collision
	//	else if(bottombb.IsValid() 
	//		&& bottombb.min.y < bb.max.y 
	//		&& rightbb.min.x > bb.max.x 
	//		&& leftbb.max.x < bb.min.x)
	//	{
	//		mVelocity.y *= -1;
	//		mPosition.y -= ((int)(bottombb.min.y - bb.max.y - 1.0f));
	//	}
	//	else
	//	{
	//		mPosition.y += mVelocity.y*deltaTime;
	//	}

	// Check if Ball is outside the screen boundary
	const int kWinHeight = IniFile_GetInt("WinHeight", 600);

	if (Collider::GetPosition().y >kWinHeight)
	{
		Kill();
		mActive = false;
	}
	
	if (mActive == false)
	{
		if (Input_IsKeyDown(Keys::SPACE))
		{
			mActive = true;
			SetRandomVelocity();
			bool check = false;
		}
	}
	
}
void Ball::Render(const SVector2& offset)
{
	if (mActive)
	{
		const float kHalfWidth = mSprite.GetWidth() * 0.5f;
		const float kHalfHeight = mSprite.GetHeight() * 0.5f;
		SVector2 renderPos(Collider::GetPosition().x - kHalfWidth, Collider::GetPosition().y - kHalfHeight);
		mSprite.SetPosition(renderPos);
		mSprite.Render();
	}
}

void Ball::Fire(const SVector2& pos, const SVector2& vel)
{
	//mPosition = pos;
	//mVelocity = vel;
	//mActive = true;

}
	
void Ball::Kill()
{
	mActive = false;
}


void Ball::SetRandomVelocity()
{
	float kSpeed = 500.0f;
	SVector2 vel(RandomFloat(-(kSpeed) + 1, (kSpeed -1)), -1*sqrtf(kSpeed*kSpeed - (Collider::GetVelocity().x*Collider::GetVelocity().x)));
	Collider::SetVelocity(vel);
}