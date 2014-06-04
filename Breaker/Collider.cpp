#include "Collider.h"

Collider::Collider(Shape shape, int value) 
	: mShape(shape), mValue(value)
	, mSpriteType(0)
	, mBrickType(BrickType::NLL)
	, mHits(1)
{

}
void Collider::SetPosition(const SVector2& pos)			
{ 
	mPosition = pos; 
	CreateBoundingBox();
}