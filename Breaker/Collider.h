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

	enum BrickType
	{
		NLL,
		REGULAR,
		TRIHIT,
		BOMB,
		LASER,
		METAL,
		MINUS,
		PLUS,
		SHORT,
		WIDEN
	};

	Collider(Shape shape, int value);
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
	int GetValue()									{ return mValue; }

	void SetType(BrickType type)					{ mBrickType = type; }
	void SetHits(int hits)							{ mHits = hits; }

	void DecreaseHits()								{ mHits--;	}

	BrickType GetType()								{ return mBrickType; }
	int GetHits()									{ return mHits; }

	virtual void CreateBoundingBox() = 0;
	virtual void Widen(){}
	virtual void Shorten() {}
	virtual void ChangeSpeed(float scalar)			{ mVelocity = SVector2(mVelocity.x * scalar, mVelocity.y * scalar);}
	
private:
	SRect mBoundingBox;
	Shape mShape;
	SVector2 mPosition;
	SVector2 mVelocity;
	int mSpriteType;
	int mValue;
	int mHits;
	BrickType mBrickType;
};



#endif 