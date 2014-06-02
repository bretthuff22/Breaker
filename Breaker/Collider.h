#ifndef _COLLIDER__
#define _COLLIDER__

#include <SGE.h>

using namespace SGE;


class Collider
{
public:
	enum Shape
	{
		box,
		brick,
		circle, 
		paddle
	};

	Collider(Shape shape) : mShape(shape), mSpriteType(0) {};
	~Collider(){};

	virtual void Load(){};
	virtual void Unload(){};
	virtual void Update(float deltaTime){};
	virtual void Render(const SVector2& offset){};

	void SetBoundingBox(SRect rect)					{ mBoundingBox = rect; }		
	SRect GetBoundingBox()							{ return mBoundingBox; }

	//virtual void CreateBoundingBox() const = 0;

	void SetShape(Shape shape)						{ mShape = shape; }

	Shape GetShape()								{ return mShape; }

	const SVector2& GetPosition() const				{ return mPosition;}
	const SVector2& GetVelocity() const				{ return mVelocity;}

	void SetPosition(const SVector2& pos);
	void SetVelocity(const SVector2& vel)			{ mVelocity = vel; }
	void SetSpriteType(int type)					{ mSpriteType = type; }

	int GetSpriteType()								{ return mSpriteType; }

	virtual void CreateBoundingBox() = 0;
	
private:
	SRect mBoundingBox;
	Shape mShape;
	SVector2 mPosition;
	SVector2 mVelocity;
	int mSpriteType;
};



#endif 