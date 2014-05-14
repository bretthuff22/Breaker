#ifndef INCLUDED_Ball_H
#define INCLUDED_Ball_H

#include <SGE.h>
using namespace SGE;

#include "Map.h"

class Ball
{
public:
	Ball();
	~Ball();

	void Load();
	void Unload();
	void Update(float deltaTime, const Map& map);
	void Render(const SVector2& offset);

	void Fire(const SVector2& pos, const SVector2& vel);
	void Kill();

	SCircle GetBoundingCircle() const	{ return SCircle(mPosition, 10.0f); } // approx radius
	SRect GetBoundingBox() const		{ return SRect(mPosition.x - 10.0f, mPosition.y - 20.0f, mPosition.x + 10.0f, mPosition.y);}
	bool IsAlive() const				{ return mActive; }

	void SetPosition(const SVector2& pos)			{ mPosition = pos;}


private:
	SGE_Sprite mSprite;
	SVector2 mPosition;
	SVector2 mVelocity;
	bool mActive;
};

#endif // #ifndef INCLUDED_Ball_H