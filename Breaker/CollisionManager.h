#ifndef _COLLISIONMANAGER__
#define _COLLISIONMANAGER__

#include "Collider.h"
#include "Map.h"

class CollisionManager
{
public:
	static CollisionManager& Get();

	void Register(Collider *coll);
	void UnRegister(Collider *coll);
	void Update(float deltaTime, const Map& map);

private:
	std::vector<Collider*> mColliders;

};

#endif