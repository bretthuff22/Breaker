#ifndef INCLUDED_TILE_H
#define INCLUDED_TILE_H

#include "Collider.h"
//#include "Map.h"
#include <SGE.h>
using namespace SGE;



class Tile : public Collider
{
public: 
	Tile();
	~Tile();

	//SRect GetBoundingBox() const;

	//const SVector2& GetPosition() const			{ return mPosition; }
	int GetSize() const							{ return mSize; }
	bool IsWalkable() const						{ return mWalkable; }
	//int GetSpriteType() const					{ return mSpriteType; }


	//void SetPosition(const SVector2& pos)		{ mPosition = pos; }
	void SetSize(int size)						{ mSize = size; }
	//void SetSpriteType(int type)				{ mSpriteType = type; }
	void SetWalkable(bool walkable)				{ mWalkable = walkable; }

	virtual void CreateBoundingBox();

private:
	//SVector2 mPosition;
	int mSize;
	bool mWalkable;
};

#endif // #ifndef INCLUDED_TILE_H