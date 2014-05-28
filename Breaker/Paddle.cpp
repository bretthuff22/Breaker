#include "Paddle.h"

Paddle::Paddle()
	: Collider(Collider::paddle)
{
	Collider::SetPosition(SVector2 (250.0f, 500.0f));
	Collider::SetVelocity(SVector2 (0.0f, 0.0f));
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