#include "Paddle.h"

Paddle::Paddle()
	: Collider(Collider::paddle, 0)
	, mScalar(1.0f)
{
	mSprite.Load("paddle.png");
	Collider::SetPosition(SVector2 (250.0f, 500.0f));
	Collider::SetVelocity(SVector2 (0.0f, 0.0f));
}

Paddle::~Paddle()
{
}

void Paddle::CreateBoundingBox() 
{
	int height = mSprite.GetHeight();
	int width = mSprite.GetWidth();
	Collider::SetBoundingBox(SRect (	Collider::GetPosition().x - mScalar*width/2,
										Collider::GetPosition().y - height, 
										Collider::GetPosition().x + mScalar*width/2,
										Collider::GetPosition().y	
									));
}

void Paddle::Load()
{
	CreateBoundingBox();
}
void Paddle::Unload()
{
	mSprite.Unload();
}
void Paddle::Update(float deltaTime)
{
	

}
void Paddle::Render(const SVector2& offset)
{
	const int kTextureWidth = mSprite.GetWidth();
	const int kTextureHeight = mSprite.GetHeight();
	SVector2 renderPos(Collider::GetPosition().x - (kTextureWidth * 0.5f), Collider::GetPosition().y - kTextureHeight);
	mSprite.SetPosition(renderPos/* + offset*/);
	mSprite.Render();
}

void Paddle::Widen()
{
	mScalar = 1.5f;
	mSprite.SetScale(SVector2(mScalar, 1.0f));
	CreateBoundingBox();
}
void Paddle::Shorten()
{
	mScalar = 0.75f;
	mSprite.SetScale(SVector2(mScalar, 1.0f));
	CreateBoundingBox();
}