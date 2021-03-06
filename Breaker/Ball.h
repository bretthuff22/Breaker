#ifndef INCLUDED_Ball_H
#define INCLUDED_Ball_H

#include <SGE.h>
using namespace SGE;

#include "Collider.h"
#include "CollisionManager.h"

class Ball : public Collider
{
public:
	Ball();
	~Ball();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render(const SVector2& offset);

	void Fire(const SVector2& pos, const SVector2& vel);
	void Kill();

	// SCircle GetBoundingCircle() const	{ return SCircle(mPosition, 8.0f); } // approx radius
	virtual void CreateBoundingBox()		{ Collider::SetBoundingBox(SRect (	Collider::GetPosition().x - 8.0f, Collider::GetPosition().y - 16.0f, Collider::GetPosition().x + 8.0f, Collider::GetPosition().y	)); }
	
	void SetAlive(bool alive)			{ mActive = alive; }
	bool IsAlive() const				{ return mActive; }

	void SetRandomVelocity();


private:
	SGE_Sprite mSprite;
	bool mActive;
};

#endif // #ifndef INCLUDED_Ball_H