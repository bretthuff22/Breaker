#ifndef INCLUDED_BULLET_H
#define INCLUDED_BULLET_H

#include <SGE.h>
using namespace SGE;

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

	void Fire(const SVector2& pos, const SVector2& vel);
	void Kill();

	SCircle GetBoundingCircle() const	{ return SCircle(mPosition, 10.0f); } // approx radius
	bool IsAlive() const				{ return mActive; }


private:
	SGE_Sprite mSprite;
	SVector2 mPosition;
	SVector2 mVelocity;
	bool mActive;
};

#endif // #ifndef INCLUDED_BULLET_H