#include "Brick.h"

Brick::Brick()
	: Collider(Collider::brick)
	, mSize(0)
	, mSpriteType(0)
	, mWalkable(true)
{
}

Brick::~Brick()
{
}


void Brick::CreateBoundingBox()
{
	Collider::SetBoundingBox(SRect
	(
		Collider::GetPosition().x ,
		Collider::GetPosition().y - mSize/2, 
		Collider::GetPosition().x + mSize,
		Collider::GetPosition().y + mSize/2
	));
}
