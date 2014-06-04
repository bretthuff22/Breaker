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
	, mBricks(nullptr)
	, mBrickSprites(nullptr)
	, mBrickColumns(0)
	, mBrickRows(0)
	, mBrickWidth(0)
	, mBrickHeight(0)
	, mBrickSpriteCount(0)
	, mBrickCount (0)
{
}

Map::~Map()
{
}

void Map::Load(const char* pLevelFile, const char* pLevelBrickFile, const char* pTexturePack, const char* pBrickTexturePack)
{
	// Clean up before we start loading anything
	Unload();

	// Load level data
	if(!LoadLevel(pLevelFile, pLevelBrickFile))
	{
		LogError("Failed to load level file %s.", pLevelFile);
		Unload();
		return;
	}

	// Load texture pack
	if(!LoadTexturePack(pTexturePack, pBrickTexturePack))
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
	if(mBricks!= nullptr)
	{
		delete[] mBricks;
		mBricks = nullptr;
	}
	if(mBrickSprites != nullptr)
	{
		delete[] mBrickSprites;
		mBrickSprites = nullptr;
	}

	// Reset params
	mColumns = 0;
	mRows = 0;
	mTileSize = 0;
	mSpriteCount = 0;

	mBrickColumns = 0;
	mBrickRows = 0;
	mBrickWidth = 0;
	mBrickHeight = 0;
	mBrickSpriteCount = 0;
}

void Map::Update(float deltaTime)
{
}

void Map::Render(const SVector2& offset)
{
	for(int y = 0; y < mRows; ++y)
	{
		for(int x = 0; x < mColumns; ++x)
		{
			const int i = x + (y*mColumns);
			const SVector2 pos = mTiles[i].GetPosition();
			const int type = mTiles[i].GetSpriteType();
			SVector2 renderPos = pos + offset;
			mSprites[type].SetPosition(renderPos);
			mSprites[type].Render();
		}
	}


	for(int y = 0; y < mBrickRows; ++y)
	{
		for(int x = 0; x < mBrickColumns; ++x)
		{
			const int i = x + (y*mBrickColumns);
			const SVector2 pos = mBricks[i].GetPosition();
			const int type = mBricks[i].GetSpriteType();
			SVector2 renderPos = pos + offset;
			mBrickSprites[type].SetPosition(renderPos);
			mBrickSprites[type].Render();
		}
	}
}

SRect Map::GetBoundingBoxFromSegment(const SLineSegment& line) const
{
	// Validate the line segment
	if (line.from.x < 0.0f || line.from.x > GetWidth() ||
		line.from.y < 0.0f || line.from.y > GetHeight() ||
		line.to.x < 0.0f || line.to.x > GetWidth() ||
		line.to.y < 0.0f || line.to.y > GetHeight())
	{
		// Line segment is out of bounds
		return SRect();
	}

	// Convert position to indices
	const int fromX = (int)line.from.x / mTileSize;
	const int fromY = (int)line.from.y / mTileSize;
	const int toX = (int)line.to.x / mTileSize;
	const int toY = (int)line.to.y / mTileSize;

	// Calculate tile count
	const int countX = toX - fromX + 1;
	const int countY =  toY - fromY + 1;

	// Get region
	SRect region;
	for (int y = 0; y < countY; ++y)
	{
		for (int x = 0; x < countX; ++x)
		{
			const int index = (fromX + x) + ((fromY + y) * mColumns);
			if (!mTiles[index].IsWalkable())
			{
				region += mTiles[index].GetBoundingBox();
			}
		}
	}
	return region;
}

bool Map::LoadLevel(const char* pLevelFile, const char* pLevelBrickFile)
{
	// LOAD BACKGROUND AND INVISIBLE BORDER
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
			mTiles[i].CreateBoundingBox();
			mTiles[i].SetSpriteType(fgetc(pFile) - '0'); // (-'0') converts to int
			mTiles[i].SetWalkable(mTiles[i].GetSpriteType() != 0);
		}
		fgetc(pFile);
	}

	// Close file
	fclose(pFile);

	// LOAD BRICKS
	FILE* pBrickFile = nullptr;
	fopen_s(&pBrickFile, pLevelBrickFile, "r");
	if (pBrickFile == nullptr)
	{
		return false;
	}

	// Read map dimensions
	scanned = 0;
	scanned += fscanf_s(pBrickFile, "%*s %d", &mBrickColumns);		// * reads and discards rather than store
	scanned += fscanf_s(pBrickFile, "%*s %d", &mBrickRows);
	scanned += fscanf_s(pBrickFile, "%*s %d", &mBrickWidth);
	scanned += fscanf_s(pBrickFile, "%*s %d", &mBrickHeight);
	if (scanned < 4)
	{
		fclose(pBrickFile);
		return false;
	}

	// Create brick buffer
	mBricks = new Brick[mBrickColumns*mBrickRows];

	// Parse brick data
	fgetc(pBrickFile);
	for(int y = 0; y < mBrickRows; ++y)
	{
		for(int x = 0; x < mBrickColumns; ++x)
		{
			const int i = x + (y*mBrickColumns);
			const float posX = static_cast<float>(x*mBrickWidth);
			const float posY = static_cast<float>(y*mBrickHeight);
			mBricks[i].SetPosition(SVector2(posX, posY));
			mBricks[i].SetSize(mBrickWidth, mBrickHeight);
			mBricks[i].CreateBoundingBox();
			const int type = fgetc(pBrickFile) - '0';
			mBricks[i].SetSpriteType(type); // (-'0') converts to int
			if (type < 6 && type > 0)
			{
				mBricks[i].SetType(Brick::BrickType::REGULAR);
				mBrickCount++;
			}
			else if (type == 6)
			{
				mBricks[i].SetType(Brick::BrickType::TRIHIT);
				mBricks[i].SetHits(3);
				mBrickCount++;
			}
			else if (type == 9)
			{
				mBricks[i].SetType(Brick::BrickType::BOMB);
				mBrickCount++;
			}
			else if (type == 10)
			{
				mBricks[i].SetType(Brick::BrickType::LASER);
				mBrickCount++;
			}
			else if (type == 11)
			{
				mBricks[i].SetType(Brick::BrickType::METAL);
			}
			else if (type == 12)
			{
				mBricks[i].SetType(Brick::BrickType::MINUS);
				mBrickCount++;
			}
			else if (type == 13)
			{
				mBricks[i].SetType(Brick::BrickType::PLUS);
				mBrickCount++;
			}
			else if (type == 14)
			{
				mBricks[i].SetType(Brick::BrickType::SHORT);
				mBrickCount++;
			}
			else if (type == 15)
			{
				mBricks[i].SetType(Brick::BrickType::WIDEN);
				mBrickCount++;
			}

			mBricks[i].SetWalkable(mBricks[i].GetSpriteType() == 0);
		}
		fgetc(pBrickFile);
	}

	return true;
}
	
bool Map::LoadTexturePack(const char* pTexturePack, const char* pBrickTexturePack)
{
	// LOAD BACKGROUND TEXTURES
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


	// LOAD BRICK TEXTURES
	FILE* pBrickFile = nullptr;
	fopen_s(&pBrickFile, pBrickTexturePack, "r");
	if (pBrickFile == nullptr)
	{
		return false;
	}

	// Read map textures
	scanned = 0;
	scanned += fscanf_s(pBrickFile, "%*s %d", &mBrickSpriteCount);
	if (scanned < 1)
	{
		fclose(pBrickFile);
		return false;
	}

	// Create texture buffer
	mBrickSprites = new SGE_Sprite[mBrickSpriteCount];

	// Parse texture data
	for(int i = 0; i < mBrickSpriteCount; ++i)
	{
		char buffer[128];
		fscanf_s(pBrickFile, "%s", buffer, 128);
		mBrickSprites[i].Load(buffer);
	}

	// Close file
	fclose(pBrickFile);


	return true;
}

void Map::SetBrickType(int index, int type)
{
	mBricks[index].SetSpriteType(type);
}