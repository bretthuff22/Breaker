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
	void Render();

private:
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