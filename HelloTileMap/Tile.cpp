#include "Tile.h"

Tile::Tile()
	: mPosition(0.0f, 0.0f)
	, mSize(0)
	, mType(0)
{
}

Tile::~Tile()
{
}

SRect Tile::GetBoundingBox() const
{
	return SRect
	(
		mPosition.x,
		mPosition.y, 
		mPosition.x + mSize,
		mPosition.y + mSize
	);
}
