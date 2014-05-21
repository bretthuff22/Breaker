#ifndef _COLLIDER__
#define _COLLIDER__

#include <SGE.h>
using namespace SGE;

class Collider
{
public:
	Collider();
	~Collider();

	enum Shape
	{
		box,
		circle
	};

	void SetBoundingBox(SRect rect)					{ mBoundingBox = rect; }		
	SRect GetBoundingBox()							{ return mBoundingBox; }

	virtual void CreateBoundingBox() const = 0;

	void SetShape(Shape shape)						{ mShape = shape; }

	int GetShape()									{ return mShape; }

	const SVector2& GetPosition() const				{ return mPosition;}
	const SVector2& GetVelocity() const				{ return mVelocity;}

	void SetPosition(const SVector2& pos)			{ mPosition = pos;}
	void SetVelocity(const SVector2& vel)			{ mVelocity = vel; }
	
private:
	SRect mBoundingBox;
	Shape mShape;
	SVector2 mPosition;
	SVector2 mVelocity;
};



#endif 