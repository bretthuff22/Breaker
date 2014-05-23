#include "Paddle.h"

Paddle::Paddle()
{
	Collider::SetPosition(SVector2 (250.0f, 500.0f));
	Collider::SetVelocity(SVector2 (0.0f, 0.0f));
	Collider::SetShape(Collider::paddle);
}

Paddle::~Paddle()
{
}

void Paddle::CreateBoundingBox() 
{
	Collider::SetBoundingBox(SRect (	Collider::GetPosition().x - 64.0f,
										Collider::GetPosition().y - 32.0f, 
										Collider::GetPosition().x + 64.0f,
										Collider::GetPosition().y	));
}

void Paddle::Load()
{
	mSprite.Load("paddle.png");
	CreateBoundingBox();
	CollisionManager::Get().Register(this);
}
void Paddle::Unload()
{
	mSprite.Unload();
	CollisionManager::Get().UnRegister(this);
}
void Paddle::Update(float deltaTime, const Map& map)
{
	const float kSpeed = 800.0f;

	//Check horizontal movement
	if (Input_IsKeyDown(Keys::RIGHT))
	{
		Collider::SetPosition(SVector2(Collider::GetPosition().x + kSpeed * deltaTime, Collider::GetPosition().y));
	}
	else if (Input_IsKeyDown(Keys::LEFT))
	{
		Collider::SetPosition(SVector2(Collider::GetPosition().x - kSpeed * deltaTime, Collider::GetPosition().y));
	}

	// Check collision
	SRect bb = GetBoundingBox();
	SRect rightbb = map.GetBoundingBoxFromSegment(bb.GetRightSegment()) ;
	SRect leftbb = map.GetBoundingBoxFromSegment(bb.GetLeftSegment());

	// Right collision
	if (rightbb.IsValid())
	{
		Collider::SetPosition(SVector2(Collider::GetPosition().x + (int)(rightbb.min.x - bb.max.x) - 1.0f, Collider::GetPosition().y));
	}
	// Left collision
	else if (leftbb.IsValid())
	{
		Collider::SetPosition(SVector2(Collider::GetPosition().x + (int)(leftbb.max.x - bb.min.x) + 1.0f, Collider::GetPosition().y)) ;
	}

}
void Paddle::Render(const SVector2& offset)
{
	const int kTextureWidth = mSprite.GetWidth();
	const int kTextureHeight = mSprite.GetHeight();
	SVector2 renderPos(Collider::GetPosition().x - (kTextureWidth * 0.5f), Collider::GetPosition().y - kTextureHeight);
	mSprite.SetPosition(renderPos/* + offset*/);
	mSprite.Render();
}