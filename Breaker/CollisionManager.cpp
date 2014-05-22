#include "CollisionManager.h"
#include "Ball.h"
#include "Paddle.h"

CollisionManager& CollisionManager::Get()
{
	static CollisionManager sInstance;

	return sInstance;
}

void CollisionManager::Register(Collider *coll)
{
	mColliders.push_back(coll);
}

void CollisionManager::UnRegister(Collider *coll)
{
	for (std::vector<Collider*>::iterator it = mColliders.begin(); it != mColliders.end(); ++it)
	{
		if (*it == coll)
		{
			mColliders.erase(it);
			return;
		}
	}
}
	
void CollisionManager::Update(float deltaTime, const Map& map)
{
	std::vector<Collider*> balls;

	for (std::vector<Collider*>::iterator it = mColliders.begin(); it != mColliders.end(); ++it)
	{
		Collider* shape = *it;
		if (shape->GetShape() ==1)
		{
			balls.push_back(*it);
		}
	}

	std::vector<Collider*> ballsMoved;

	for (std::vector<Collider*>::iterator it = balls.begin(); it != balls.end(); ++it)
	{
		Collider* ball = *it;
		
		if (ball->GetVelocity().x != 0 && ball->GetVelocity().y != 0)
		{
			SRect bb = ball->GetBoundingBox();
			SRect newbb = bb + SVector2(ball->GetVelocity().x, 0.0f);
			for (std::vector<Collider*>::iterator itOther = mColliders.begin(); itOther != mColliders.end(); ++itOther)
			{

				Collider* other = *itOther;

				// Check left/right collision
				newbb = bb + SVector2(ball->GetVelocity().x, 0.0f);

				// Right collision
				if (other->GetBoundingBox().IsValid() 
					&& other->GetBoundingBox().min.x < newbb.max.x 
					&& other->GetBoundingBox().max.y < newbb.min.y 
					&& other->GetBoundingBox().min.y > newbb.max.y)
				{
					ball->SetPosition(SVector2(ball->GetPosition().x + (int)(other->GetBoundingBox().min.x - bb.max.x) - 1.0f, ball->GetPosition().y));
					ball->SetVelocity(SVector2(ball->GetVelocity().x * -1, ball->GetVelocity().y));

					// DESTROY IF BRICK
					other->Update(deltaTime, map);
				}
				// Left collision
				else if (other->GetBoundingBox().IsValid() 
						&& other->GetBoundingBox().max.x > newbb.min.x 
						&& other->GetBoundingBox().max.y < newbb.min.y 
						&& other->GetBoundingBox().min.y > newbb.max.y)
				{
					ball->SetPosition(SVector2(ball->GetPosition().x + (int)(other->GetBoundingBox().max.x - bb.min.x) + 1.0f, ball->GetPosition().y));
					ball->SetVelocity(SVector2(ball->GetVelocity().x * -1, ball->GetVelocity().y));
					// DESTROY IF BRICK
					other->Update(deltaTime, map);
				}
				else
				{
					ball->SetPosition(SVector2(ball->GetPosition().x + (int)ball->GetVelocity().x, ball->GetPosition().y));
				}


				// Check top/bottom intersection
				newbb =  bb + SVector2(0.0f, ball->GetVelocity().y);

				// Bottom collision
				if(other->GetBoundingBox().IsValid() 
					&& other->GetBoundingBox().min.y < newbb.max.y 
					&& other->GetBoundingBox().min.x > newbb.max.x 
					&& other->GetBoundingBox().max.x < newbb.min.x)
				{
					ball->SetPosition(SVector2(ball->GetPosition().x, ball->GetPosition().y - (int)(other->GetBoundingBox().min.y - bb.max.y - 1.0f)));
					ball->SetVelocity(SVector2(ball->GetVelocity().x, ball->GetVelocity().y * -1));
					// DESTROY IF BRICK
					other->Update(deltaTime, map);
				}

				// Top collision
				else if(other->GetBoundingBox().IsValid() 
						&& other->GetBoundingBox().max.y > newbb.min.y
						&& other->GetBoundingBox().min.x > newbb.max.x 
						&& other->GetBoundingBox().max.x < newbb.min.x)
				{
					ball->SetPosition(SVector2(ball->GetPosition().x, ball->GetPosition().y - (int)(other->GetBoundingBox().max.y - bb.min.y - 1.0f)));
					ball->SetVelocity(SVector2(ball->GetVelocity().x, ball->GetVelocity().y * -1));
					// DESTROY IF BRICK
					other->Update(deltaTime, map);
				}
				else
				{
					ball->SetPosition(SVector2(ball->GetPosition().x, ball->GetPosition().y + (int)ball->GetVelocity().y));
				}
			}
		}



	}


	// Move
	// Check collision
	// Resolve
}


/*SRect CollisionManager::GetBoundingBoxFromSegment(const SLineSegment& line) const
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
}*/