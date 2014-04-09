#ifndef INCLUDED_FIGHTER_H
#define INCLUDED_FIGHTER_H

#include <SGE.h>
using namespace SGE;

class Fighter
{
public:
	Fighter();
	~Fighter();

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

private:
	SGE_Sprite mSprite;
	SVector2 mPosition;
};

#endif // #ifndef INCLUDED_FIGHTER_H