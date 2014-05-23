#ifndef INCLUDED_TILE_H
#define INCLUDED_TILE_H

#include <SGE.h>
using namespace SGE;

#include "Collider.h"
#include "Map.h"

class Tile : public Collider
{
public: 
	Tile();
	~Tile();

	SRect GetBoundingBox() const;

	void Load() {};
	void Unload() {};
	void Update(float deltaTime, const Map& map) {};
	void Render(const SVector2& offset) {};

	const SVector2& GetPosition() const			{ return mPosition; }
	int GetSize() const							{ return mSize; }
	int GetType() const							{ return mType; }
	bool IsWalkable() const						{ return mWalkable; }

	void SetPosition(const SVector2& pos)		{ mPosition = pos; }
	void SetSize(int size)						{ mSize = size; }
	void SetType(int type)						{ mType = type; }
	void SetWalkable(bool walkable)				{ mWalkable = walkable; }

private:
	SVector2 mPosition;
	int mSize;
	int mType;
	bool mWalkable;
};

#endif // #ifndef INCLUDED_TILE_H