#include "Brick.h"

Brick::Brick()
	: Collider(Collider::brick, 10)
	, mWidth(0)
	, mHeight(0)
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
		Collider::GetPosition().y - mHeight/2.0f, 
		Collider::GetPosition().x + mWidth,
		Collider::GetPosition().y + mHeight/2.0f
	));
}

