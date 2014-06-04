#ifndef _COLLISIONMANAGER__
#define _COLLISIONMANAGER__

//#include "Collider.h"
#include "Map.h"

class CollisionManager
{
public:
	CollisionManager() : mPaddleWiden(false), mPaddleShorten(false){};
	static CollisionManager& Get();

	void Register(Collider *coll);
	void UnRegister(Collider *coll);

	void Load(const Map& map);
	void Unload();
	int Update(float deltaTime, const Map& map);
	void Render(const SVector2& offset);

	//SRect GetBoundingBoxFromSegment(const SLineSegment& line) const;

private:
	std::vector<Collider*> mColliders;
	
	bool mPaddleWiden;
	bool mPaddleShorten;
};

#endif