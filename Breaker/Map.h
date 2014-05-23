#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

#include <SGE.h>
using namespace SGE;
#include "Tile.h"

class Map
{
public: 
	Map();
	~Map();

	void Load(const char* pLevelFile, const char* pTexturePack);
	void Unload();
	void Update(float deltaTime);
	void Render(const SVector2& offset);

	SRect GetBoundingBoxFromSegment(const SLineSegment& line) const;

	int GetWidth() const		{ return mColumns * mTileSize; }
	int GetHeight() const		{ return mRows * mTileSize; }
	int GetTileSize() const		{ return mTileSize; }

	Tile* GetTiles() const		{ return mTiles; }

private:
	// Block copy construction and assignment operation
	Map(const Map& rhs);
	Map& operator=(const Map&);
	bool LoadLevel(const char* pLevelFile);
	bool LoadTexturePack(const char* pTexturePack);

	SGE_Sprite* mSprites;
	Tile* mTiles;

	int mColumns;
	int mRows;
	int mTileSize;
	int mSpriteCount;
};

#endif // #ifndef INCLUDED_MAP_H