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

	//SRect GetBoundingBoxFromSegment(const SLineSegment& line) const;

private:
	std::vector<Collider*> mColliders;

};

#endif