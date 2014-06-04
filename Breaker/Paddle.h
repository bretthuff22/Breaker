#ifndef INCLUDED_Paddle_H
#define INCLUDED_Paddle_H

#include <SGE.h>
using namespace SGE;

#include "Collider.h"
#include "CollisionManager.h"

class Paddle : public Collider
{
public: 
	Paddle();
	~Paddle();

	virtual void CreateBoundingBox();
	
	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render(const SVector2& offset);

	virtual void Widen();
	virtual void Shorten();

private:
	SGE_Sprite mSprite;
	float mScalar;
};

#endif // #ifndef INCLUDED_Paddle_H