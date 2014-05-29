#ifndef INCLUDED_Brick_H
#define INCLUDED_Brick_H

//#include "Collider.h"
#include "CollisionManager.h"
//#include "Map.h"
#include <SGE.h>
using namespace SGE;



class Brick : public Collider
{
public: 
	Brick();
	~Brick();

	//SRect GetBoundingBox() const;

	//const SVector2& GetPosition() const			{ return mPosition; }
	int GetSize() const							{ return mSize; }
	bool IsWalkable() const						{ return mWalkable; }
	int GetSpriteType() const					{ return mSpriteType; }


	//void SetPosition(const SVector2& pos)		{ mPosition = pos; }
	void SetSize(int size)						{ mSize = size; }
	void SetSpriteType(int type)				{ mSpriteType = type; }
	void SetWalkable(bool walkable)				{ mWalkable = walkable; }

	virtual void CreateBoundingBox();

private:
	//SVector2 mPosition;
	int mSize;
	int mSpriteType;
	bool mWalkable;
};

#endif // #ifndef INCLUDED_Brick_H