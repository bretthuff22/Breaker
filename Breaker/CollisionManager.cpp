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
	std::vector<Ball> balls;

	// Move
	// Check collision
	// Resolve
}