#include "Collider.h"

void Collider::SetPosition(const SVector2& pos)			
{ 
	mPosition = pos; 
	CreateBoundingBox();
}