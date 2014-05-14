#ifndef INCLUDED_Paddle_H
#define INCLUDED_Paddle_H

#include <SGE.h>
using namespace SGE;

#include "Map.h"

class Paddle
{
public: 
	Paddle();
	~Paddle();

	SRect GetBoundingBox() const;


	void Load();
	void Unload();
	void Update(float deltaTime, const Map& map);
	void Render(const SVector2& offset);

	const SVector2& GetPosition() const				{ return mPosition;}

	void SetPosition(const SVector2& pos)			{ mPosition = pos;}


private:
	SGE_Sprite mSprite;

	SVector2 mPosition;

	
};

#endif // #ifndef INCLUDED_Paddle_H