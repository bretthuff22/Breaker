#ifndef INCLUDED_TILE_H
#define INCLUDED_TILE_H

#include <SGE.h>
using namespace SGE;

class Tile
{
public: 
	Tile();
	~Tile();

	const SVector2& GetPosition() const			{ return mPosition; }
	int GetSize() const							{ return mSize; }
	int GetType() const							{ return mType; }

	void SetPosition(const SVector2& pos)		{ mPosition = pos; }
	void SetSize(int size)						{ mSize = size; }
	void SetType(int type)						{ mType = type; }

private:
	SVector2 mPosition;
	int mSize;
	int mType;
};

#endif // #ifndef INCLUDED_TILE_H