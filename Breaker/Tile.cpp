#include "Tile.h"

Tile::Tile()
	: Collider(Collider::box)
	, mSize(0)
	, mWalkable(true)
{
}

Tile::~Tile()
{
}

void Tile::CreateBoundingBox()
{
	Collider::SetBoundingBox(SRect
	(
		Collider::GetPosition().x ,
		Collider::GetPosition().y - mSize/2, 
		Collider::GetPosition().x + mSize,
		Collider::GetPosition().y + mSize/2
	));
}
