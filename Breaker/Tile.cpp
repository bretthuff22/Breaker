#include "Tile.h"

Tile::Tile()
	: Collider(Collider::box)
	, mPosition(0.0f, 0.0f)
	, mSize(0)
	, mSpriteType(0)
{
}

Tile::~Tile()
{
}

void Tile::CreateBoundingBox()
{
	Collider::SetBoundingBox(SRect
	(
		mPosition.x,
		mPosition.y, 
		mPosition.x + mSize,
		mPosition.y + mSize
	));
}
