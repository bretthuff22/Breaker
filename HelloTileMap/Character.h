#ifndef INCLUDED_Character_H
#define INCLUDED_Character_H

#include <SGE.h>
using namespace SGE;

#include "Map.h"

class Character
{
public: 
	Character();
	~Character();

	SRect GetBoundingBox() const;


	void Load();
	void Unload();
	void Update(float deltaTime, const Map& map);
	void Render(const SVector2& offset);

	const SVector2& GetPosition() const				{ return mPosition;}
	const SVector2& GetVelocity() const				{ return mVelocity;}

	void SetPosition(const SVector2& pos)			{ mPosition = pos;}
	void SetVelocity(const SVector2& vel)			{ mVelocity = vel;}

private:
	SGE_Sprite mSprite;

	SVector2 mPosition;
	SVector2 mVelocity;
	
};

#endif // #ifndef INCLUDED_Character_H