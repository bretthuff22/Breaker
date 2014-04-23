#include "Map.h"
#include <iostream>
using namespace std;

Map::Map()
	: mTiles(nullptr)
	, mSprites(nullptr)
	, mColumns(0)
	, mRows(0)
	, mTileSize(0)
	, mSpriteCount(0)
{
}

Map::~Map()
{
}

void Map::Load(const char* pLevelFile, const char* pTexturePack)
{
	// Clean up before we start loading anything
	Unload();

	// Load level data
	if(!LoadLevel(pLevelFile))
	{
		LogError("Failed to load level file %s.", pLevelFile);
		Unload();
		return;
	}

	// Load texture pack
	if(!LoadTexturePack(pTexturePack))
	{
		LogError("Failed to load texture pack %s.", pTexturePack);
		Unload();
		return;
	}
}

void Map::Unload()
{
	// Release memory

	if(mTiles!= nullptr)
	{
		delete[] mTiles;
		mTiles = nullptr;
	}
	if(mSprites != nullptr)
	{
		delete[] mSprites;
		mSprites = nullptr;
	}

	// Reset params
	mColumns = 0;
	mRows = 0;
	mTileSize = 0;
	mSpriteCount = 0;
}

void Map::Update(float deltaTime)
{
}

void Map::Render()
{
	for(int y = 0; y < mRows; ++y)
	{
		for(int x = 0; x < mColumns; ++x)
		{
			const int i = x + (y*mColumns);
			const SVector2 pos = mTiles[i].GetPosition();
			const int type = mTiles[i].GetType();
			mSprites[type].SetPosition(pos);
			mSprites[type].Render();
		}
	}
}

bool Map::LoadLevel(const char* pLevelFile)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, pLevelFile, "r");
	if (pFile == nullptr)
	{
		return false;
	}

	// Read map dimensions
	int scanned = 0;
	scanned += fscanf_s(pFile, "%*s %d", &mColumns);		// * reads and discards rather than store
	scanned += fscanf_s(pFile, "%*s %d", &mRows);
	scanned += fscanf_s(pFile, "%*s %d", &mTileSize);
	if (scanned < 3)
	{
		fclose(pFile);
		return false;
	}

	// Create tile buffer
	mTiles = new Tile[mColumns*mRows];

	// Parse tile data
	fgetc(pFile);
	for(int y = 0; y < mRows; ++y)
	{
		for(int x = 0; x < mColumns; ++x)
		{
			const int i = x + (y*mColumns);
			const float posX = static_cast<float>(x*mTileSize);
			const float posY = static_cast<float>(y*mTileSize);
			mTiles[i].SetPosition(SVector2(posX, posY));
			mTiles[i].SetSize(mTileSize);
			mTiles[i].SetType(fgetc(pFile) - '0'); // (-'0') converts to int
		}
		fgetc(pFile);
	}

	// Close file
	fclose(pFile);
	return true;
}
	
bool Map::LoadTexturePack(const char* pTexturePack)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, pTexturePack, "r");
	if (pFile == nullptr)
	{
		return false;
	}

	// Read map textures
	int scanned = 0;
	scanned += fscanf_s(pFile, "%*s %d", &mSpriteCount);
	if (scanned < 1)
	{
		fclose(pFile);
		return false;
	}

	// Create texture buffer
	mSprites = new SGE_Sprite[mSpriteCount];

	// Parse texture data
	for(int i = 0; i < mSpriteCount; ++i)
	{
		char buffer[128];
		fscanf_s(pFile, "%s", buffer, 128);
		mSprites[i].Load(buffer);
	}

	// Close file
	fclose(pFile);
	return true;
}