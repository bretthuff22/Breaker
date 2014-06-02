#ifndef INCLUDED_MAP_H
#define INCLUDED_MAP_H

#include <SGE.h>
#include "Tile.h"
#include "Brick.h"

using namespace SGE;


class Map
{
public: 
	Map();
	~Map();

	void Load(const char* pLevelFile, const char* pLevelBrickFile, const char* pTexturePack, const char* pBrickTexturePack);
	void Unload();
	void Update(float deltaTime);
	void Render(const SVector2& offset);

	SRect GetBoundingBoxFromSegment(const SLineSegment& line) const;

	int GetWidth() const		{ return mColumns * mTileSize; }
	int GetHeight() const		{ return mRows * mTileSize; }
	int GetTileSize() const		{ return mTileSize; }

	int GetBrickWidth() const	{ return mBrickColumns * mBrickWidth; }
	int GetBrickHeight() const	{ return mBrickRows * mBrickHeight; }
	int GetBrickSize() const	{ return mBrickWidth * mBrickHeight; }

	Tile* GetTiles() const		{ return mTiles; }
	Brick* GetBricks() const	{ return mBricks; }

	void SetBrickType(int index, int type);

private:
	// Block copy construction and assignment operation
	Map(const Map& rhs);
	Map& operator=(const Map&);
	bool LoadLevel(const char* pLevelFile, const char* pLevelBrickFile);
	bool LoadTexturePack(const char* pTexturePackconst, const char* pBrickTexturePack);

	SGE_Sprite* mSprites;
	SGE_Sprite* mBrickSprites;
	Tile* mTiles;
	Brick* mBricks;

	int mColumns;
	int mRows;
	int mTileSize;
	int mSpriteCount;

	int mBrickColumns;
	int mBrickRows;
	int mBrickWidth;
	int mBrickHeight;
	int mBrickSpriteCount;
};

#endif // #ifndef INCLUDED_MAP_H