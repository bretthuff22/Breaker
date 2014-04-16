#ifndef INCLUDED_Enemy_H
#define INCLUDED_Enemy_H

#include <SGE.h>
using namespace SGE;

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	void Spawn(const SVector2& pos);
	void Kill();
	SCircle GetBoundingCircle() const	{ return SCircle(mPosition, 50.0f); } // approx radius
	bool IsAlive() const				{ return mActive; }


private:
	SGE_Sprite mSprite;
	SVector2 mPosition;
	SVector2 mVelocity;
	bool mActive;
};

#endif // #ifndef INCLUDED_Enemy_H