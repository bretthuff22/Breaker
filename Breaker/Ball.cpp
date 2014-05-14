#include "Ball.h"


Ball::Ball()
	: mPosition(0.0f, 0.0f)
	, mVelocity(0.0f, 0.0f)
	, mActive(false)
{
}
Ball::~Ball()
{
}
void Ball::Load()
{
	mSprite.Load("Ball1.png");
}	
void Ball::Unload()
{
	mSprite.Unload();
}
void Ball::Update(float deltaTime, const Map& map)
{
	if (mActive)
	{
		// Update Ball position
		mPosition += mVelocity * deltaTime;


		// Check collision
		SRect bb = GetBoundingBox();
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
		else
		{
			mPosition.x += (int)mVelocity.x;
		}


		// Check vertical movement
		if (Input_IsKeyDown(Keys::DOWN))
		{
			mVelocity.y = kSpeed * deltaTime;
		}
		else if (Input_IsKeyDown(Keys::UP))
		{
			mVelocity.y = -kSpeed * deltaTime;
		}
		else
		{
			mVelocity.y = 0.0f;
		}

	
		// Check collision
		newbb =  bb + SVector2(0.0f, mVelocity.y);
		SRect bottombb = map.GetBoundingBoxFromSegment(newbb.GetBottomSegment());
		SRect topbb = map.GetBoundingBoxFromSegment(newbb.GetTopSegment());

		// Bottom collision
		if(mVelocity.y > 0.0f && bottombb.IsValid())
		{
			mPosition.y += (int)(bottombb.min.y - bb.max.y) - 1.0f;
			mVelocity.y = 0.0f;
		}
		// Top collision
		else if(mVelocity.y < 0.0f && topbb.IsValid())
		{
			mPosition.y += (int)(topbb.max.y - bb.min.y) + 1.0f;
			mVelocity.y = 0.0f;
		}



		// Check if Ball is outside the screen boundary
		const int kWinHeight = IniFile_GetInt("WinHeight", 600);

		if (mPosition.y >kWinHeight)
		{
			Kill();
		}
	}
}
void Ball::Render(const SVector2& offset)
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

void Ball::Fire(const SVector2& pos, const SVector2& vel)
{
	mPosition = pos;
	mVelocity = vel;
	mActive = true;

}
	
void Ball::Kill()
{
	mActive = false;
}